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

ISR(USART0_RXC_vect)
{
   char ReceivedByte;
   ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
   UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}

void PWM_Init()
{
	//DDRD |= (1 << PD5);
	set_bit(DDRD, DDD5);
	
	clear_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	clear_bit(TCCR1A, WGM11);
	set_bit(TCCR1A, WGM10);
	
	set_bit(TCCR1A, COM1A1);
	clear_bit(TCCR1A, COM1A0);
	
	clear_bit(TCCR1B, CS12);
	clear_bit(TCCR1B, CS11);
	set_bit(TCCR1B, CS10);
}


int main(void)
{
	
	stdout = &mystdout;
	
	USART_Init(UBRR);
	
	xmem_init();
	
	PWM_Init();
	//SRAM_test();
	while(1)
	{
		decoder_test();
	}
	
	/*
	while(1)
	{
		SRAM_test();
		_delay_ms(5000);
	}
	*/
	
	
	/*
	while(1)
	{
		xmem_write(0x52, 0x400);
		_delay_ms(500);
		xmem_write(0x52, 0x800);
		_delay_ms(500);
		
	}
	*/
	
	
	
}
