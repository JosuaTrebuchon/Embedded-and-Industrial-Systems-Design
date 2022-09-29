/*
 * p1000_driver.h
 *
 * Created: 22.09.2022 14:44:19
 *  Author: bjornolo and Taylor
 */ 


#ifndef P1000_DRIVER_H_
#define P1000_DRIVER_H_

#include <avr/io.h>
#include "ATmega162_driver.h"

typedef enum pos_t {LEFT, RIGHT, UP, DOWN, NEUTRAL} pos_t;void joystick_analog_position(float* x_per, float* y_per, uint8_t* ADC_data, int* calibrated);void slider_position(float *left_per, float *right_per, uint8_t* ADC_data);pos_t pos_read(float* x_per, float* y_per);


#endif /* P1000_DRIVER_H_ */

