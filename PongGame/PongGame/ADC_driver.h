#include <avr/io.h>
#include <stdio.h>
#include "bit_maniulation.h"
void ADC_init(void);

uint8_t adc_read(uint8_t channel); //volatile

void adc_calibrate();