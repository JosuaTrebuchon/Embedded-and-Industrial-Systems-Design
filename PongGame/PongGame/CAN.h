#define F_CPU 4915200

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "MCP2515_driver.h"
#include "MCP2515_registers.h"
#include "ATmega162_driver.h"

#define TXB0SIDH	0x31
#define TXB0SIDL	0x32
#define	TXB0DLC		0x35
#define TXB0D0		0x36
#define RXB0SIDL	0x62
#define RXB0DLC		0x65
#define RXB0D0		0x66


typedef struct can_message 
{
	uint16_t id ;
	char data_length ;
	char data [8];
	
}can_message;void can_message_send(can_message *message);can_message can_data_recieve();