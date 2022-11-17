#include "ADC_driver.h"

/**
 * @brief 
 * Set Registers for enabling PWM for use as clock signal
 */
void PWM_Init() {
  set_bit(DDRD, DDD5);

  /* Fast PWM, TOP value = ICR1 */
  set_bit(TCCR1B, WGM13);
  set_bit(TCCR1B, WGM12);
  set_bit(TCCR1A, WGM11);
  clear_bit(TCCR1A, WGM10);

  set_bit(TCCR1A, COM1A1);
  clear_bit(TCCR1A, COM1A0);

  set_bit(TIMSK, TOIE1);

  /* Configuration of the width of the PWM */

  ICR1 = 1;

  OCR1A = (dutyCircle / 100.0) * ICR1;

  /*  */

  clear_bit(TCCR1B, CS12);
  clear_bit(TCCR1B, CS11);
  set_bit(TCCR1B, CS10);
}

void ADC_init(void) {
  // set clock out on MC
  set_bit(DDRD, DDD5);
  set_bit(DDRD, DDD6); /* Enable WR output signal */
  set_bit(DDRD, DDD7); /* Enable RD output signal */

  clear_bit(DDRE, DDE0); /* Set pin PE0 as INPUT to use the INT2 Interrupt for
                            BUSY signal from ADC */

  set_bit(EMCUCR, ISC2); /* Trigger interrupt on rising edge */
  set_bit(GICR, INT2);   /* Enable INT2 interrupt */
}

void ADC_read(uint8_t *ADC_data) {
  float t_BRD = 50E-6;
  float t_RDL = 100E-5;
  float t_RDH = 180E-6;

  int channels = 4;


  _delay_ms(t_BRD);

  for (int i = 0; i < channels; ++i) {
    ADC_data[i] = xmem_read(0x1700);
    _delay_ms(t_RDL + t_RDH);
  }

}
