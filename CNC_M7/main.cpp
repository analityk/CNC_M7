/*
 * GccApplication2.cpp
 *
 * Created: 2020-01-16 19:36:51
 * Author : Szymon
 */

#include <asf.h>
#include <string.h>
#include "mini_ip.h"
#include "conf_eth.h"
#include <array.h>
#include <math.h>

#define BITS_BY_SLOT	16
#define TOTAL_BUFFERS	4
#define MAX_DMA_SIZE	500

#define XDMA_SSC_TX_CH	0
#define XDMA_SSC_RX_CH	1

uint32_t volatile xdmac_chan_0_status = 0;
uint32_t volatile xdmac_chan_1_status = 0;

uint8_t volatile manage_byte = 0;

uint8_t volatile record = 0;

uint8_t head_vol = 10;
uint8_t pc_vol = 7;

COMPILER_ALIGNED(8)
lld_view1 linklist_write[TOTAL_BUFFERS];
lld_view1 linklist_read[TOTAL_BUFFERS];


COMPILER_ALIGNED(8)
int16_t TxAudioBuffer[TOTAL_BUFFERS][MAX_DMA_SIZE * (BITS_BY_SLOT/8)];
int16_t RxAudioBuffer[TOTAL_BUFFERS][MAX_DMA_SIZE * (BITS_BY_SLOT/8)];
COMPILER_PACK_RESET();

void delay(uint32_t volatile t){
	while(t--){};
};


DTCM uint8_t gs_uc_mac_address[] = {
	ETHERNET_CONF_ETHADDR0, ETHERNET_CONF_ETHADDR1, ETHERNET_CONF_ETHADDR2,
	ETHERNET_CONF_ETHADDR3, ETHERNET_CONF_ETHADDR4, ETHERNET_CONF_ETHADDR5
};

DTCM uint8_t gs_uc_ip_address[] = { 192, 168, 0, 20 };

/** The GMAC driver instance */
DTCM gmac_device_t gs_gmac_dev;

/** Buffer for ethernet packets */
DTCM volatile uint8_t gs_uc_eth_buffer_a[GMAC_FRAME_LENTGH_MAX];
//DTCM volatile uint8_t gs_uc_eth_buffer_b[GMAC_FRAME_LENTGH_MAX];

DTCM volatile uint8_t temp_udp_header[42];

DTCM volatile uint8_t bc = 0;

DTCM volatile uint32_t del = 0x4FFFFF;

DTCM uint16_t volatile ptr_a = 0;
DTCM uint16_t volatile ptr_b = 0;

DTCM uint8_t volatile active_read_buffer = 0;

DTCM volatile uint8_t ba_lock = 1;
DTCM volatile uint8_t bb_lock = 1;

uint8_t volatile tx_swch = 0;
uint8_t volatile rx_swch = 0;

uint8_t volatile rx_ba = 1;
uint8_t volatile rx_bb = 1;


uint32_t volatile long_time = 0;
uint8_t volatile ledstate = 0;

//__attribute__((section(".itcm_functions")))__attribute__((aligned(64)))
uint16_t gmac_icmp_checksum(uint16_t *p_buff, uint32_t ul_len)
{
	uint32_t i, ul_tmp;

	for(i = 0, ul_tmp = 0; i < ul_len; i++, p_buff++){
		ul_tmp += SWAP16(*p_buff);
	};
	ul_tmp = (ul_tmp & 0xffff) + (ul_tmp >> 16);

	return (uint16_t) (~ul_tmp);
}

//__attribute__((section(".itcm_functions")))__attribute__((aligned(64)))
uint16_t gmac_ip_checksum(p_ip_header_t ph){
	// how many 4B words is in ip header -> words is two times more
	uint16_t words = 2 * (ph->ip_hl_v & 0x0F);
	// don't include actual checksum of ip header
	ph->ip_sum = 0;
	// ip header is always 4 byte multiplies, use pointer to memory like uint16_t
	uint16_t* p_buff = (uint16_t*)ph;

	uint32_t i, ul_tmp = 0;

	for(i = 0; i < words; i++, p_buff++){
		ul_tmp += SWAP16(*p_buff);
	};
	ul_tmp = (ul_tmp & 0xffff) + (ul_tmp >> 16);
	ul_tmp = (ul_tmp & 0xffff) + (ul_tmp >> 16);
	return (uint16_t) (~ul_tmp);
}

