#ifndef timers_h__
#define timers_h__

#include <asf.h>

typedef void (*StepCallback)(int8_t, int8_t, int8_t);

uint8_t volatile do_step = 0;
uint8_t volatile do_low = 0;

void TC0_Handler( void ){
	if(do_step == 1){
		// call step fun
		do_step = 0;
	};
	if(do_low == 1){
		// call method make motor driver signals low
		do_low = 0;
	};
};

#endif // timers_h__
