#include "sam.h"
#include "pwm.h"
#include "printf-stdarg.h"
#include "can_interrupt.h"
#include "can_controller.h"

/*
#define PWM_CPRD5 0x400942AC
#define PWM_CDTY5 0x400942A4
#define PWM_ENA 0x40094004*/

void peripheral_init();

void pwm_init();

void pwm_duty_update(int PWM_dutycycle_tick_NEW);
void joystick_input(void);