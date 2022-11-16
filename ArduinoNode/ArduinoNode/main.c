/*
 * ArduinoNode.c
 *
 * Created: 12.10.2022 12:12:14
 * Author : bjornolo
 */ 

#define F_CPU 84000000L
//#define __SAM3X8E__

#include "sam.h"
#include "printf-stdarg.h"
#include "uart.h"
#include "can_interrupt.h"
#include "can_controller.h"
#include "pwm_driver.h"
#include "IR_driver.h"
#include "adc.h"
#include "DAC_driver.h"
#include "motor_controller.h"
#include "pid.h"

extern P1000_DATA P1000_data;
extern pidData_t pid;

void LED_init(void);
void toggleLED1(void);
void toggleLED2(void);

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	configure_uart();
	uint32_t can_br = 0x00290165;//0x10165;
	
	/*UNCOMMENT FOR CAN*/
	can_init_def_tx_rx_mb(can_br);
		
	/*disable watchdog*/
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	peripheral_init_pwm();

	pwm_init();
	
	peripheral_init_adc();
	ADC_init();
	DACC_init();
	motor_init();
	solenoid_init();

	int score = 0;
	int no_goal_counter = 0;

	int16_t p_factor = 20; //45 P only stable START 100
	int16_t i_factor = 1; 
	int16_t d_factor = 0;

	pid_Init(p_factor, i_factor, d_factor, &pid);	
	
	init_motor_position();
	//reset_encoder();
		//PIOD -> PIO_SODR |= (0x1 << 10);// Set direction to right
	
	//volatile int encoder = 0;
	while(1)
	{	
		check_for_score(&score, &no_goal_counter);
		joystick_input();
		//printf("joystick %d left %d right %d \n", P1000_data.joystick, P1000_data.left_slider, P1000_data.right_slider);
		//printf("Value from the counter inside decoder = %d \n", encoder);
		
		move_to_setpoint();
		//printf(" Button: %d \n",P1000_data.joystick_button);
		if(P1000_data.joystick_button == 1)
		{

			solenoid_impulse();
		}
		
		
	}
}


void LED_init()
{
	/* Enables pin A19 and A20 */
	PIOA->PIO_PER |= ((0x1 << 20) | (0x1 << 19));
		
	/* Enable the output on the I/O line */
	PIOA->PIO_OER |= ((0x1 << 20) | (0x1 << 19));
}

void toggleLED1()
{

	if(((PIOA->PIO_ODSR & 0x00040000) >> 19) == 0x1)
	{
		/* Setting output value to 0 */
		// PIOA->PIO_SODR &= ~0x00040000;
		PIOA->PIO_CODR |= (0x1 << 19);
	}
	else
	{
		/* Setting output value to 1 */
		PIOA->PIO_SODR |= (0x1 << 19);
	}
}

void toggleLED2()
{

	if(((PIOA->PIO_ODSR & 0x00050000) >> 20) == 0x1)
	{
		/* Setting output value to 0 */
		// PIOA->PIO_SODR &= ~0x00050000;
		PIOA->PIO_CODR |= (0x1 << 20);
	}
	else
	{
		/* Setting output value to 1 */
		PIOA->PIO_SODR |= (0x1 << 20);
	}
}