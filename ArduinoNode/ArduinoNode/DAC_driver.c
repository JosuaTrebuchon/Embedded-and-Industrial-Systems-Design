#include "DAC_driver.h"

/**
 * @brief Set registers to enable DAC on Arduino Due
 * 
 */
void DACC_init(void) {
  PMC->PMC_PCER1 |= PMC_PCER1_PID38;

  /*Reset DACC*/
  DACC->DACC_CR |= DACC_CR_SWRST;

  /*Select CH1*/
  DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;

  /*Enable CH1*/
  DACC->DACC_CHER |= DACC_CHER_CH1;
}
