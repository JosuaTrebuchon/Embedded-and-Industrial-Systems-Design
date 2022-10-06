#include <avr/io.h>

void spi_init(void);

void spi_transmit(char cData);

void spi_slave_init(void);

char spi_slave_receive(void);