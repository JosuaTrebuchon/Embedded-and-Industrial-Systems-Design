#include "sam.h"
#include "pwm.h"
#include "printf-stdarg.h"
#include "can_interrupt.h"
#include "can_controller.h"
#include "DAC_driver.h"
#include "pid.h"

#define MJ2_DATA_Msk 0x1FE

void reset_encoder(void);
void slider_open_loop(void);
void init_motor_position(void);
void Delay(int num);
void motor_init(void);
uint16_t read_encoder(void);
void move_to_setpoint(void);

void solenoid_init(void);
void solenoid_impulse(void);


