#ifndef ClassSerial_h__
#define ClassSerial_h__

#include <asf.h>
#include <../src/containers/array.h>

extern array<uint8_t> uart_rec_buff;

class Serial{
	public:
	Serial(void);

	void SetBaudRate(uint32_t baud);
	void Enable(void);
	void Disable(void);
	void InterruptEnable_RX(void);
	void InterruptDisable_RX(void);
	void write(uint8_t* buff, uint8_t size);
	void write(const char* s, uint8_t size);
	void write(char* t);
	void write(const char* s);
	void write(uint8_t byte);
	void write(array<uint8_t> &data);
	uint8_t readByte(void);
};

extern Serial serial;


#endif // ClassSerial_h__