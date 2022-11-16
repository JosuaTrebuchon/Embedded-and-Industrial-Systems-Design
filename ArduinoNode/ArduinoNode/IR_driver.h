#include "adc.h"
#include "printf-stdarg.h"
#include "sam.h"

void peripheral_init_adc(void);

void ADC_init(void);

int IR_read(void);

void check_for_score(int *score, int *no_goal_counter);
