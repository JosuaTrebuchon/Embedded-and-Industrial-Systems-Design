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


int main(void)
{
	uart_interrupt_test();
}
