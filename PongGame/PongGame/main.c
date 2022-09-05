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




int main(void)
{
	uart_test();
}
