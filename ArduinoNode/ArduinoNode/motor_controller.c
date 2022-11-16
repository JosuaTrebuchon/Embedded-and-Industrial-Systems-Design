#include "motor_controller.h"

#define F_CPU 84000000L

P1000_DATA P1000_data;
pidData_t pid;

void slider_open_loop() {
  // printf("pos %d\n", *pos);
  if (P1000_data.left_slider < 128) {
    // CODR = Clear Output Data Register
    PIOD->PIO_CODR |= (0x1 << 10);
    DACC->DACC_CDR = 0x9FF;
  }

  else {
    // SODR = Set Output Data Register
    PIOD->PIO_SODR |= (0x1 << 10); //&= ~(0x200);
    DACC->DACC_CDR = 0x9FF;
  }
}

void init_motor_position() {
  // SODR = Set Output Data Register
  PIOD->PIO_SODR |= (0x1 << 10); // Set direction to right
  DACC->DACC_CDR = 0xCFF;

  Delay(2000);

  DACC->DACC_CDR = 0x0;

  Delay(100);

  reset_encoder();
}

void Delay(int num) {
  volatile float f = 1.0f;

  for (volatile int i = 0; i < 1024 * num; ++i)

    f *= 1.1f;
}

void motor_init() {
  /*Pull up */
  PIOC->PIO_PUDR |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) |
                    (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);
  PIOD->PIO_PUDR |=
      (0x1 << 10) | (0x1 << 9) | (0x1 << 2) | (0x1 << 1) | (0x1 << 0);

  /* Enable PIOC clock */
  PMC->PMC_PCER0 |= PMC_PCER0_PID13;
  /* Enable PIOD clock */
  PMC->PMC_PCER0 |= PMC_PCER0_PID14;

  /*Enable MJ1 pins*/
  PIOD->PIO_PER |= 0x607;

  /*Enable MJ1 pins as outputs*/
  PIOD->PIO_OER |= 0x607;

  /*MJ1 output to 1*/
  PIOD->PIO_SODR |=
      (0x1 << 10) | (0x1 << 9) | (0x1 << 2) | (0x1 << 1) | (0x1 << 0); // 0x607;

  /*Clock divider*/
  // PMC->PMC_PCR |= (0x1 << 28) | (0x1 << 12) | (0xd << 0);

  /*Enable MJ2 pins (C1 to C8)*/
  PIOC->PIO_PER |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) |
                   (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);

  /*Disable MJ2 pins as output */
  PIOC->PIO_ODR |= (0x1 << 8) | (0x1 << 7) | (0x1 << 6) | (0x1 << 5) |
                   (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);
}

uint16_t read_encoder() {
  uint16_t encoder = 0;

  /* Clearing the not OE (Encoder output enable) */
  PIOD->PIO_CODR |= (0x1 << 0);

  /* Setting SEL low to output high byte */
  PIOD->PIO_CODR |= (0x1 << 2);

  Delay(20); // delay_20ms();// for(int i = 0; i < 1680000; i++); //
             // _delay_ms(20); change this

  encoder = (((PIOC->PIO_PDSR & MJ2_DATA_Msk) >> 1) << 8);

  /* Setting SEL high to output low byte */
  PIOD->PIO_SODR |= (0x1 << 2);

  Delay(20); // for(int i = 0; i < 1680000; i++); // _delay_ms(20);

  encoder += ((PIOC->PIO_PDSR & MJ2_DATA_Msk) >> 1);

  /* Setting the not OE (Encoder output enable) high */
  PIOD->PIO_SODR |= (0x1 << 0);

  return encoder;
}

void move_to_setpoint() {
  int speed = 0;
  int dir = 0;
  /*percentage of slider*/
  uint16_t setPoint = 100 * ((float)P1000_data.left_slider / 255.0);
  // setPoint = 50;
  int16_t measured_value = read_encoder();
  if ((measured_value > 8600) && (measured_value < 30000)) {
    measured_value = 8600;
  }

  if ((measured_value < 0) && (measured_value > 30000)) {
    measured_value = 0;
  }

  uint16_t motor_per = 100 * ((float)measured_value / 8600.0);

  int16_t motor_input = pid_Controller(setPoint, motor_per, &pid);
  if (motor_input > 100) {
    motor_input = 100;
  }

  if (motor_input < -100) {
    motor_input = -100;
  }

  if (motor_input > 0) {
    PIOD->PIO_CODR |= (0x1 << 10); // Set direction to right
    dir = 1;
  }
  if (motor_input < 0) {
    PIOD->PIO_SODR |= (0x1 << 10); // Set direction to left
    dir = 0;
  }

  if (motor_input < 0)
    motor_input *= -1;

  speed = ((0xFFF - 0x450) * ((float)motor_input / 100.0)) + 0x450; // min 580

  if (motor_input == 0) {
    // DACC->DACC_CDR = 0x00;
    speed = 0x00;
  }

  DACC->DACC_CDR = speed;

  // printf("setpoint: %d measured: %d pid out: %d, speed: %d dir: %d",
  // setPoint, motor_per, motor_input, speed, dir);
}

void reset_encoder(void) {
  /* Clearing the not RST (Reset encoder) */
  PIOD->PIO_CODR |= (0x1 << 1);

  Delay(1);

  /* Setting the not RST high (Normal state) */
  PIOD->PIO_SODR |= (0x1 << 1);
}

void solenoid_init() {
  /* Enable PIOC12 */
  PIOC->PIO_PER |= (0x1 << 12);

  /* Enable PIOC12 as output */
  PIOC->PIO_OER |= (0x1 << 12);

  // PIOC->PIO_PUER |= (0x1 << 12);

  /* Set PIOC12 high PIN51*/
  PIOC->PIO_SODR |= (0x1 << 12);
}

void solenoid_impulse() {
  /* Set PIOC12 Low PIN51*/
  PIOC->PIO_CODR |= (0x1 << 12);

  Delay(100);

  /* Set PIOC12 High PIN51*/
  PIOC->PIO_SODR |= (0x1 << 12);

  // Delay(270);
  Delay(500);
}
