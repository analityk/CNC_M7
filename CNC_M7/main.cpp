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
#include <stdlib.h>
#include <tracker.h>

#define LED_CLR { pio_set(PIOC, PIO_PC8); }
#define LED_SET { pio_clear(PIOC, PIO_PC8); }

/*
	znane b³êdy - nie dzia³a serial TX. Zdebugowaæ.
*/

/*
	jak to dzia³a:
	dostajemy do wykonania gkody - buforowane stringi do rozkodowania
	ruch w x i y jest liczony dla narzêdzia a nie dla silników. chodzi o
	zachowanie sta³ej prêdkoœci narzêdzia a nie sta³ej prêdkoœci silnika.

	wszystkie ruchy sprowadzamy do linii. du¿o krótkich (lub d³ugich) odcinków.
	ka¿dy odcinek ma wiod¹c¹ oœ i w niej zawiera n kroków,
	do tego dochodzi maksymalnie tyle samo kroków w osi zale¿nej od wiod¹cej, czyli ruchy pod k¹tem od zera do 45 stopni
	wzlêdem osi g³ównej/wiod¹cej

	w wolnym czasie nale¿y zbudowaæ bufor takich odcinków i dbaæ o jego zape³nienie.
	to bêdzie bufor ma poziomie pomiêdzy gkodem a transmisj¹ danych z pc.

	krok wykonywany bêdzie w przerwaniu od timera tc0.
	krok to bêdzie pojedyncza iteracja algorytmu bresenhama.
	na ka¿dy wektor ruchu wrzeciona z³o¿¹ siê maksymalnie 3 ruchy w osi xyz.
	na ka¿de przerwanie tc0 musi zostaæ wykonany krok w osi wiod¹cej i ewentualnie po kroku w osiach mniejszych

	czyli w przerwaniu tc0 mo¿na mieæ ju¿ ustalone wszystko:
	w jakiej osi zrobic krok i w jakim kierunku. mo¿na to zapisac w jednym bajcie:



*/


void delay(volatile uint32_t t){
	while(t--){};
};

int main(void)
{
    /* Initialize the SAM system */

	sysclk_init();

	board_init();

	pio_configure(PIOC, PIO_OUTPUT_0, PIO_PC8, PIO_PULLUP);

	pio_configure(PIOA, PIO_OUTPUT_0, PIO_PA2, PIO_PULLUP);

	pio_configure(PIOA, PIO_OUTPUT_0, PIO_PA17, PIO_PULLUP);

	pio_configure(PIOA, PIO_OUTPUT_0, PIO_PA30, PIO_PULLUP);

	fpu_enable();

	irq_initialize_vectors();

	irq_register_handler(UART4_IRQn, 3);	// -> serial uart receive

	irq_register_handler(TC0_IRQn, 1);
	irq_register_handler(TC1_IRQn, 2);

	Enable_global_interrupt();


	serial.InterruptEnable_RX();
	serial.write("szymon\r\n");

	tracker.set_accelerate(50000);
	tracker.set_target_speed(400);
	tracker.set_speed(300);

    while (1)
    {

		delay(0x6FFFFFF);
		
		tracker.set_target_speed(140000);
		
		delay(0x2FFFFFF);
		
		tracker.set_target_speed(50);
		

    };
};