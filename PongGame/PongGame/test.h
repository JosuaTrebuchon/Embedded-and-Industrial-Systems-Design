#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "bit_maniulation.h"
#include <stdlib.h>

void pin_test();

void uart_test();

void uart_interrupt_test();

void SRAM_test(void);