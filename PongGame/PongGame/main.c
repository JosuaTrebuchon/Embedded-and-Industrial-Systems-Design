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
#include "bit_maniulation.h"
#include "test.h"
#include "ATmega162_driver.h"

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
_FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}
int main(void)
{
	unsigned char test;
	USART_Init(UBRR);
	stdout = &mystdout;	
	// test = 0;
	while(1)
	{
		printf("a");
		_delay_ms(500);
		
		/*
		test = USART_RX();
		USART_TX(test);
		*/
	}
	
}
