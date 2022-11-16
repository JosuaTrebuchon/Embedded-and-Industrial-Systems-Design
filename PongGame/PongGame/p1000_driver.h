/*
 * p1000_driver.h
 *
 * Created: 22.09.2022 14:44:19
 *  Author: bjornolo and Taylor
 */

#ifndef P1000_DRIVER_H_
#define P1000_DRIVER_H_

#include "ADC_driver.h"
#include "ATmega162_driver.h"
#include <avr/io.h>

typedef enum pos_t { LEFT, RIGHT, UP, DOWN, NEUTRAL } pos_t;
void joystick_analog_position(float *x_per, float *y_per, uint8_t *ADC_data);
void slider_position(int *left_per, int *right_per, uint8_t *ADC_data);
pos_t pos_read(float *x_per, float *y_per);

#endif /* P1000_DRIVER_H_ */
