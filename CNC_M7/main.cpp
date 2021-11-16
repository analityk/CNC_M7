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
#include <../src/containers/array.h>
#include <math.h>
#include <ClassSerial.h>
#include <ClassGpio.h>
#include <stdlib.h>

#define LED_CLR { pio_set(PIOC, PIO_PC8); }
#define LED_SET { pio_clear(PIOC, PIO_PC8); }

int main(void)
{
    /* Initialize the SAM system */

	sysclk_init();

	board_init();

	pio_configure(PIOC, PIO_OUTPUT_0, PIO_PC8, PIO_PULLUP);
	pio_configure(PIOA, PIO_OUTPUT_0, PIO_PA2, PIO_DEFAULT);

	fpu_enable();


	irq_initialize_vectors();

	Enable_global_interrupt();

    while (1)
    {

    };
};