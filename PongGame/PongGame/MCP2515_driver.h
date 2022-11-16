#include "MCP2515_registers.h"
#include "SPI.h"
#include "bit_maniulation.h"

uint8_t mcp2515_init();

char mcp2515_read(unsigned char addr);

void mcp2515_write(unsigned char addr, unsigned char data);

void mcp2515_request_to_send(unsigned char transmit_buffer);

char mcp2515_read_status();

void mcp2515_bit_modify(unsigned char addr, unsigned char mask,
                        unsigned char data);

void mcp2515_reset();
