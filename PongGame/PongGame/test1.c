#include "test.h"

void pin_test()
{
	set_bit(DDRB, 0);
    /* Replace with your application code */
    while (1) 
    {
		set_bit(PORTB, 0);
		
		_delay_ms(500);
		
		clear_bit(PORTB, 0);
		
		_delay_ms(500);
    }
}
