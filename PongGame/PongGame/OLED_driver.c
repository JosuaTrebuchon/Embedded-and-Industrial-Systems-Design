#include "OLED_driver.h"

void oled_init() {

  xmem_write(0xae, 0x1000); // display off
  xmem_write(0xa1, 0x1000); // segment remap

  /*
  xmem_write(0xD3, 0x1000);
  xmem_write(0x00, 0x1000);
  */

  xmem_write(0xda, 0x1000); // common pads hardware: alternative
  xmem_write(0x12, 0x1000);
  xmem_write(0xc8, 0x1000); // common output scan direction:com63~com0
  xmem_write(0xa8, 0x1000); // multiplex ration mode:63
  xmem_write(0x3f, 0x1000);
  xmem_write(0xd5, 0x1000); // display divide ratio/osc. freq. mode
  xmem_write(0x80, 0x1000);
  xmem_write(0x81, 0x1000); // contrast control
  xmem_write(0x50, 0x1000);
  xmem_write(0xd9, 0x1000); // set pre-charge period
  xmem_write(0x21, 0x1000);
  xmem_write(0x20, 0x1000); // Set Memory Addressing Mode
  xmem_write(0x02, 0x1000);
  xmem_write(0xdb, 0x1000); // VCOM deselect level mode
  xmem_write(0x30, 0x1000);
  xmem_write(0xad, 0x1000); // master configuration
  xmem_write(0x00, 0x1000);
  xmem_write(0xa4, 0x1000); // out follows RAM content
  xmem_write(0xa6, 0x1000); // set normal display

  xmem_write(0x00, 0x1000);
  // xmem_write(0x10, 0x1000);
  // xmem_write(0x52, 0x1000);
  //

  xmem_write(0xaf, 0x1000); // display on
}

void oled_reset() {

  int num_pages = 8;
  int num_rows = 128;
  uint8_t page_num = 0xb0;

  // start location in page
  xmem_write(0x40, 0x1000);

  // page number
  xmem_write(page_num, 0x1000);

  for (int i = 0; i < num_pages; ++i) {
    for (int j = 0; j < num_rows; ++j) {
      xmem_write(0x00, 0x1200);
    }

    page_num = page_num + 1;
    xmem_write(page_num, 0x1000);
  }
}

/*
void oled_reset()
{
        xmem_write(0xa7, 0x1000);
        xmem_write(0xa6, 0x1000);
        
}*/
void write_char(char n) {
  unsigned char segment[8] = {0};

  for (int i = 0; i < 8; ++i) {
    segment[i] = pgm_read_byte(&(font8[(int)n - 32][i]));
    xmem_write(segment[i], 0x1200);
  }
}

void oled_home() {
  xmem_write(0xb0, 0x1000);

  xmem_write(0x00, 0x1000);
  xmem_write(0x10, 0x1000);
}

void go_to_page(int i) // 0-7
{
  uint8_t pos = 0xb0 + i;
  xmem_write(pos, 0x1000);
}

void go_to_col(uint8_t i) // 0-127
{
  /*
          uint8_t lower_start;
          uint8_t upper;
  */

  // lower_start = (i & 0x0f);
  // upper = ((i >> 4) & 0x0f);
  xmem_write((i & 0x0f), 0x1000);
  xmem_write((0x10 + ((i >> 4) & 0x0f)), 0x1000);
  /*
          xmem_write(0x0D, 0x1000);
          xmem_write(0x17, 0x1000);*/
}

void clear_line(int i) {
  for (int col = 0; col < 128; col++) {
    go_to_page(i);
    go_to_col(col);
    xmem_write(0x00, 0x1200);
  }
}

void oled_print(char *word) {
  int i = 0;
  while (word[i] != '\0') {
    write_char(word[i]);
    ++i;
  }
}

void oled_print_arrow(int row, int col, uint8_t clear) {
  go_to_col(col);
  go_to_page(row);
  //_delay_ms(5);
  if (clear < 1) {
    xmem_write(0b00011000, 0x1200);
    xmem_write(0b00011000, 0x1200);
    xmem_write(0b01111110, 0x1200);
    xmem_write(0b00111100, 0x1200);
    xmem_write(0b00011000, 0x1200);
  } else {
    xmem_write(0b00000000, 0x1200);
    xmem_write(0b00000000, 0x1200);
    xmem_write(0b00000000, 0x1200);
    xmem_write(0b00000000, 0x1200);
    xmem_write(0b00000000, 0x1200);
  }
}

extern int joystick_button_flag;
uint8_t ADC_data[4];

void oled_menu(float *x_per, float *y_per, pos_t *position, int *left_pos,
               int *right_pos, uint8_t *ADC_data) {
  int page_arrow = 0;
  int y_arrow = 0;
  uint8_t size_arrow = 1;
  oled_init();
  oled_reset();

  oled_home();
  oled_reset();

  go_to_page(1);
  go_to_col(10);
  oled_print("Welcome to ");
  go_to_page(2);
  go_to_col(10);
  oled_print("group 31");
  go_to_page(3);
  go_to_col(10);
  oled_print("Pong game.");
  go_to_page(4);
  go_to_col(30);
  oled_print("Start game");

  oled_print_arrow(page_arrow, y_arrow, 0);

  while ((!joystick_button_flag) || !(page_arrow == 4)) {

    joystick_analog_position(x_per, y_per, ADC_data);
    *position = pos_read(x_per, y_per);

    printf("joystick button flag: %d page arrow: %d \n", joystick_button_flag,
           page_arrow);
    switch (*position) {
    case UP:
      // printf("UP\n");
      oled_print_arrow(page_arrow, y_arrow, 1);
      page_arrow -= size_arrow;
      if (page_arrow < 0)
        page_arrow = 7;
      oled_print_arrow(page_arrow, y_arrow, 0);
      break;
    case DOWN:
      // printf("DOWN\n");
      oled_print_arrow(page_arrow, y_arrow, 1);
      page_arrow += size_arrow;
      if (page_arrow > 7)
        page_arrow = 0;
      oled_print_arrow(page_arrow, y_arrow, 0);
      break;

    /*
    case RIGHT:
    //printf("RIGHT\n");

    oled_print_arrow(page_arrow, y_arrow, 1);
    y_arrow += 5;
    oled_print_arrow(page_arrow, y_arrow, 0);
    break;

    case LEFT:

    //printf("LEFT\n");
    oled_print_arrow(page_arrow, y_arrow, 1);
    y_arrow -= 5;
    oled_print_arrow(page_arrow, y_arrow, 0);
    break;
    */
    case NEUTRAL:
      // printf("NEUTRAL\n");
      break;
    default:
      printf("Not working ?\n");
      break;
    }

    //_delay_ms(100);

    //_delay_ms(5);
    joystick_button_flag = 0;
  }
  joystick_button_flag = 0;
  printf("exiting while loop \n");
  oled_home();
  oled_reset();
  go_to_page(3);
  go_to_col(30);
  oled_print("Good luck :)");
  go_to_page(4);
  go_to_col(30);
  oled_print("3         ");
  go_to_page(3);
  go_to_col(30);
  oled_print("Good luck :)");
  go_to_page(5);
  go_to_col(30);
  oled_print("2         ");
  go_to_page(3);
  go_to_col(30);
  oled_print("Good luck :)");
  go_to_page(6);
  go_to_col(30);
  oled_print("1         ");
  go_to_page(3);
  go_to_col(30);
  oled_print("Good luck :)");
  //_delay_ms(100);
  xmem_write(0xae, 0x1000); // display off
}
