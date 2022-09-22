/*
 * p1000_driver.c
 *
 * Created: 22.09.2022 14:43:47
 *  Author: bjornolo
 */ 

#include "p1000_driver.h" 

int joystick_calibrate = 128;void joystick_analog_position(int* x_per, int* y_per, uint8_t* ADC_data)
{
	xmem_write(0x52, 0x1400);
	
	printf( "ADC_data[%d] = %d, ADC_data[%d] = %d\n", 0, (int)ADC_data [0],3, (int)ADC_data [3]);
	*x_per = ((ADC_data[0] - joystick_calibrate) / joystick_calibrate) *100; //fix this
	*y_per = ((ADC_data[3] - joystick_calibrate) / joystick_calibrate) *100; //fix this
	printf("%d\n",*x_per);
	printf("%d\n",*y_per);
	//printf("pos check ?\n");
}

pos_t pos_read(int* x_per, int* y_per)
{
	if((*x_per) >= 70)
	{
		return RIGHT; 	
	}
	else if((*x_per) <= -70)
	{
		return LEFT;
	}
	else if((*y_per) >= 70)
	{
		return UP;
	}
	else if((*y_per) <= -70)
	{
		return DOWN;
	}
	
	return NEUTRAL;
	
}

