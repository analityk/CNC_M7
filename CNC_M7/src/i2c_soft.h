#ifndef i2c_soft_h__
#define i2c_soft_h__

#include <asf.h>
#include <mdelay.h>

#ifdef __cplusplus
extern "C" {
#endif

void get_codec_addr(uint8_t ad);

#define I2C_DELAY	600

#define I2C_SDA	PIO_PA3
#define I2C_SCL	PIO_PA4

#define I2C_SDA_PIO	PIOA
#define I2C_SCL_PIO	PIOA

#define CLR_SDA	{ pio_clear(I2C_SDA_PIO, I2C_SDA); }
	
#define SET_SDA { pio_set(I2C_SDA_PIO, I2C_SDA); }
	
#define CLR_SCL { pio_clear(I2C_SCL_PIO, I2C_SCL); }
	
#define SET_SCL { pio_set(I2C_SCL_PIO, I2C_SCL); }
	
uint8_t GET_SDA(void);


void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t b);

uint8_t i2c_ack(void);

uint8_t i2c_codec_write(uint8_t adr, uint16_t data);

uint8_t i2c_test_addr(uint8_t addr);


#ifdef __cplusplus
}
#endif

#endif // i2c_soft_h__
