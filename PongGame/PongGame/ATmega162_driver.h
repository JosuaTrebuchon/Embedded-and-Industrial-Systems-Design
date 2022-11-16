#include "bit_maniulation.h"
#include <avr/io.h>
#include <stdio.h>

// #define F_CPU 4915200
#define FOSC 4915200 // 1843200
#define BAUD 9600
#define UBRR FOSC / 16 / BAUD - 1
#define BASE_ADDRESS 0x0000

double dutyCircle;

void USART_Init(unsigned int ubrr);

void USART_TX(unsigned char data);

unsigned char USART_RX();

FILE mystdout;
int uart_putchar(char c, FILE *stream);

void xmem_init(void);

void xmem_write(uint8_t data, uint16_t addr);

uint8_t xmem_read(uint16_t addr);

void pushButton_init(void);
