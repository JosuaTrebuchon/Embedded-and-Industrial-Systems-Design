#include "motor_controller.h"

#define F_CPU 84000000L

P1000_DATA P1000_data;
pidData_t pid;

void slider_open_loop()
{
	//printf("pos %d\n", *pos);
	if (P1000_data.left_slider < 128)
	{
		//CODR = Clear Output Data Register
		PIOD -> PIO_CODR |= (0x1 << 10);
		DACC->DACC_CDR = 0x9FF;
	}
	
	else
	{
		//SODR = Set Output Data Register
		PIOD -> PIO_SODR |= (0x1 << 10);//&= ~(0x200);
		DACC->DACC_CDR = 0x9FF;
	}
}

/*
void delay_20ms(void) {
	uint16_t t;
	for (t = 0; t < F_CPU/4; t++)
	__asm__ volatile("nop\n\t"); // busy wait
}*/

void Delay(int num)

{
	volatile float f = 1.0f;

	for (volatile int i = 0; i < 1024 * num; ++i )

	f *= 1.1f;
}

uint16_t read_decoder()
{
	uint16_t encoder = 0;
	
	/* Clearing the not OE (Encoder output enable) */ 
	PIOD->PIO_CODR |= (0x1 << 0); 
	
	/* Setting SEL low to output high byte */
	PIOD->PIO_CODR |= (0x1 << 2);
	
	Delay(20);//delay_20ms();// for(int i = 0; i < 1680000; i++); // _delay_ms(20); change this
	
	encoder = (((PIOC->PIO_PDSR && MJ2_DATA_Msk) >> 1) << 8);
	
	/* Setting SEL high to output low byte */
	PIOD->PIO_SODR |= (0x1 << 2);
	
	Delay(20);// for(int i = 0; i < 1680000; i++); // _delay_ms(20);
	
	encoder += ((PIOC->PIO_PDSR && MJ2_DATA_Msk) >> 1);
	
	/* Setting the not OE (Encoder output enable) high */ 
	PIOD->PIO_SODR |= (0x1 << 0); 
	
	
	return encoder;
}


void move_to_setpoint()
{	
	/*percentage of slider*/
	uint16_t setPoint = 100*(P1000_data.left_slider/255);

	int16_t measured_value = read_decoder();
	int16_t motor_input = pid_Controller(setPoint, measured_value, *pid);

	/*
		set register to motor_value? 
		PIOD -> PIO_CODR |= (0x1 << 10);
		DACC->DACC_CDR = 0x9FF;
	
	*/


}