/*
 * PongGame.c
 *
 * Created: 01.09.2022 12:22:03
 * Author : bjornolo
 */ 

#define F_CPU 4915200
//#define BAUD 9600
#include "OLED_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include "test.h"
#include "ATmega162_driver.h"
#include <avr/interrupt.h>
#include "ADC_driver.h"
#include "p1000_driver.h" 

extern uint8_t ADC_data [4];
int y_arrow;
int page_arrow;


/************************************************************************/
/* Interrupt catching byte reception for UART communication             */
/************************************************************************/
ISR(USART0_RXC_vect)
{
	char ReceivedByte;
	ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}
/************************************************************************/
/* Interrupt catching the timer counter for PWM clock                   */
/************************************************************************/
ISR(TIMER1_OVF_vect)
{
	OCR1A = (dutyCircle/100.0)*ICR1;
}

/************************************************************************/
/* Interrupt catching BUSY signal for ADC data read                     */
/************************************************************************/
ISR(INT2_vect)
{
	ADC_read(ADC_data);
	// xmem_write(0x52, 0x1400);

}
/************************************************************************/
/* Interrupt catching joystick button falling edge                      */
/************************************************************************/
ISR(INT0_vect)
{
	printf("BUTTON pressed y arrow: %d, page arrow: %d\n", y_arrow, page_arrow);
}

int main(void)
{
			


	uint8_t size_arrow;
	
	float x_per;
	float y_per;
	pos_t position;
	int calibrated = 0;
	dutyCircle = 50;

	(x_per) = 0;
	(y_per) = 0;


	stdout = &mystdout;

	USART_Init(UBRR);
	
	xmem_init();
	
	PWM_Init();
	ADC_init();
	
	sei(); // Enable all interrupt

	size_arrow = 1;
	page_arrow = 2;
	y_arrow = 0;
	position = 0;
	pushButton_init();
	oled_init();
	oled_reset();
	
	oled_home();
	//
	//oled_home();
	
	go_to_page(2);
	go_to_col(30);
	oled_print("Start");
	go_to_page(3);
	go_to_col(30);
	oled_print("PingPong");
	go_to_page(4);
	go_to_col(30);
	oled_print("End game");
	
	//oled_home();
	
	
	oled_print_arrow(page_arrow, y_arrow, 0);
	
	while (1)
	{		
		joystick_analog_position(&x_per, &y_per, ADC_data, &calibrated);
		position = pos_read(&x_per, &y_per);
			
		// slider_position(&x_per, &y_per, ADC_data);
		switch(position)
		{
			case UP:
				printf("UP\n");
				oled_print_arrow(page_arrow, y_arrow, 1);
				page_arrow -= size_arrow;
				if(page_arrow < 0) page_arrow = 7;
				oled_print_arrow(page_arrow, y_arrow, 0);
				break;
			case DOWN:
				printf("DOWN\n");
				oled_print_arrow(page_arrow, y_arrow, 1);
				page_arrow += size_arrow;
				if(page_arrow > 7) page_arrow = 0;
				oled_print_arrow(page_arrow, y_arrow, 0);
				break;
			case RIGHT:
				printf("RIGHT\n");
				
				oled_print_arrow(page_arrow, y_arrow, 1);
				y_arrow += 5;
				oled_print_arrow(page_arrow, y_arrow, 0);
				break;
				
			case LEFT:
			
				printf("LEFT\n");
				oled_print_arrow(page_arrow, y_arrow, 1);
				y_arrow -= 5;
				oled_print_arrow(page_arrow, y_arrow, 0);				
				break;
				
			case NEUTRAL:
				printf("NEUTRAL\n");
				break;
			default:
				printf("Not working ?\n");
				break;
		}
		
		_delay_ms(1);
	}
	
	
	
}

