#include "MCP2515_driver.h"

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t mcp2515_init() {
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

/**
 * @brief 
 * 
 * @param addr  :Address
 * @return char :Can message
 */
char mcp2515_read(unsigned char addr) {
  /*Chip select*/
  clear_bit(PORTB, PB4);

  /*SPI transmit*/
  spi_transmit(MCP_READ);
  spi_transmit(addr);
  spi_transmit(0x00);
  
  /*CAN controller read data*/
  char data = spi_slave_receive();
  
  /*Chip de-select*/
  set_bit(PORTB, PB4);

  return data;
}

/**
 * @brief 
 * 
 * @param addr  :Address
 * @param data  :Data
 */
void mcp2515_write(unsigned char addr, unsigned char data) {
  /*Chip select*/
  clear_bit(PORTB, PB4);

  /*SPI transmit*/
  spi_transmit(MCP_WRITE);
  spi_transmit(addr);
  spi_transmit(data);

  /*Chip de-select*/
  set_bit(PORTB, PB4);
}

/**
 * @brief 
 * 
 * @param transmit_buffer :Transmit buffer
 */
*/
void mcp2515_request_to_send(unsigned char transmit_buffer)
{
  /*Chip select*/
  clear_bit(PORTB, PB4);
  
  /*SPI transmit*/
  spi_transmit(transmit_buffer);

  /*Chip de-select*/
  set_bit(PORTB, PB4);
}

/**
 * @brief 
 * 
 * @return char :CAN controller status register
 */
char mcp2515_read_status() {
  /*Chip select*/
  clear_bit(PORTB, PB4);
  
  /*SPI transmit*/
  spi_transmit(MCP_READ_STATUS);
  spi_transmit(0x00);

  /*Chip de-select*/
  set_bit(PORTB, PB4);

  /*CAN caontroller status*/
  char data;
  data = spi_slave_receive();

  return data;
}

/**
 * @brief 
 * 
 * @param addr :Address
 * @param mask :Bit modify mask
 * @param data :Bit modify data
 */
void mcp2515_bit_modify(unsigned char addr, unsigned char mask, unsigned char data) {
  /*Chip select*/
  clear_bit(PORTB, PB4);

  /*SPI transmit*/
  spi_transmit(MCP_BITMOD);
  spi_transmit(addr);
  spi_transmit(mask);
  spi_transmit(data);

  /*Chip de-select*/
  set_bit(PORTB, PB4);
}

/**
 * @brief 
 *  Reset CAN controller
 */
void mcp2515_reset() {
  clear_bit(PORTB, PB4);

  spi_transmit(MCP_RESET);

  set_bit(PORTB, PB4);
}
