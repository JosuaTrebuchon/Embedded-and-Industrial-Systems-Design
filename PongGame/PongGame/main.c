/*
 * PongGame.c
 *
 * Created: 01.09.2022 12:22:03
 * Author : bjornolo
 */ 

#define F_CPU 4915200
//#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include "test.h"
#include "ATmega162_driver.h"
#include <avr/interrupt.h>
#include "ADC_driver.h"
#include "p1000_driver.h" 

uint8_t ADC_data [4];

ISR(USART0_RXC_vect)
{
	char ReceivedByte;
	ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}

ISR(TIMER1_OVF_vect)
{
	OCR1A = (dutyCircle/100.0)*ICR1;
}

ISR(INT2_vect)
{
	ADC_read(ADC_data);
	// xmem_write(0x52, 0x1400);

}

int main(void)
{
	int x_per;
	int y_per;
	pos_t position;
	
	dutyCircle = 50;
	// ADC_data = {0,0,0,0};
	(x_per) = 0;
	(y_per) = 0;
	
	stdout = &mystdout;

	USART_Init(UBRR);
		
	xmem_init();
		
	PWM_Init();
	ADC_init();
		
	sei(); // Enable all interrupt
		
	while(1)
	{
		//_delay_ms(100);
		joystick_analog_position(&x_per, &y_per, ADC_data);
		position = pos_read(&x_per, &y_per);
		
		switch(position)
		{
			case UP:
				printf("UP\n");
				break;
			case DOWN:
				printf("DOWN\n");
				break;
			case RIGHT:
				printf("RIGTH\n");
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
			
	}
	
}
