/*
 * PongGame.c
 *
 * Created: 01.09.2022 12:22:03
 * Author : bjornolo
 */ 

#define F_CPU 4915200
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include "bit_maniulation.h"
#include "test.h"
#include "ATmega162_driver.h"

int main(void)
{
	unsigned char test;
	USART_Init(UBRR);
	test = 0;
	while(1)
	{
		
		_delay_ms(50);
		
		test = USART_RX();
		USART_TX(test);
	}
	
}
