/*
 * p1000_driver.c
 *
 * Created: 22.09.2022 14:43:47
 *  Author: bjornolo
 */ 

#include "p1000_driver.h" 

float x_joystick_calibrate=128; 
float y_joystick_calibrate=128; void joystick_analog_position(float* x_per, float* y_per, uint8_t* ADC_data, int* calibrated)
{
	xmem_write(0x52, 0x1400);
	/*
	if(!(*calibrated))
	{
		x_joystick_calibrate = ADC_data[3];
		y_joystick_calibrate = ADC_data[0];
		
		*calibrated = 1;
	}
	*/

	*x_per = ((float)ADC_data[3]*(float)(200.0/255.0)-100);
	*y_per = ((float)ADC_data[0]*(float)(200.0/255.0)-100);

}

void slider_position(float *left_per, float *right_per, uint8_t* ADC_data)
{
	xmem_write(0x52, 0x1400);
	//printf( "ADC_data[%d] = %d, ADC_data[%d] = %d\n", 1, (int)ADC_data [1],2, (int)ADC_data [2]);
}



pos_t pos_read(float* x_per, float* y_per)
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
/*
switch(position)
{
	case UP:
	printf("UP\n");
	break;
	case DOWN:
	printf("DOWN\n");
	break;
	case RIGHT:
	printf("RIGHT\n");
	break;
	case LEFT:
	printf("LEFT\n");
	break;
	case NEUTRAL:
	printf("NEUTRAL\n");
	break;
	default:
	printf("Not working ?\n");
	break;
}
*/