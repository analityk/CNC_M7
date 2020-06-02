#ifndef tracker_h__
#define tracker_h__

#include <asf.h>
#include <vector.h>

class Tracker{
public:

	int32_t delay_ms_irq;

	uint32_t actual_speed;
	uint32_t target_speed;

	uint8_t acl_phase;
	uint8_t dcl_phase;

	Vector abs_pos;

	uint32_t step_time;

	uint32_t accel; // = 2000

	Tracker():abs_pos(1, 1, 1){};

	void line_3d(Vector* start, Vector* stop);
	void step(int8_t x, int8_t y, int8_t z);

	//void line_2d(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
	//void set_speed(int32_t step_per_second);
	//void set_speed_acc(int32_t step_per_second);
	//void reset_coordinates(void);

};

#endif // tracker_h__
