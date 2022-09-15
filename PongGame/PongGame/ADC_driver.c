#include "ADC_driver.h"


void ADC_init(void)
{
	//set clock out on MC
	set_bit(DDRD, DDD5);
}