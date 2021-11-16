#include <ClassSerial.h>

sam_uart_opt_t rs232_opt;


void init_232(void){
	uart_init(UART4, &rs232_opt);
	uart_enable(UART4);
};

Serial::Serial(void){
	pio_configure(PIOD, PIO_PERIPH_C, PIO_PD18, PIO_DEFAULT);
	pio_configure(PIOD, PIO_PERIPH_C, PIO_PD19, PIO_DEFAULT);
	pmc_enable_periph_clk(ID_UART4);


	rs232_opt.ul_baudrate = 115200;
	rs232_opt.ul_mck = 150000000;
	rs232_opt.ul_mode = (4<<9); // parity none
	init_232();
};

void Serial::SetBaudRate(uint32_t baud){
	rs232_opt.ul_baudrate = baud;
	init_232();
};

void Serial::Enable(void)
{
	uart_enable(UART4);
};

void Serial::Disable(void)
{
	uart_disable(UART4);
};

void Serial::InterruptEnable_RX(void)
{
	//uart_enable_interrupt(UART4, )
};

void Serial::InterruptDisable_RX(void)
{
	//
};

void Serial::write(uint8_t* buff, uint8_t size){
	for(uint8_t i=0; i < size; i++){
		while(!uart_is_tx_empty(UART4)){};
		uart_write(UART4, buff[i]);
	};
};

void Serial::write(const char* s, uint8_t size){
	this->write( (uint8_t*)s, size);
};

void Serial::write(char* t){
	while(*t){
		while(!uart_is_tx_empty(UART4)){};
		uart_write(UART4, *t++);
	};
};

void Serial::write(const char* s){
	while(*s){
		while(!uart_is_tx_empty(UART4)){};
		uart_write(UART4, *s++);
	};
};

void Serial::write(uint8_t byte)
{
	while(!uart_is_tx_empty(UART4)){};
	uart_write(UART4, byte);
};

void Serial::write(array<uint8_t> &data)
{
	for(uint8_t i=0; i<data.size(); i++){
		if( data[i] == 0 )break;
		if( data[i] == '\n' ){
			this->write( (uint8_t) data[i]);
			break;
		};

		this->write( (uint8_t) data[i]);
	};
};

uint8_t Serial::readByte(){
	uint8_t t;
	while(!uart_is_rx_ready(UART4)){};
	uart_read(UART4, &t);
	return t;
};

Serial serial;