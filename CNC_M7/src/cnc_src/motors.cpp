#include <motors.h>

void Motors::DirPortPinSet(Pio* t, uint32_t p)
{
	this->motor_port_dir_a = t;
	this->motor_pin_dir_a = p;
}

void Motors::StepPorPintSet(Pio* t, uint32_t p)
{
	this->motor_port_step_a = t;
	this->motor_pin_step_a = p;
}

void Motors::DirSet(void)
{
	pio_set(motor_port_dir_a, motor_pin_dir_a);
}

void Motors::DirClr(void)
{
	pio_clear(motor_port_dir_a, motor_pin_dir_a);
}

void Motors::StepSet(void)
{
	pio_set(motor_port_step_a, motor_pin_step_a);
}

void Motors::StepClr(void)
{
	pio_clear(motor_port_step_a, motor_pin_step_a);
}
