#ifndef pinout_h__
#define pinout_h__

#include <asf.h>


class MotorPins{
public:
	uint32_t* motor_port_dir_a;
	uint32_t motor_pin_dir_a;
	uint32_t* motor_port_step_a;
	uint32_t motor_pin_step_a;

	//uint32_t* motor_port_dir_b;
	//uint32_t motor_pin_dir_b;
	//uint32_t* motor_port_step_b;
	//uint32_t motor_pin_step_b;

	MotorPins(){};

	void DirPortPinSet(uint32_t* t, uint32_t p);
	void StepPorPintSet(uint32_t* t, uint32_t p);

	void DirSet(void);
	void DirClr(void);

	void StepSet(void);
	void StepClr(void);

/*
	// need be implemented for differential signals
	void DirPort_A_Set(uint32_t* t);
	void DirPort_B_Set(uint32_t* t);

	void StepPort_A_Set(uint32_t* t);
	void StepPort_B_Set(uint32_t* t);

	void DirPin_A_Set(uint32_t t);
	void DirPin_B_Set(uint32_t t);

	void StepPin_A_Set(uint32_t t);
	void StepPin_B_Set(uint32_t t);
*/

};


#endif // pinout_h__
