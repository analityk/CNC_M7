#include <tracker.h>
#include <ClassSerial.h>
#include <vector.h>

Tracker tracker;
uint32_t ticks = 0;
uint8_t volatile speed_change_lock = 0;

tc0_data_t step_buffer[1000];
uint16_t step_buffer_offset = 0;

int32_t actual_x_position = 0;
int32_t actual_y_position = 0;
int32_t actual_z_position = 0;

uint16_t volatile step_buffer_cnt = 0;
uint16_t volatile step_executed = 0;

void Tracker::stop(void)
{
	this->lock = 1;
};

void Tracker::start(void)
{
	this->lock = 0;
};

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

uint32_t Tracker::line_xy(Vector* start, Vector* end)
{

	float vlen = Vector::Length(start, end);
	uint32_t vector_step_cnt = (uint32_t)vlen;

	if(vector_step_cnt > 1000){
		serial.write("have to split vectors\r\n");
	};

	step_buffer_offset = 0;
	step_executed = 0;

	int32_t d, dx, dy, ai, bi, xi, yi;
	int32_t x = start->x;
	int32_t y = start->y;

	if(start->x < end->x){
		xi = 1;
		dx = end->x - start->x;
	}else{
		xi = -1;
		dx = start->x - end->x;
	};

	if(start->y < end->y){
		yi = 1;
		dy = end->y - start->y;
	}else{
		yi = -1;
		dy = start->y - end->y;
	};

	if(dx > dy){
		ai = (dy - dx) * 2;
		bi = dy * 2;
		d = bi - dx;
		while(x != end->x){
			if(d >= 0){
				x += xi;
				y += yi;
				d += ai;
			}else{
				d += bi;
				x += xi;
			};
			step_xy(&x, &y);
		};
	}else{
		ai = ( dx - dy ) * 2;
		bi = dx * 2;
		d = bi - dy;
		while(y != end->y){
			if(d >= 0){
				x += xi;
				y += yi;
				d += ai;
			}else{
				d += bi;
				y += yi;
			};
			step_xy(&x, &y);
		};
	};

	step_buffer_cnt = step_buffer_offset - 1;
	return step_buffer_cnt;
};

void Tracker::step(int8_t x, int8_t y, int8_t z)
{

};

void Tracker::step_xy(int32_t* x, int32_t* y)
{
	int32_t dx = *x - actual_x_position;
	int32_t dy = *y - actual_y_position;

	//char r[80];
	//sprintf(r, "x %d y%d px %d py %d dx %d dy %d\r\n",*x, *y, actual_x_position, actual_y_position, dx, dy);
//
	//serial.write(r);

	if(dx > 0){
		step_buffer[step_buffer_offset].dir_x = 1;
		step_buffer[step_buffer_offset].step_x = 1;
		actual_x_position++;
	};

	if(dx < 0){
		step_buffer[step_buffer_offset].dir_x = 0;
		step_buffer[step_buffer_offset].step_x = 1;
		actual_x_position--;
	};

	if(dx == 0){
		step_buffer[step_buffer_offset].dir_x = 0;
		step_buffer[step_buffer_offset].step_x = 0;
	};

	if(dy > 0){
		step_buffer[step_buffer_offset].dir_y = 1;
		step_buffer[step_buffer_offset].step_y = 1;
		actual_y_position++;
	};

	if(dy < 0){
		step_buffer[step_buffer_offset].dir_y = 0;
		step_buffer[step_buffer_offset].step_y = 1;
		actual_y_position--;
	};

	if(dy == 0){
		step_buffer[step_buffer_offset].dir_y = 0;
		step_buffer[step_buffer_offset].step_y = 0;
	};

	step_buffer_offset++;
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

	if( tracker.actual_speed >= 300){
		REG_TC0_CMR0 = (MCK_8) | (1<<15) | (1<<14);
		REG_TC0_RC0 = (uint16_t)(MCK_DIV_8 / (tracker.actual_speed * 2));
		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
	};

	if( (tracker.actual_speed < 300) && (tracker.actual_speed >= 75) ){
		REG_TC0_CMR0 = (MCK_32) | (1<<15) | (1<<14);
		REG_TC0_RC0 = (MCK_DIV_32 / (tracker.actual_speed * 2));
		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
	};

	if( (tracker.actual_speed < 75) && (tracker.actual_speed >= 20) ){
		REG_TC0_CMR0 = (MCK_128) | (1<<15) | (1<<14);
		REG_TC0_RC0 = (MCK_DIV_128 / (tracker.actual_speed * 2));
		REG_TC0_IER0 = (1<<4);
		REG_TC0_CCR0 = 5;
	};


	// czy są w ogóle jakieś kroki do zrobienia?
	uint16_t volatile stex = step_buffer_cnt - step_executed;

	if( (set_clr_phase == 1) && (tracker.lock == 0) && (stex > 0) ){
		set_clr_phase = 0;

		if(step_buffer[step_executed].step_x == 1){

			if(step_buffer[step_executed].dir_x == 1){
				tracker.motor_x.DirClr();
			}else{
				tracker.motor_x.DirSet();
			};

			tracker.motor_x.StepClr();
		};

		if(step_buffer[step_executed].step_y == 1){

			if(step_buffer[step_executed].dir_y == 1){
				tracker.motor_y.DirClr();
			}else{
				tracker.motor_y.DirSet();
			};

			tracker.motor_y.StepClr();
		};

		if(step_buffer[step_executed].step_z == 1){

			if(step_buffer[step_executed].dir_z == 1){
				tracker.motor_z.DirClr();
			}else{
				tracker.motor_z.DirSet();
			};

			tracker.motor_z.StepClr();
		};

		step_executed++;

	}else{
		set_clr_phase = 1;

		tracker.motor_x.StepSet();
		tracker.motor_y.StepSet();
		tracker.motor_z.StepSet();
	};

};

// accelerate and decelerate
ISR( TC1_Handler ){
	uint32_t volatile tc0_sr1 = REG_TC0_SR1;
	UNUSED(tc0_sr1);

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