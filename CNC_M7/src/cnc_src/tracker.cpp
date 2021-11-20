#include <tracker.h>
#include <ClassSerial.h>

Tracker tracker;
uint32_t ticks = 0;
uint8_t volatile speed_change_lock = 0;

typedef struct tc0_data{
	uint8_t step_x	:	1;
	uint8_t step_y	:	1;
	uint8_t step_z	:	1;
	uint8_t dir_x	:	1;
	uint8_t dir_y	:	1;
	uint8_t dir_z	:	1;
}tc0_data_t;

tc0_data_t tco = { .step_x=1, .step_y=0, .step_z=0, .dir_x=0, .dir_y=0, .dir_z=0 };

void Tracker::line_3d(Vector* start, Vector* stop)
{
	int32_t dx = abs(stop->x - start->x);
    int32_t dy = abs(stop->y - start->y);
    int32_t dz = abs(stop->z - start->z);

	int8_t xs = 0;
	int8_t ys = 0;
	int8_t zs = 0;

    if(stop->x > start->x){
		xs = 1;
	}else{
		xs = -1;
	};

    if(stop->y > start->y){
        ys = 1;
	}else{
		ys = -1;
	};

	if(stop->z > start->z){
        zs = 1;
    }else{
        zs = -1;
	};


    if(dx >= dy && dx >= dz){
        int32_t p1 = 2 * dy - dx;
        int32_t p2 = 2 * dz - dx;

		while(start->x != stop->x){
            start->x += xs;
            if(p1 >= 0){
                start->y += ys;
                p1 -= 2 * dx;
			};
            if(p2 >= 0){
                start->z += zs;
                p2 -= 2 * dx;
			};
            p1 += 2 * dy;
            p2 += 2 * dz;

			int8_t mdx = abs_pos.x - start->x;
			int8_t mdy = abs_pos.y - start->y;
			int8_t mdz = abs_pos.z - start->z;

			tracker.step(mdx, mdy, mdz);

			abs_pos.x -= mdx;
			abs_pos.y -= mdy;
			abs_pos.z -= mdz;

		};
	}else{
		if(dy >= dx && dy >= dz){
			int32_t p1 = 2 * dx - dy;
			int32_t p2 = 2 * dz - dy;

			while(start->y != stop->y){
				start->y += ys;
				if(p1 >= 0){
					start->x += xs;
					p1 -= 2 * dy;
				};
				if(p2 >= 0){
					start->z += zs;
					p2 -= 2 * dy;
				};
				p1 += 2 * dx;
				p2 += 2 * dz;

				int8_t mdx = abs_pos.x - start->x;
				int8_t mdy = abs_pos.y - start->y;
				int8_t mdz = abs_pos.z - start->z;

				tracker.step(mdx, mdy, mdz);

				abs_pos.x -= mdx;
				abs_pos.y -= mdy;
				abs_pos.z -= mdz;

			};
		}else{
			int32_t p1 = 2 * dy - dz;
			int32_t p2 = 2 * dx - dz;

			while(start->z != stop->z){
				start->z += zs;
				if(p1 >= 0){
					start->y += ys;
					p1 -= 2 * dz;
				};
				if(p2 >= 0){
					start->x += xs;
					p2 -= 2 * dz;
				};
				p1 += 2 * dy;
				p2 += 2 * dx;

				int8_t mdx = abs_pos.x - start->x;
				int8_t mdy = abs_pos.y - start->y;
				int8_t mdz = abs_pos.z - start->z;

				tracker.step(mdx, mdy, mdz);

				abs_pos.x -= mdx;
				abs_pos.y -= mdy;
				abs_pos.z -= mdz;

			};
		};

	};

};

void Tracker::step(int8_t x, int8_t y, int8_t z)
{
	while(tracker.lock == 1){};

	tracker.lock = 1;
};

uint32_t Tracker::set_speed(uint32_t step_per_second)
{

	tracker.actual_speed = step_per_second;
	return 0;
};

uint32_t Tracker::set_target_speed(uint32_t step_per_second)
{
	tracker.target_speed = step_per_second;
};