//__attribute__((section(".itcm_functions")))__attribute__((aligned(64)))
uint16_t udp_new_packet_length(uint8_t* p_uc_data, uint16_t new_payload_size){

	p_ip_header_t ip_header = (p_ip_header_t) (p_uc_data + ETH_HEADER_SIZE);
	p_udp_header_t udp_header = (p_udp_header_t)(p_uc_data + ETH_HEADER_SIZE + ETH_IP_HEADER_SIZE);

	// udp frame = udp header size plus udp payload
	uint16_t udp_frame_size = ETH_UDP_HEADER_SIZE + new_payload_size;

	// total bytes for by mac = eth header + ip_total_len (ip header + udp header + udp payload)
	uint16_t gmac_payload = ETH_HEADER_SIZE + ETH_IP_HEADER_SIZE + udp_frame_size;

	// ip frame size = ip header + udp header + udp payload
	uint16_t ip_frame_size = udp_frame_size + ETH_IP_HEADER_SIZE;

	uint16_t udp_datalen = udp_frame_size - ETH_UDP_HEADER_SIZE;

	ip_header->ip_len = SWAP16(ip_frame_size);

	udp_header->length = SWAP16(udp_frame_size);

	uint16_t crc = gmac_ip_checksum(ip_header);
	ip_header->ip_sum = SWAP16(crc);

	return gmac_payload;
};


uint8_t volatile pck_rec = 0;

//__attribute__((section(".itcm_functions")))__attribute__((aligned(64)))
void gmac_process_udp_packet(uint8_t* p_uc_data, uint32_t ul_size){
	UNUSED(ul_size);

	p_ethernet_header_t p_eth = (p_ethernet_header_t) p_uc_data;
	p_ip_header_t ip_header = (p_ip_header_t) (p_uc_data + ETH_HEADER_SIZE);
	p_udp_header_t udp_header = (p_udp_header_t)(p_uc_data + ETH_HEADER_SIZE + ETH_IP_HEADER_SIZE);
	uint8_t* udp_pdata = (uint8_t*)(p_uc_data + ETH_HEADER_SIZE + ETH_IP_HEADER_SIZE + ETH_UDP_HEADER_SIZE);
	uint16_t raw_data_payload = SWAP16(udp_header->length) - ETH_UDP_HEADER_SIZE;

	/* Swap the UDP port destination and source */
	uint16_t rp = udp_header->scr_port;
	udp_header->scr_port = udp_header->dst_port;
	udp_header->dst_port = rp;


	/* Swap the IP destination  address and the IP source address */
	for (uint8_t i = 0; i < 4; i++) {
		ip_header->ip_dst[i] = ip_header->ip_src[i];
		ip_header->ip_src[i] = gs_uc_ip_address[i];
	};

	/* Swap ethernet destination address and ethernet source address */
	for (uint8_t i = 0; i < 6; i++) {
		/* Swap ethernet destination address and ethernet source address */
		p_eth->et_dest[i] = p_eth->et_src[i];
		p_eth->et_src[i] = gs_uc_mac_address[i];
	};


	// port numbers was swaped
	if(SWAP16(udp_header->scr_port) != 52001)return;

	uint16_t gmac_payload = udp_new_packet_length(p_uc_data, 4);

	udp_header->crc = 0;

	udp_pdata[0] = xdmac_chan_0_status;
	udp_pdata[1] = xdmac_chan_0_status << 8;
	udp_pdata[2] = xdmac_chan_0_status << 16;
	udp_pdata[3] = manage_byte;

	gmac_dev_write(&gs_gmac_dev, GMAC_QUE_0, p_uc_data, gmac_payload, NULL);

	if(pck_rec == 1){
		long_time = 0;
	};
};

