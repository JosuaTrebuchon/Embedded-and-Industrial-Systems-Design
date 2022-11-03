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

extern P1000_DATA P1000_data;

void delay(void) {
	uint16_t t;
	for (t = 0; t < F_CPU/4; t++)
	__asm__ volatile("nop\n\t"); // busy wait
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

int main(void)
{


	

    /* Enables pin A19 and A20 */
	PIOA->PIO_PER |= ((0x1 << 20) | (0x1 << 19));
    
	/* Enable the output on the I/O line */
    PIOA->PIO_OER |= ((0x1 << 20) | (0x1 << 19));
	    /* Initialize the SAM system */
    SystemInit();
	
	configure_uart();
	uint32_t can_br = 0x00290165;//0x10165;
		
	can_init_def_tx_rx_mb(can_br);
		
	/*disable watchdog*/
	WDT->WDT_MR = WDT_MR_WDDIS;
	/*
	CAN_MESSAGE can_msg;
	while(1){
			can_receive(&can_msg, 0);
			
			printf("message data read %c length %d ID %d\n", can_msg.data[0], can_msg.data_length, can_msg.id);
			
			
	}
	*/
	
	peripheral_init_pwm();

	pwm_init();
	
	peripheral_init_adc();
	ADC_init();
	DACC_init();
	motor_init();
	motor_read_init();
	int score = 0;
	int no_goal_counter = 0;
	
// 	PIOD -> PIO_CODR |= (0x1 << 10);
// 	DACC->DACC_CDR = 0x9FF;
	while(1)
	{
		check_for_score(&score, &no_goal_counter);
		slider_open_loop();
		joystick_input();
		//printf("joystick %d left %d right %d \n", P1000_data.joystick, P1000_data.left_slider, P1000_data.right_slider);
	
		printf("Value from the counter inside decoder = %d \n", read_decoder());
		printf("PDSR %d\n",(int)(PIOC->PIO_PDSR) );
	}
}
