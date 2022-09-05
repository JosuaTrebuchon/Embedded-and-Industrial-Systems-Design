#include <avr/io.h>
#include <stdio.h>

// #define F_CPU 4915200
#define FOSC 1843200
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr);

void USART_TX(unsigned char data);

unsigned char USART_RX();
/*
static FILE mystdout;

static int uart_putchar(char c, FILE *stream);
*/