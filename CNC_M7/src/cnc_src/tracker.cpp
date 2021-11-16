#include <tracker.h>

Tracker tracker;

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

    // Driving axis is X-axis
	//tspeed.Start();
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
	//tspeed.Stop();
};

void Tracker::step(int8_t x, int8_t y, int8_t z)
{
	while(tracker.lock == 1){};

	tracker.lock = 1;

	if(x > 0){
		motor_x.DirClr();
		motor_x.StepClr();
	};
	if(x < 0){
		motor_x.DirSet();
		motor_x.StepClr();
	};

	if(y > 0){
		motor_y.DirClr();
		motor_y.StepClr();
	};
	if(y < 0){
		motor_y.DirSet();
		motor_y.StepClr();
	};

	if( z > 0){
		motor_z.DirClr();
		motor_z.StepClr();
	};
	if(z < 0){
		motor_z.DirSet();
		motor_z.StepClr();
	};
};

uint32_t Tracker::set_speed(uint32_t step_per_second)
{
	if(step_per_second > 300){
		// div_8
		// stop timer
		REG_TC0_CCR0 = 1;
		// set mck div=8, interrupt on rc compare, wave mode
		REG_TC0_CMR0 = (MCK_8) | (1<<15) | (1<<14);

		// real speed in step per second
		tracker.step_time = (MCK_DIV_8 / (step_per_second * 2));

		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
		return 8;
	};

	if(step_per_second > 75){
		REG_TC0_CCR0 = 1;
		REG_TC0_CMR0 = (MCK_32) | (1<<15) | (1<<14);

		tracker.step_time = (MCK_DIV_32 / (step_per_second * 2));

		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
		return 32;
	};

	if(step_per_second > 20){
		REG_TC0_CCR0 = 1;
		REG_TC0_CMR0 = (MCK_128) | (1<<15) | (1<<14);

		tracker.step_time = (MCK_DIV_128 / (step_per_second * 2));

		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
		return 128;
	};

	return 0;
};

uint32_t Tracker::set_accelerate(uint32_t accelerate)
{
	tracker.target_speed = tracker.accel;
	if( tracker.actual_speed < tracker.target_speed ){
		tracker.acl_phase = 1;
	};
	if( tracker.actual_speed > tracker.target_speed ){
		tracker.dcl_phase = 1;
	};
};


uint8_t volatile testled = 0;
// motors speed
ISR( TC0_Handler ){
	uint32_t volatile tc0_sr0 = REG_TC0_SR0;
	UNUSED(tc0_sr0);
	tracker.lock = 0;
	REG_TC0_RC0 = (uint16_t)(tracker.step_time);

		if(testled == 1){
			pio_set(PIOC, PIO_PC8);
			testled = 0;
		}else{
			pio_clear(PIOC, PIO_PC8);
			testled = 1;
		};
};

// accelerate and decelerate
ISR( TC1_Handler ){
	uint32_t volatile tc0_sr1 = REG_TC0_SR1;

	if(tc0_sr1 & (1<<2)){ // set all motor io
		pio_set(PIOA, PIO_PA19);
	};

	if(tc0_sr1 & (1<<4)){




		if( tracker.acl_phase == 1 ){
			if( tracker.target_speed > tracker.actual_speed ){
				tracker.actual_speed++;
				tracker.set_speed(tracker.actual_speed);
				REG_TC0_RC1 = tracker.accel;	//accelerate;
				REG_TC0_RA1 = tracker.accel / 2;
			}else{
				tracker.acl_phase = 0;
				REG_TC0_RC1 = tracker.accel;
				REG_TC0_RA1 = tracker.accel / 2;
			};
		};

		if( tracker.dcl_phase == 1 ){
			if( tracker.actual_speed > tracker.target_speed ){
				tracker.actual_speed--;
				tracker.set_speed(tracker.actual_speed);
				REG_TC0_RC1 = tracker.accel;	//decelerate;
				REG_TC0_RA1 = tracker.accel / 2;
			}else{
				tracker.dcl_phase = 0;
				REG_TC0_RC1 = tracker.accel;
				REG_TC0_RA1 = tracker.accel / 2;
			};
		};


	};

};