//__attribute__((section(".itcm_functions")))__attribute__((aligned(64)))
void gmac_process_ip_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint32_t i;
	uint32_t ul_icmp_len;
	int32_t ul_rc = GMAC_OK;

	/* avoid Cppcheck Warning */
	UNUSED(ul_size);

	p_ethernet_header_t p_eth = (p_ethernet_header_t) p_uc_data;
	p_ip_header_t p_ip_header = (p_ip_header_t) (p_uc_data + ETH_HEADER_SIZE);

	p_icmp_echo_header_t p_icmp_echo = (p_icmp_echo_header_t) ((int8_t *) p_ip_header + ETH_IP_HEADER_SIZE);

	switch (p_ip_header->ip_p) {
		case IP_PROT_UDP: {

			gmac_process_udp_packet(p_uc_data, ul_size);

			break;
		};
		case IP_PROT_ICMP:
		if (p_icmp_echo->type == ICMP_ECHO_REQUEST) {
			p_icmp_echo->type = ICMP_ECHO_REPLY;
			p_icmp_echo->code = 0;
			p_icmp_echo->cksum = 0;

			/* Checksum of the ICMP message */
			ul_icmp_len = (SWAP16(p_ip_header->ip_len) - ETH_IP_HEADER_SIZE);
			if (ul_icmp_len % 2) {
				*((uint8_t *) p_icmp_echo + ul_icmp_len) = 0;
				ul_icmp_len++;
			}
			ul_icmp_len = ul_icmp_len / sizeof(uint16_t);

			p_icmp_echo->cksum = SWAP16(gmac_icmp_checksum((uint16_t *)p_icmp_echo, ul_icmp_len));
			/* Swap the IP destination  address and the IP source address */
			for (i = 0; i < 4; i++) {
				p_ip_header->ip_dst[i] = p_ip_header->ip_src[i];
				p_ip_header->ip_src[i] = gs_uc_ip_address[i];
			}
			/* Swap ethernet destination address and ethernet source address */
			for (i = 0; i < 6; i++) {
				/* Swap ethernet destination address and ethernet source address */
				p_eth->et_dest[i] = p_eth->et_src[i];
				p_eth->et_src[i] = gs_uc_mac_address[i];
			}
			/* Send the echo_reply */

			ul_rc = gmac_dev_write(&gs_gmac_dev, GMAC_QUE_0, p_uc_data, SWAP16(p_ip_header->ip_len) + ETH_HEADER_SIZE, NULL);

			if (ul_rc != GMAC_OK) {
				printf("E: ICMP Send - 0x%x\n\r", ul_rc);
			}
		}
		break;

		default:
		break;
	}
}


DTCM uint8_t volatile arp_rec = 0;

void gmac_process_arp_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint32_t i;
	uint8_t ul_rc = GMAC_OK;

	p_ethernet_header_t p_eth = (p_ethernet_header_t) p_uc_data;
	p_arp_header_t p_arp = (p_arp_header_t) (p_uc_data + ETH_HEADER_SIZE);

	if (SWAP16(p_arp->ar_op) == ARP_REQUEST) {

		/* ARP reply operation */
		p_arp->ar_op = SWAP16(ARP_REPLY);

		/* Fill the destination address and source address */
		for (i = 0; i < 6; i++) {
			/* Swap ethernet destination address and ethernet source address */
			p_eth->et_dest[i] = p_eth->et_src[i];
			p_eth->et_src[i] = gs_uc_mac_address[i];
			p_arp->ar_tha[i] = p_arp->ar_sha[i];
			p_arp->ar_sha[i] = gs_uc_mac_address[i];
		}
		/* Swap the source IP address and the destination IP address */
		for (i = 0; i < 4; i++) {
			p_arp->ar_tpa[i] = p_arp->ar_spa[i];
			p_arp->ar_spa[i] = gs_uc_ip_address[i];
		}

		ul_rc = gmac_dev_write(&gs_gmac_dev, GMAC_QUE_0, p_uc_data, ul_size, NULL);
		if(arp_rec == 0){
			arp_rec = 1;
		}
	}
}

static void gmac_process_eth_packet(uint8_t *p_uc_data, uint32_t ul_size)
{
	uint16_t us_pkt_format;

	p_ethernet_header_t p_eth = (p_ethernet_header_t) (p_uc_data);
	us_pkt_format = SWAP16(p_eth->et_protlen);

	switch (us_pkt_format) {
		/* ARP Packet format */
		case ETH_PROT_ARP:
		/* Process the ARP packet */
		gmac_process_arp_packet(p_uc_data, ul_size);

		break;

		/* IP protocol frame */
		case ETH_PROT_IP:
		/* Process the IP packet */
		gmac_process_ip_packet(p_uc_data, ul_size);

		break;

		default:break;
	};
};

void GMAC_Handler(void)
{
	gmac_handler(&gs_gmac_dev, GMAC_QUE_0);
}

/**
 * \brief XDMAC interrupt handler.
 */

#define LED_CLR { pio_set(PIOC, PIO_PC8); }
#define LED_SET { pio_clear(PIOC, PIO_PC8); }

volatile uint32_t led_dma_state = 0;

