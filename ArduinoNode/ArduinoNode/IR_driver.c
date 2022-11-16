#include "IR_driver.h"

/**
 * @brief 
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

/**
 * @brief 
 * 
 */
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
 * @brief 
 * 
 * @return int 
 */
int IR_read(void) {
  int adc_out = (int)(ADC->ADC_LCDR & ADC_LCDR_LDATA_Msk);

  if (adc_out < 200) {
    return 0;
  }
  // printf("no goal \n");
  return 1;
}

/**
 * @brief 
 * 
 * @param score 
 * @param no_goal_counter 
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
