#include "ATmega162_driver.h"

void USART_Init(unsigned int ubrr)
{
	/* Set baud rate */
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) (ubrr);
	
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);  
	
}

void USART_TX(unsigned char data){
	while ( !( UCSR0A & (1 << UDRE0)) );
		
	UDR0 = data;
}

unsigned char USART_RX(){
	while ( !( UCSR0A & (1 << RXC0) ));
	
	return UDR0;	
}

/*
	Links printf to UART
	Uses code from this source: 
	https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaea2b6be92ead4673bc487b271b7227fb
*/


