/*
 * ArduinoNode.c
 *
 * Created: 12.10.2022 12:12:14
 * Author : bjornolo
 */ 


#include "sam.h"
#include "printf-stdarg.h"
#include "uart.h"
#include "can_interrupt.h"
#include "can_controller.h"

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

	//CAN0_Handler();
	
	/*
	while(1)
	{
		toggleLED1();
		toggleLED2();
		
		printf("success!");
	}
	*/
}
