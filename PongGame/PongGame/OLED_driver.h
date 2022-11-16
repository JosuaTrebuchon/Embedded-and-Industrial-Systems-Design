#include "ATmega162_driver.h"
#include "fonts.h"
#include "p1000_driver.h"

void oled_init();

void oled_reset();

void write_char(char n);

void oled_home();

void go_to_page(int i);

void go_to_col(uint8_t i);

void clear_line(int i);

void oled_print(char *word);

void oled_print_arrow(int row, int col, uint8_t clear);

void oled_menu(float *x_per, float *y_per, pos_t *position, int *left_pos,
               int *right_pos, uint8_t *ADC_data);
