#include <i2c_soft.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t codec_addr = 0;

 void get_codec_addr(uint8_t ad)
{
	codec_addr = ad;
};

uint8_t GET_SDA(void)
{
	pio_configure(I2C_SDA_PIO, PIO_INPUT, I2C_SDA, PIO_PULLUP);

	for(uint8_t n=0; n<255; n++){
		SET_SCL;
		if( pio_get(I2C_SDA_PIO, PIO_INPUT, I2C_SDA) == 0 ){
			mdelay(0xFF);
			return 1;
		};
		mdelay(0xFF);
	};
	return 0;
};

void i2c_init(void){
	SET_SCL;
	SET_SDA;
	mdelay(I2C_DELAY);
};

void i2c_start(void)
{
	pio_configure(I2C_SDA_PIO, PIO_OUTPUT_0, I2C_SDA, PIO_PULLUP);
	CLR_SDA;
	mdelay(I2C_DELAY);
	CLR_SCL;
	mdelay(I2C_DELAY);
};


void i2c_stop(void)
{
	pio_configure(I2C_SDA_PIO, PIO_OUTPUT_0, I2C_SDA, PIO_PULLUP);
	CLR_SDA;
	mdelay(I2C_DELAY);
	SET_SCL;
	mdelay(I2C_DELAY);
	SET_SDA;
	mdelay(I2C_DELAY);
	pio_configure(I2C_SDA_PIO, PIO_INPUT, I2C_SDA, PIO_PULLUP);
};

void i2c_write(uint8_t b)
{
	pio_configure(I2C_SDA_PIO, PIO_OUTPUT_0, I2C_SDA, PIO_PULLUP);
	
	uint8_t i = 0x80;
	
	for(; i; i >>= 1)
	{
		if(b & i){ SET_SDA; } else { CLR_SDA; };
			
		mdelay(I2C_DELAY);
		SET_SCL;
		mdelay(I2C_DELAY);	
		CLR_SCL;
		mdelay(I2C_DELAY);
		
		mdelay(I2C_DELAY/2);
	};
	
	SET_SDA;
	pio_configure(I2C_SDA_PIO, PIO_INPUT, I2C_SDA, PIO_PULLUP);
	
};

uint8_t i2c_ack(void)
{
	uint8_t i = 0;
	i = GET_SDA();

	CLR_SCL;
	mdelay(I2C_DELAY);
	return i;
};

uint8_t i2c_codec_write(uint8_t adr, uint16_t data)
{
	
	uint8_t data_tx = data & 0xFF;
	uint8_t b8 = (data & 0x0100) >> 8;
		
	uint8_t cd =(uint8_t)((adr << 1) | b8);
	
	uint8_t acks = 0;
	
	i2c_start();
	i2c_write(0x34);
	if(i2c_ack()==0)acks++;
	i2c_write(cd);
	if(i2c_ack()==0)acks++;
	i2c_write(data_tx);
	if(i2c_ack()==0)acks++;
	i2c_stop();
	
return acks;
};

uint8_t i2c_test_addr(uint8_t addr)
{
	uint8_t ack = 0;
	i2c_start();
	i2c_write(addr);
	if(i2c_ack() == 1)ack++;
	i2c_write(0);
	if(i2c_ack() == 1)ack++;
	i2c_write(0);
	if(i2c_ack() == 1)ack++;
	i2c_stop();
	
	return ack;
};

#ifdef __cplusplus
}
#endif