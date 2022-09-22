/*
#include <avr/interrupt.h>


ISR(USART0_RXC_vect)
{
	char ReceivedByte;
	ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	UDR0 = ReceivedByte; // Echo back the received byte back to the computer
}

ISR(TIMER1_OVF_vect)
{
	OCR1A = (dutyCircle/100.0)*ICR1;
}

ISR(INT2_vect)
{
	ADC_read(&ADC_data);
	// xmem_write(0x52, 0x1400);

}*/