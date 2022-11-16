#include "MCP2515_driver.h"

uint8_t mcp2515_init() {
  // stdout = &mystdout;
  char value;
  spi_init();      // Initialize SPI
  mcp2515_reset(); // Send reset - command

  // Self - test for Config mode (set during reset)
  value = mcp2515_read(MCP_CANSTAT);
  if ((value & MODE_MASK) != MODE_CONFIG) {
    printf(" MCP2515 is NOT in configuration mode after reset !\n");
    return 1;
  }

  // Set baudrate, PropSeg, PS1, PS2, SJW,
  // F_osc= 16MHz
  // Use set in register CNF1, CNF2, CNF3 From page 43 in MCP2515

  mcp2515_bit_modify(MCP_CNF1, 0xFF, 0x03);
  mcp2515_bit_modify(MCP_CNF2, 0xFF, 0xB1);
  mcp2515_bit_modify(MCP_CNF3, 0xC7, 0x05);
  // Baud = 125kHz
  //
  // set to Loopback mode
  // mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

  // set to Normal mode
  mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

  return 0;
}

char mcp2515_read(unsigned char addr) {
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

void mcp2515_write(unsigned char addr, unsigned char data) {
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

char mcp2515_read_status() {
  clear_bit(PORTB, PB4);

  spi_transmit(MCP_READ_STATUS);
  spi_transmit(0x00);

  set_bit(PORTB, PB4);

  char data;
  data = spi_slave_receive();

  return data;
}

void mcp2515_bit_modify(unsigned char addr, unsigned char mask,
                        unsigned char data) {
  clear_bit(PORTB, PB4);

  spi_transmit(MCP_BITMOD);
  spi_transmit(addr);
  spi_transmit(mask);
  spi_transmit(data);

  set_bit(PORTB, PB4);
}

void mcp2515_reset() {
  clear_bit(PORTB, PB4);

  spi_transmit(MCP_RESET);

  set_bit(PORTB, PB4);
}