uint32_t Tracker::set_accelerate(uint32_t accelerate)
{
	tracker.accel = accelerate;

	if(accelerate > 300){
		// div_8
		// stop timer
		REG_TC0_CCR1 = 1;
		// set mck div=8, interrupt on rc compare, wave mode
		REG_TC0_CMR1 = (MCK_8) | (1<<15) | (1<<14);

		// real speed in step per second
		tracker.accel = (MCK_DIV_8 / (accelerate * 2));

		REG_TC0_IER1 = (1<<4);
		REG_TC0_CCR1 = 5;
		return 8;
	};

	if(accelerate > 75){
		REG_TC0_CCR1 = 1;
		REG_TC0_CMR1 = (MCK_32) | (1<<15) | (1<<14);

		tracker.accel = (MCK_DIV_32 / (accelerate * 2));

		REG_TC0_IER1 = (1<<4);
		REG_TC0_CCR1 = 5;
		return 32;
	};

	if(accelerate > 20){
		REG_TC0_CCR1 = 1;
		REG_TC0_CMR1 = (MCK_128) | (1<<15) | (1<<14);

		tracker.accel = (MCK_DIV_128 / (accelerate * 2));

		REG_TC0_IER1 = (1<<4);
		REG_TC0_CCR1 = 5;
		return 128;
	};

	return 0;

};


uint8_t volatile set_clr_phase = 0;

// motors speed
ISR( TC0_Handler ){
	uint32_t volatile tc0_sr0 = REG_TC0_SR0;
	UNUSED(tc0_sr0);
	tracker.lock = 0;

	if(tracker.actual_speed > 300){
		// div_8
		// set mck div=8, interrupt on rc compare, wave mode
		REG_TC0_CMR0 = (MCK_8) | (1<<15) | (1<<14);

		// real speed in step per second
		REG_TC0_RC0 = (uint16_t)(MCK_DIV_8 / (tracker.actual_speed * 2));

		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
	};

	//if(tracker.actual_speed > 75){
		//REG_TC0_CMR0 = (MCK_32) | (1<<15) | (1<<14);
//
		//tracker.step_time = (MCK_DIV_32 / (tracker.actual_speed * 2));
//
		//REG_TC0_IER0 = (1<<4);
		//REG_TC0_CCR0 = 5;
	//};
//
	//if(tracker.actual_speed > 20){
		//REG_TC0_CMR0 = (MCK_128) | (1<<15) | (1<<14);
//
		//tracker.step_time = (MCK_DIV_128 / (tracker.actual_speed * 2));
//
		//REG_TC0_IER0 = (1<<4);
		//REG_TC0_CCR0 = 5;
	//};

	//REG_TC0_RC0 = (uint16_t)(tracker.step_time);
	
	ticks++;

	if(set_clr_phase == 1){
		set_clr_phase = 0;

		if(tco.step_x == 1){

			if(tco.dir_x == 1){
				tracker.motor_x.DirClr();
			}else{
				tracker.motor_x.DirSet();
			};

			tracker.motor_x.StepClr();
		};

		if(tco.step_y == 1){

			if(tco.dir_y == 1){
				tracker.motor_y.DirClr();
			}else{
				tracker.motor_y.DirSet();
			};

			tracker.motor_y.StepClr();
		};

		if(tco.step_z == 1){

			if(tco.dir_z == 1){
				tracker.motor_z.DirClr();
			}else{
				tracker.motor_z.DirSet();
			};

			tracker.motor_z.StepClr();
		};
	}else{
		set_clr_phase = 1;

		tracker.motor_x.StepSet();
		tracker.motor_y.StepSet();
		tracker.motor_z.StepSet();
	};

};

// accelerate and decelerate
uint8_t volatile ttt = 0;

ISR( TC1_Handler ){
	uint32_t volatile tc0_sr1 = REG_TC0_SR1;
	UNUSED(tc0_sr1);

	//if(ttt==0){
		//ttt=1;
		//pio_set(PIOA, PIO_PA2);
	//}else{
		//ttt=0;
		//pio_clear(PIOA, PIO_PA2);
	//};

	REG_TC0_RC1 = (uint16_t)tracker.accel;
	REG_TC0_RA1 = (uint16_t)tracker.accel / 2;

	if(tc0_sr1 & (1<<4)){

			if( tracker.target_speed > tracker.actual_speed ){
				tracker.actual_speed += 1;
				tracker.set_speed(tracker.actual_speed);
			};

			if( tracker.actual_speed > tracker.target_speed ){
				tracker.actual_speed -= 1;
				tracker.set_speed(tracker.actual_speed);
			};

	};

};