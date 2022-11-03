#include "sam.h"
#include "pwm.h"
#include "printf-stdarg.h"
#include "can_interrupt.h"
#include "can_controller.h"
#include "DAC_driver.h"

#define MJ2_DATA_Msk 0x1FE

void slider_open_loop();

uint16_t read_decoder();