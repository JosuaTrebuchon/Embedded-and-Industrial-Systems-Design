/*
 * p1000_driver.c
 *
 * Created: 22.09.2022 14:43:47
 *  Author: bjornolo
 */

#include "p1000_driver.h"

float x_joystick_calibrate = 128;
float y_joystick_calibrate = 128;
/**
 * @brief 
 * 
 * @param x_per    :x percentage 
 * @param y_per    :y percentage
 * @param ADC_data :ADC data
 */
void joystick_analog_position(float *x_per, float *y_per, uint8_t *ADC_data) {
  ADC_read(ADC_data);
  xmem_write(0x00, 0x1400);

  *x_per = ((float)ADC_data[3] * (float)(200.0 / 255.0) - 100);
  *y_per = ((float)ADC_data[0] * (float)(200.0 / 255.0) - 100);
}

/**
 * @brief 
 * 
 * @param x_per    :x percentage 
 * @param y_per    :y percentage
 * @param ADC_data :ADC data
 */
void slider_position(int *left_per, int *right_per, uint8_t *ADC_data) {
  ADC_read(ADC_data);
  xmem_write(0x00, 0x1400);
  *left_per = ADC_data[1];
  *right_per = ADC_data[2];
}

/**
 * @brief 
 * 
 * @param x_per  :x percentage 
 * @param y_per  :y percentage
 * @return pos_t :joystick position enum
 */
pos_t pos_read(float *x_per, float *y_per) {
  if ((*x_per) >= 70) {
    return RIGHT;
  } else if ((*x_per) <= -70) {
    return LEFT;
  } else if ((*y_per) >= 70) {
    return UP;
  } else if ((*y_per) <= -70) {
    return DOWN;
  }

  return NEUTRAL;
}
