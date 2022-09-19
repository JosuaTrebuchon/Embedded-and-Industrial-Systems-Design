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
#include "ADC_driver.h"
#include <avr/interrupt.h>

double dutyCircle = 50;

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
	ADC_read();
	xmem_write(0x52, 0x1400);
// 	stdout = &mystdout;
// 	printf("Busy\n");
}

void PWM_Init()
{
	//DDRD |= (1 << PD5);
	set_bit(DDRD, DDD5);
	
	/* Fast PWM, TOP value = ICR1 */
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11);
	clear_bit(TCCR1A, WGM10);
	
	set_bit(TCCR1A, COM1A1);
	clear_bit(TCCR1A, COM1A0);
	
	set_bit(TIMSK, TOIE1);
}


int main(void)
{
	
	stdout = &mystdout;

		USART_Init(UBRR);
		
		xmem_init();
		
		PWM_Init();
		ADC_init();
		
		ICR1 = 1;
		
		OCR1A = (dutyCircle/100.0)*ICR1;
		
		sei(); // Enable all interrupt
		
		clear_bit(TCCR1B, CS12);
		clear_bit(TCCR1B, CS11);
		set_bit(TCCR1B, CS10);
		
		
		// decoder_test();
		//SRAM_test();
// 	while(1)
// 	{
// 		//decoder_test();
// 		// xmem_write(0x51, 0x1400); /* Chip select CS turned on for ADC */
// 		
// 		/* Write signal turned on to initiate data sampling */
// // 		set_bit(PORTD, PD6);
// // 		_delay_ms(100);
// // 		clear_bit(PORTD, PD6);
// 		_delay_ms(100);
// 		
// 	}
	
	
	while(1)
	{
		//SRAM_test();
		//_delay_ms(5000);
		xmem_init();
	}
//  	
// 	xmem_write(0x00, 0x1800);
// 	clear_bit(PINC, PINC3);
// 	xmem_write(0x00, 0x1400);
// 	xmem_write(0x00, 0x1700);
// 	xmem_write(0x00, 0x1800);
	/*while(1)
	{
		
		//ADC_read();
		//
		//_delay_ms(500);
		
	}*/
	
	
	
}
