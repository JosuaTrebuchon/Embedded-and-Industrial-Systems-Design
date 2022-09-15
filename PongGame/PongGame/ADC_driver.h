#include <avr/io.h>
#include <stdio.h>
#include "bit_maniulation.h"
void ADC_init(void);

uint8_t adc_read(uint8_t channel); //volatile

void adc_calibrate();/*enum pos_t {LEFT, RIGHT, UP, DOWN, NEUTRAL};	pos_t pos_read(void);*/