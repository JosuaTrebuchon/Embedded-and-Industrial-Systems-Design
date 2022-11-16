#include "ATmega162_driver.h"

void USART_Init(unsigned int ubrr) {
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);

  /* Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0B |=
      (1 << RXCIE0); // Enable the USART Receive Complete interrupt (USART_RXC)

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

void USART_TX(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;

  UDR0 = data;
}

unsigned char USART_RX() {
  while (!(UCSR0A & (1 << RXC0)))
    ;

  return UDR0;
}

/*
        Links printf to UART
        Uses code from this source:
        https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaea2b6be92ead4673bc487b271b7227fb
*/
FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
int uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

void xmem_init(void) {
  // set_bit(SFIOR, XMM2);
  // clear_bit(SFIOR, XMM1);
  // clear_bit(SFIOR, XMM0);
  // set_bit(MCUCR, SRE);
  MCUCR |= (1 << SRE); // THIS MFER
  SFIOR |= (1 << XMM2);
}

void xmem_write(uint8_t data, uint16_t addr) {

  stdout = &mystdout;
  volatile char *ext_mem = (char *)BASE_ADDRESS;
  ext_mem[addr] = data;
  uint8_t retreived_value = ext_mem[addr];
  // printf( "value stored at ext_mem[0x%08x] is 0x%08x, should be 0x%08x\n",
  // addr, retreived_value, data);
}
uint8_t xmem_read(uint16_t addr) {
  volatile char *ext_mem = (char *)BASE_ADDRESS;
  uint8_t ret_val = ext_mem[addr];
  return ret_val;
}

void pushButton_init() {
  clear_bit(
      DDRD,
      DDD2); // set PD2 as Input to use the INT0 Interrupt for Joystick button

  set_bit(PORTD, DDD2); // Set pull-up resistor ON -> high level on input

  clear_bit(MCUCR, ISC00); /* Trigger interrupt on falling edge */
  clear_bit(MCUCR, ISC01);

  set_bit(GICR, INT0); /* Enable INT0 interrupt */
}

void interrupt_MCP2515_init() {
  clear_bit(DDRD, DDD3); // set PD3 as Input to use the INT1 Interrupt for CAN
                         // controller interrupt

  set_bit(PORTD, DDD3); // Set pull-up resistor ON -> high level on input

  clear_bit(MCUCR, ISC10); /* Trigger interrupt on falling edge */
  clear_bit(MCUCR, ISC11);

  set_bit(GICR, INT1); /* Enable INT1 interrupt */
}
