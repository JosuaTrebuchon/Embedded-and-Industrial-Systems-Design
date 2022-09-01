#include <avr/io.h>
#include <util/delay.h>

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr);

void USART_TX(unsigned char data);

unsigned char USART_RX();