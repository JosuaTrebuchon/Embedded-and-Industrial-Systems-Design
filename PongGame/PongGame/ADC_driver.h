#include <avr/io.h>
#include <stdio.h>
#include "bit_maniulation.h"
#include "ATmega162_driver.h"
#define F_CPU 4915200

#include <util/delay.h>



void ADC_init(void);

void ADC_read(void);

//uint8_t adc_read(uint8_t channel); //volatile

void adc_calibrate();/*enum pos_t {LEFT, RIGHT, UP, DOWN, NEUTRAL};	pos_t pos_read(void);*/