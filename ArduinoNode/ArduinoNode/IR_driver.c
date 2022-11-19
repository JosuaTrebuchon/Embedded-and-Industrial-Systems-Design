#include "IR_driver.h"

/**
 * @brief Set peripheral pin and enable clock to use IR on Arduino due
 * 
 */
void peripheral_init_adc() {
  // pin A11
  // CH11

  PIOB->PIO_PDR |= PIO_PDR_P18;
  // Using peripheral B of PIOC11
  // PIOA ->PIO_ABSR |= PIO_ABSR_P11;

  /* Enable clock for the PWM peripheral */
  PMC->PMC_PCER1 |= PMC_PCER1_PID37;
}

void ADC_init(void) {
  /*Reset ADC*/
  ADC->ADC_CR |= ADC_CR_SWRST;

  /*Disable write protect mode*/
  ADC->ADC_WPMR |= ~ADC_WPMR_WPEN;
  /*Enable channel 11*/
  ADC->ADC_CHER |= ADC_CHER_CH11;

  /*Set to 10-bit resolution*/
  ADC->ADC_MR |= (1 << 0x4);

  /*Put in free run mode*/
  ADC->ADC_MR |= ADC_MR_FREERUN_ON;

  /*Interrupt on end of conversion CH11*/
  ADC->ADC_IER |= ADC_IER_EOC11;

  ADC->ADC_EMR |= ADC_EMR_TAG;
}

/**
 * @brief Returns 0 if goal, 1 if not
 * 
 * @return int 
 */
int IR_read(void) {
  int adc_out = (int)(ADC->ADC_LCDR & ADC_LCDR_LDATA_Msk);

  if (adc_out < 200) {
    return 0;
  }
  
  return 1;
}

/**
 * @brief Keeps track of score. Delay added to prevent multiple goals in a row
 * 
 * @param score Total score
 * @param no_goal_counter Counter must be over 10 iterations for next goal to count
 */
void check_for_score(int *score, int *no_goal_counter) {

  int no_goal = IR_read();
  *no_goal_counter = *no_goal_counter + no_goal;

  if (*no_goal_counter > 10 && no_goal == 0) {
    (*score)++;
    printf("GOAL! score = %d\n", *score);
    *no_goal_counter = 0;
  }
}
