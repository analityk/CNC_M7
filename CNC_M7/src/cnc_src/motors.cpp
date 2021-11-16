#include <motors.h>

void Motors::DirSet(void)
{
	pio_set(motor_dir_pio, motor_dir_pin_mask);
};

void Motors::DirClr(void)
{
	pio_clear(motor_dir_pio, motor_dir_pin_mask);
};

void Motors::StepSet(void)
{
	pio_set(motor_step_pio, motor_step_pin_mask);
};

void Motors::StepClr(void)
{
	pio_clear(motor_step_pio, motor_step_pin_mask);
};

void Motors::EnSet(void)
{
	pio_set(motor_enable_pio, motor_enable_pin_maks);
};

void Motors::EnClr(void)
{
	pio_clear(motor_enable_pio, motor_enable_pin_maks);
};

