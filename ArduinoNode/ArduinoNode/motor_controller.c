#include "motor_controller.h"

P1000_DATA P1000_data;

void slider_open_loop()
{
	//printf("pos %d\n", *pos);
	if (P1000_data.left_slider < 128)
	{
		PIOD -> PIO_CODR |= (0x1 << 10);
		DACC->DACC_CDR = 0x9FF;
	}
	
	else
	{
		PIOD -> PIO_SODR |= (0x1 << 10);//&= ~(0x200);
		DACC->DACC_CDR = 0x9FF;
	}
}

uint16_t read_decoder()
{
	uint16_t encoder = 0;
	
	/* Clearing the not OE (Encoder output enable) */ 
	PIOD->PIO_CODR |= (0x1 << 0); 
	
	/* Setting SEL low to output high byte */
	PIOD->PIO_CODR |= (0x1 << 2);
	
	for(int i = 0; i < 1680000; i++); // _delay_ms(20);
	
	encoder = (((PIOC->PIO_PDSR && MJ2_DATA_Msk) >> 1) << 8);
	
	/* Setting SEL high to output low byte */
	PIOD->PIO_SODR |= (0x1 << 2);
	
	for(int i = 0; i < 1680000; i++); // _delay_ms(20);
	
	encoder += ((PIOC->PIO_PDSR && MJ2_DATA_Msk) >> 1);
	
	
	/* Setting the not OE (Encoder output enable) high */ 
	PIOD->PIO_SODR |= (0x1 << 0); 
	
	
	return encoder;
}