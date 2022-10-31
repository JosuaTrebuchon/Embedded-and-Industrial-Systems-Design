#include "pwm_driver.h"

void peripheral_init_pwm(){
	
	
	// PIOC->PIO_PER |= ((0x1 << 19));
	
	PIOC ->  PIO_PDR |= PIO_PDR_P19;
	
	// Using peripheral B of PIOC19
	PIOC ->PIO_ABSR |= PIO_ABSR_P19;
	
	/* Enable clock for the PWM peripheral */
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
}

void pwm_init()
{

	PWM->PWM_WPCR |= PWM_WPCR_WPCMD(0);
	PWM->PWM_WPCR |= PWM_WPCR_WPRG3;
	PWM->PWM_ENA |= PWM_ENA_CHID5;
	PWM->PWM_CH_NUM[5].PWM_CMR |=PWM_CMR_CPRE_CLKB;
	PWM->PWM_CH_NUM[5].PWM_CMR |=~(PWM_CMR_CALG | PWM_CMR_CPOL);
	
	PWM->PWM_CLK |= PWM_CLK_DIVA(0);
	PWM->PWM_CLK |= PWM_CLK_DIVB(42);
	PWM->PWM_CLK |= PWM_CLK_PREB(0);
	
	int PWM_period_tick=40000;
	int PWM_dutycycle_tick=3000; //MIN 1800 CENTER:3000 MAX:4200
	PWM->PWM_CH_NUM[5].PWM_CPRD |= PWM_period_tick;
	PWM->PWM_CH_NUM[5].PWM_CDTY |= PWM_dutycycle_tick;
	
	//PWM->PWM_CH_NUM[5].PWM_CDTYUPD |= PWM_dutycycle_tick_NEW; example
}

void pwm_duty_update(int PWM_dutycycle_tick_NEW)
{
	if(1800<=PWM_dutycycle_tick_NEW && PWM_dutycycle_tick_NEW<=4200)
	{
		PWM->PWM_CH_NUM[5].PWM_CDTYUPD |= PWM_dutycycle_tick_NEW;
	}
	else
	{
		printf("End of Range ");
	}
}

void joystick_input(void)
{
	CAN_MESSAGE can_msg;
	can_receive(&can_msg, 0);
	int pwm_dutycycle = (int)(PWM->PWM_CH_NUM[5].PWM_CDTY);
	if(can_msg.id==1){
		if (can_msg.data[0]==0)
		{
			pwm_dutycycle+=50;
			printf("increased duty cycle to %d \n",pwm_dutycycle);
		}
		if (can_msg.data[0]==1){
			pwm_dutycycle-=50;
			printf("decreased duty cycle to %d \n",pwm_dutycycle);
		}
		pwm_duty_update(pwm_dutycycle);
	}
}