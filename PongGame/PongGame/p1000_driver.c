/*
 * p1000_driver.c
 *
 * Created: 22.09.2022 14:43:47
 *  Author: bjornolo
 */

#include "p1000_driver.h"

float x_joystick_calibrate = 128;
float y_joystick_calibrate = 128;
void joystick_analog_position(float *x_per, float *y_per, uint8_t *ADC_data) {
  ADC_read(ADC_data);
  xmem_write(0x00, 0x1400);

  *x_per = ((float)ADC_data[3] * (float)(200.0 / 255.0) - 100);
  *y_per = ((float)ADC_data[0] * (float)(200.0 / 255.0) - 100);
}

void slider_position(int *left_per, int *right_per, uint8_t *ADC_data) {
  ADC_read(ADC_data);
  xmem_write(0x00, 0x1400);
  // printf( "ADC_data[%d] = %d, ADC_data[%d] = %d\n", 1, (int)ADC_data [1],2,
  // (int)ADC_data [2]);
  *left_per = ADC_data[1];
  *right_per = ADC_data[2];
}

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
