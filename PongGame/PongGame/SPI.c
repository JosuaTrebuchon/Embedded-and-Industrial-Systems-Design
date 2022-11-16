#include "SPI.h"

// start/stop with SPDR

void spi_init(void) {
  /* Set SS, MOSI and SCK output, all others input */
  DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void spi_transmit(char cData) {
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)))
    ;
}

void spi_slave_init(void) {
  /* Set MISO output, all others input */
  DDRB |= (1 << DDB6);
  /* Enable SPI */
  SPCR = (1 << SPE);
}

char spi_slave_receive(void) {
  /* Wait for reception complete */
  while (!(SPSR & (1 << SPIF)))
    ;
  /* Return data register */
  return SPDR;
}
