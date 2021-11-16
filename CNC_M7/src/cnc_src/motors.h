#ifndef motors_h__
#define motors_h__

#include <asf.h>


class Motors{
	public:
	Pio* motor_dir_pio;
	uint32_t motor_dir_pin_mask;
	Pio* motor_step_pio;
	uint32_t motor_step_pin_mask;
	Pio* motor_enable_pio;
	uint32_t motor_enable_pin_maks;

	Motors(Pio* DirPio, uint32_t DirPinMask, Pio* StepPio, uint32_t StepPinMask, Pio* EnablePio, uint32_t EnablePinMaks):
	motor_dir_pio(DirPio),
	motor_dir_pin_mask(DirPinMask),

	motor_step_pio(StepPio),
	motor_step_pin_mask(StepPinMask),

	motor_enable_pio(EnablePio),
	motor_enable_pin_maks(EnablePinMaks)
	{
		pio_configure(motor_dir_pio,	PIO_OUTPUT_0, motor_dir_pin_mask,	 PIO_DEFAULT);
		pio_configure(motor_step_pio,	PIO_OUTPUT_0, motor_step_pin_mask,	 PIO_DEFAULT);
		pio_configure(motor_enable_pio, PIO_OUTPUT_0, motor_enable_pin_maks, PIO_DEFAULT);
		DirClr();
		StepClr();
	};

	void DirSet(void);
	void DirClr(void);

	void StepSet(void);
	void StepClr(void);

	void EnSet(void);
	void EnClr(void);
};

#endif // motors_h__