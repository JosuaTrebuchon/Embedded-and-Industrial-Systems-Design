#define F_CPU 4915200

#include "OLED_driver.h"
#include "bit_maniulation.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

void pin_test();

void uart_test();

void uart_interrupt_test();

void SRAM_test(void);

void decoder_test(void);

void ADC_test(void);

void joystick_test();

void oled_print_test(void);

void oled_movement_test(void);

void test_CAN();
