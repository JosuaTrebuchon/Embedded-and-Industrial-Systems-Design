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
#include "MCP2515_driver.h"
#include "CAN.h"

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
	printf("BUTTON pressed Column: %d, Page: %d\n", y_arrow, page_arrow);
}

/************************************************************************/
/* Interrupt catching INT1 VAN controller low level                     */
/************************************************************************/
ISR(INT1_vect)
{
	printf("CAN controller interrupt caught /!\\\n");
}

int main(void)
{

	stdout = &mystdout;

	USART_Init(UBRR);
	xmem_init();
	PWM_Init();
	ADC_init();
	mcp2515_init();
	
	float x_per;
	float y_per;
	pos_t position;
	position = 0;
	(x_per) = 0;
	(y_per) = 0;
	int calibrated = 0;
	can_message joystick_msg;
	
	while (1)
	{
		joystick_analog_position(&x_per, &y_per, ADC_data, &calibrated);
		position = pos_read(&x_per, &y_per);

		joystick_msg.id = 1;
		joystick_msg.data_length = 1;
		joystick_msg.data[0] = position;
		printf("position %d\n", position);
		can_message_send(&joystick_msg);
		
		//_delay_ms(100);
	}


}

