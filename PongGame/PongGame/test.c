#include "test.h"
#include "ATmega162_driver.h"

void pin_test()
{
	set_bit(DDRB, 0);
	/* Replace with your application code */
	while (1)
	{
		set_bit(PORTB, 0);
		
		_delay_ms(500);
		
		clear_bit(PORTB, 0);
		
		_delay_ms(500);
	}
}


void uart_test()
{
	unsigned char test;
	USART_Init(UBRR);
	stdout = &mystdout;	

	while(1)
	{
		test = USART_RX();
		printf("%c", test);
		_delay_ms(500);
		
		/*
		test = USART_RX();
		USART_TX(test);
		*/
	}
}