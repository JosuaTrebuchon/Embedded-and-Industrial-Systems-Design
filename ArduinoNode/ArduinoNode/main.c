/*
 * ArduinoNode.c
 *
 * Created: 12.10.2022 12:12:14
 * Author : bjornolo
 */ 


#include "sam.h"


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
    /* Initialize the SAM system */
    SystemInit();

    /* Enables pin A19 and A20 */
	PIOA->PIO_PER |= ((0x1 << 20) | (0x1 << 19));
    
	/* Enable the output on the I/O line */
    PIOA->PIO_OER |= ((0x1 << 20) | (0x1 << 19));
	
	while(1)
	{
		toggleLED1();
		toggleLED2();
	}

}
