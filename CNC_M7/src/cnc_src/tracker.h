#ifndef tracker_h__
#define tracker_h__

#include <asf.h>
#include <vector.h>
#include <motors.h>


#define MCK_8		TC_CMR_TCCLKS_TIMER_CLOCK2
#define MCK_32		TC_CMR_TCCLKS_TIMER_CLOCK3
#define MCK_128		TC_CMR_TCCLKS_TIMER_CLOCK4

#define MCK			150000000

#define MCK_DIV_8		18750000
#define MCK_DIV_32		4687500
#define MCK_DIV_128		1171875





class Tracker{
public:

	Motors motor_x;
	Motors motor_y;
	Motors motor_z;

	int32_t delay_ms_irq;

	uint32_t actual_speed;
	uint32_t target_speed;

	Vector abs_pos;

	uint8_t acl_phase;
	uint8_t dcl_phase;

	uint32_t accel;
	uint32_t step_time;

	uint8_t lock;

	Tracker():
		motor_x(PIOA, PIO_PA19, PIOC, PIO_PC31),
		motor_y(PIOB, PIO_PB2, PIOB, PIO_PB3),
		motor_z(PIOC, PIO_PC30, PIOA, PIO_PA0),
		actual_speed(0),
		target_speed(1000),
		abs_pos(1, 1, 1),
		acl_phase(1),
		dcl_phase(0),
		accel(2000),
		step_time(1000),
		lock(1)
	{
		pmc_enable_periph_clk(ID_TC0);
		pmc_enable_periph_clk(ID_TC1);

		REG_TC0_CCR1 = 1;
		REG_TC0_CMR1 = (MCK_32) | (1<<15) | (1<<14);
		REG_TC0_RC1 = (MCK_DIV_32 / (accel * 2));
		REG_TC0_IER1 = (1<<4);
		REG_TC0_CCR1 = 5;
	};

	void line_3d(Vector* start, Vector* stop);
	void step(int8_t x, int8_t y, int8_t z);
	uint32_t set_speed(uint32_t step_per_second);
	uint32_t set_accelerate(uint32_t accelerate);

	// there is 3 instance (0-2) with each instance have 3 channels but you can enalbe clock for 12 timers channel
	// and interrupt vectors have number form 0 to 12 (and i do not know where is fourth instance of timers).
	// ID_TC1 does it mean second channel in first instance of any timers in same70q21
	// but here you have to type instance number (0-2) and channel in this instance (0-2)
	// why atmel do not use consistent nubering of vectors and channels i do not know, but now i can tell you how they think about it.
};

extern Tracker tracker;

#endif // tracker_h__
