#include "ADC_driver.h"


void ADC_init(void)
{
	//set clock out on MC
	set_bit(DDRD, DDD5);
	set_bit(DDRD, DDD6); /* Enable WR output signal */
	set_bit(DDRD, DDD7); /* Enable RD output signal */
	
	clear_bit(DDRE, DDE0); /* Set pin PE0 as INPUT to use the INT2 Interrupt for BUSY signal from ADC */
	
	set_bit(EMCUCR, ISC2); /* Trigger interrupt on rising edge */
	set_bit(GICR, INT2); /* Enable INT2 interrupt */ 
}

void ADC_read(void)
{
	float t_BRD = 50E-6;
	float t_RDL = 100E-5;
	float t_RDH = 180E-6;
	

	int channels = 4;
	
	uint8_t ADC_data [4]= {0,0,0,0};
	
	_delay_ms(t_BRD);
	
	for(int i = 0; i<channels;++i)
	{
		ADC_data [i] = xmem_read(0x1700);
		_delay_ms(t_RDL+t_RDH);
		
	
	}
	printf( "value stored at ADC_data[%d] is 0x%08x\n", 1, ADC_data [1]);
	
}