volatile uint8_t txb = 2;
volatile uint8_t ntxb = 0;

volatile uint8_t rxb = 1;
volatile uint8_t nrxb = 0;

void XDMAC_Handler(void)
{
	uint32_t volatile xdmac_gis = xdmac_get_interrupt_status(XDMAC);
	UNUSED(xdmac_gis);

	xdmac_chan_0_status = xdmac_channel_get_interrupt_status(XDMAC, XDMA_SSC_TX_CH);
	if( xdmac_chan_0_status == 1){
		txb++;
		if(txb > TOTAL_BUFFERS){
			txb = 1;
		};
	};

	xdmac_chan_1_status = xdmac_channel_get_interrupt_status(XDMAC, XDMA_SSC_RX_CH);
	if( xdmac_chan_1_status == 1){
		rxb++;
		if(rxb > TOTAL_BUFFERS){
			rxb = 1;
		};
	};
};

void TC0_Handler(void){

	uint32_t volatile tc0_status0 = REG_TC0_SR0;
	long_time++;

	if( long_time > 20 ){
		ledstate++;
		long_time = 0;
	};

	//if( ((ledstate % 2) == 1) && (arp_rec == 1)){
		//pio_set(PIOC, PIO_PC8);
	//}else{
		//pio_clear(PIOC, PIO_PC8);
	//};

	REG_TC0_CCR0 = 5;
};

xdmac_channel_config_t xdmac_ssc_tx_cfg = {0};
xdmac_channel_config_t xdmac_ssc_rx_cfg = {0};

int main(void)
{
    /* Initialize the SAM system */

	sysclk_init();

	board_init();

	pio_configure(PIOC, PIO_OUTPUT_0, PIO_PC8, PIO_PULLUP);	// LED
	pio_clear(PIOC, PIO_PC8);

	uint16_t b = 3;
	uint16_t c = 4;

	uint32_t ul_frm_size;
	volatile uint32_t ul_delay;
	gmac_options_t gmac_option;

	/* Enable GMAC clock */
	pmc_enable_periph_clk(ID_GMAC);

	gmac_option.uc_copy_all_frame = 0;
	gmac_option.uc_no_boardcast = 0;

	memcpy(gmac_option.uc_mac_addr, gs_uc_mac_address, sizeof(gs_uc_mac_address));

	gs_gmac_dev.p_hw = GMAC;

	/* Init GMAC driver structure */
	gmac_dev_init(GMAC, &gs_gmac_dev, &gmac_option);
	delay(0x5FFfffF);


	pmc_enable_periph_clk(ID_TC0);
	tc_set_writeprotect(TC0, 0);
	tc_init(TC0, 0, 0);

	REG_TC0_CCR0 = 1;
	REG_TC0_CMR0 = (3<<0) | (1<<15) | (1<<14);
	REG_TC0_RC0 = 58594;

	REG_TC0_IER0 = (1<<4);

	REG_TC0_CCR0 = 5;

	irq_initialize_vectors();

	irq_register_handler(XDMAC_IRQn, 1);
	irq_register_handler(GMAC_IRQn, 3);
	irq_register_handler(TC0_IRQn, 4);

	Enable_global_interrupt();

	gmac_dev_reset(&gs_gmac_dev, GMAC_QUE_0);

	ethernet_phy_reset(GMAC, 0);

	/* Init MAC PHY driver */
	if (ethernet_phy_init(GMAC, BOARD_GMAC_PHY_ADDR, sysclk_get_cpu_hz()) != GMAC_OK) {
		bc = 3;
	};

	/* Auto Negotiate, work in RMII mode */
	if (ethernet_phy_auto_negotiate(GMAC, BOARD_GMAC_PHY_ADDR) != GMAC_OK) {
		bc = 4;
	}

	/* Establish ethernet link */
	while (ethernet_phy_set_link(GMAC, BOARD_GMAC_PHY_ADDR, 1) != GMAC_OK) {
		bc = 5;
	};

    /* Replace with your application code */
    while (1)
    {
		if( GMAC_OK == gmac_dev_read(&gs_gmac_dev, GMAC_QUE_0, (uint8_t *) gs_uc_eth_buffer_a, sizeof(gs_uc_eth_buffer_a), &ul_frm_size) ){
			if (ul_frm_size > 0) {
				gmac_process_eth_packet((uint8_t *) gs_uc_eth_buffer_a, ul_frm_size);
			};
		};
    };
};