#include "pwm_driver.h"

void peripheral_init(){
	
	
	// PIOC->PIO_PER |= ((0x1 << 19));
	
	PIOC ->  PIO_PDR |= PIO_PDR_P19;
	
	// Using peripheral B of PIOC19
	PIOC ->PIO_ABSR |= PIO_ABSR_P19;
	
	/* Enable clock for the PWM peripheral */
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
}

void pwm_init()
{
	//prescaler 512
	//cprd 8,203,125 0x7D2B75
	PWM->PWM_WPCR |= PWM_WPCR_WPCMD(0);
	PWM->PWM_WPCR |= PWM_WPCR_WPRG3;
	
	PWM->PWM_CLK |= PWM_CMR_CPRE_CLKB;
	PWM->PWM_CLK |= PWM_CLK_PREB(PWM_CMR_CPRE_MCK_DIV_512);
	
	PWM->PWM_CH_NUM[5].PWM_CPRDUPD |= 0x7D2B75;
	PWM->PWM_CH_NUM[5].PWM_CPRD |= 0x7D2B75;
	PWM->PWM_CH_NUM[5].PWM_CDTY |= (int) (0x2B75 / 2);
	
	PWM->PWM_ENA |= PWM_ENA_CHID5; 
	
	
}
