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
#include "OLED_driver.h"

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
				float x_per;
				float y_per;
				pos_t position;
				int calibrated = 0;
				dutyCircle = 50;
				// ADC_data = {0,0,0,0};
				(x_per) = 0;
				(y_per) = 0;

	dutyCircle = 50;
	// ADC_data = {0,0,0,0};

	stdout = &mystdout;

	USART_Init(UBRR);
		
	xmem_init();
		
	PWM_Init();
	ADC_init();
		
	sei(); // Enable all interrupt
	int delay = 1;
	
	oled_init();
	_delay_ms(delay);
	
	
	/*xmem_write(0x2f, 0x1000);
*/
/*	xmem_write(0xb1, 0x1000);
	xmem_write(0x00, 0x1000);
	xmem_write(0xb2, 0x1000);
	xmem_write(0x00, 0x1000);
	*/
	//xmem_write(0x40, 0x1000);
	while(1)
	{
		//xmem_write(0xae, 0x1000); // display off
		// xmem_write(0xff, 0x1000);
		
		xmem_write(0xff, 0x1200);
		_delay_ms(delay);
		xmem_write(0x00, 0x1200); // display on
		//_delay_ms(delay);
	}
	
}

/*
			float x_per;
			float y_per;
			pos_t position;
			int calibrated = 0;
			dutyCircle = 50;
			// ADC_data = {0,0,0,0};
			(x_per) = 0;
			(y_per) = 0;
		joystick_analog_position(&x_per, &y_per, ADC_data, &calibrated);
		position = pos_read(&x_per, &y_per);
		
		slider_position(&x_per, &y_per, ADC_data);
		*/