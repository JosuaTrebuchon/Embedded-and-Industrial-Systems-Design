#include "MCP2515_driver.h"


char mcp2515_read(unsigned char addr)
{
	clear_bit(PORTB, PB4);
	
	/*read command*/
	spi_transmit(MCP_READ);
	
	/*address*/
	spi_transmit(addr);
	
	spi_transmit(0x00);
	
	char data = spi_slave_receive();
	
	set_bit(PORTB, PB4);
	
	return data;
}

void mcp2515_write(unsigned char addr, unsigned char data)
{
	clear_bit(PORTB, PB4);
	
	/*write command*/
	spi_transmit(MCP_WRITE);
	
	/*address*/
	spi_transmit(addr);
	
	spi_transmit(data);
	
	set_bit(PORTB, PB4);
	
}

void mcp2515_request_to_send(unsigned char transmit_buffer)
/*	#define MCP_RTS_TX0		0x81
	#define MCP_RTS_TX1		0x82
	#define MCP_RTS_TX2		0x84
	#define MCP_RTS_ALL		0x87
*/
{
	clear_bit(PORTB, PB4);
	
	spi_transmit(transmit_buffer);
	
	set_bit(PORTB, PB4);
	
	
}

char mcp2515_read_status()
{
	clear_bit(PORTB, PB4);
	
	spi_transmit(MCP_READ_STATUS);
	spi_transmit(0x00);
	
	set_bit(PORTB, PB4);
	
	char data;
	data = spi_slave_receive();
	
	return data;
	
}

void mcp2515_bit_modify(unsigned char addr, unsigned char mask, unsigned char data)
{
	clear_bit(PORTB, PB4);
	
	spi_transmit(MCP_BITMOD);
	spi_transmit(addr);
	spi_transmit(mask);
	spi_transmit(data);
	
	set_bit(PORTB, PB4);
}

void mcp2515_reset()
{
	clear_bit(PORTB, PB4);
	
	spi_transmit(MCP_RESET);
	
	set_bit(PORTB, PB4);
	
}

