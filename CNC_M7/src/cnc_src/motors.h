#ifndef motors_h__
#define motors_h__

#include <asf.h>


class Motors{
public:
	Pio* motor_port_dir_a;
	uint32_t motor_pin_dir_a;
	Pio* motor_port_step_a;
	uint32_t motor_pin_step_a;

	//uint32_t* motor_port_dir_b;
	//uint32_t motor_pin_dir_b;
	//uint32_t* motor_port_step_b;
	//uint32_t motor_pin_step_b;

	Motors(){};

	Motors(Pio* PortDir, uint32_t PinDir, Pio* PortStep, uint32_t PinStep):
		motor_port_dir_a(PortDir),
		motor_port_step_a(PortStep),
		motor_pin_dir_a(PinDir),
		motor_pin_step_a(PinStep)
	{
		DirClr();
		StepClr();
	};

	void DirPortPinSet(Pio* t, uint32_t p);
	void StepPorPintSet(Pio* t, uint32_t p);

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

#endif // motors_h__
