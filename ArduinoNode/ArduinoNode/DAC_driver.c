#include "DAC_driver.h"

void DACC_init(void)
{
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	/*Reset DACC*/
	DACC->DACC_CR |= DACC_CR_SWRST;
	
	/*Select CH1*/
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	
	/*Enable CH1*/
	DACC ->DACC_CHER |= DACC_CHER_CH1;
	

}

void motor_init()
{
	/* Enable PIOD clock */
	//PMC->PMC_PCER0 |= PMC_PCER0_PID14;
	
	/*Enable MJ1 pins*/
	PIOD -> PIO_PER |= 0x607;	
	
	/*Enable MJ1 pins as outputs*/
	PIOD -> PIO_OER |= 0x607;
	
	// Input filters ?
	
	/*Enable MJ1 pins as outputs*/
	//207 = R (to motor)
	//607 = L
	//PIOD -> PIO_CODR |= (0x1 << 1);
	PIOD -> PIO_SODR |= (0x1 << 10) | (0x1 << 9) | (0x1 << 2) | (0x1 << 1) | (0x1 << 0);//0x607;
	
	PIOD->PIO_ABSR |= 0x607;
	
	// Motor or encoder reset ?
	
}


void motor_read_init()
{
	//PMC->PMC_PCR |= (0x1 << 28) | (0x1 << 12) | (0xd << 0);
	/* Enable PIOC clock */
	//PMC->PMC_PCER0 |= PMC_PCER0_PID13;
	
	/*Enable MJ2 pins (C1 to C8)*/
	PIOC -> PIO_PER |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) | (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);
	
 	/*Disable MJ2 pins as output */
 	PIOC -> PIO_ODR |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) | (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);

	PIOC->PIO_ABSR |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) | (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1); 

	/* Enable Clock Glitch Filter */
	//PIOC->PIO_IFER |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) | (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1); 
	PIOC->PIO_PUDR |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) | (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);
}