#include "test.h"
#include "ATmega162_driver.h"
#include "ADC_driver.h"
#include "p1000_driver.h"
#include <avr/interrupt.h>
#include "MCP2515_driver.h"
#include "CAN.h"

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


void uart_test()
{
	unsigned char test;
	USART_Init(UBRR);
	stdout = &mystdout;	

	while(1)
	{
		test = USART_RX();
		printf("%c", test);
		_delay_ms(500);
		
		/*
		test = USART_RX();
		USART_TX(test);
		*/
	}
}

void uart_interrupt_test()
{
	// unsigned char test;
	stdout = &mystdout;
	USART_Init(UBRR);
	sei();

	while(1)
	{
		
	}
}

void SRAM_test(void)
{

	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


void decoder_test(void)
{

	while(1)
	{
		xmem_write(0x51, 0x1800);
		_delay_ms(500);
		
		xmem_write(0x51, 0x1F00);
		_delay_ms(500);
		
		xmem_write(0x51, 0x1FFF);
		_delay_ms(500);
		
		xmem_write(0x51, 0x1600);
			_delay_ms(500);
			
	}

}


void ADC_test() 
{
		double dutyCircle = 50;
		
		stdout = &mystdout;
		
		USART_Init(UBRR);
		
		xmem_init();
		
		PWM_Init();
		ADC_init();
		
		ICR1 = 1;
		
		OCR1A = (dutyCircle/100.0)*ICR1;
		
		sei(); // Enable all interrupt
		
		clear_bit(TCCR1B, CS12);
		clear_bit(TCCR1B, CS11);
		set_bit(TCCR1B, CS10);
		
		xmem_write(0x00, 0x1400);
		while(1)
		{
			/* Interrupt handling */
			//ADC_read();
			//xmem_write(0x00, 0x1400);
		}
}

uint8_t ADC_data [4];
void joystick_test()
{
	
		int x_per;
		int y_per;
		pos_t position;
		int calibrated = 0;
		dutyCircle = 50;
		// ADC_data = {0,0,0,0};
		(x_per) = 0;
		(y_per) = 0;
		
		while (1)
		{	
			ADC_read(&ADC_data);
			//printf( "ADC_data[%d] = %d, ADC_data[%d] = %d\n", 0, (int)ADC_data [0],3, (int)ADC_data [3]);	
			joystick_analog_position(&x_per, &y_per, ADC_data, &calibrated);
			position = pos_read(&x_per, &y_per);
			
			slider_position(&x_per, &y_per, ADC_data);
			switch(position)
			{
				case UP:
				printf("UP\n");
				break;
				case DOWN:
				printf("DOWN\n");
				break;
				case RIGHT:
				printf("RIGHT\n");
				break;
				case LEFT:
				printf("LEFT\n");
				break;
				case NEUTRAL:
				printf("NEUTRAL\n");
				break;
				default:
				printf("Not working ?\n");
				break;
			}
		}
}


void oled_print_test()
{
	oled_init();
		
	oled_reset();
		
	char i = 33;
	int co = 0;
	uint8_t page = 0xb0;
	int page_count =0;
		
	oled_home();
		
	_delay_ms(1);
	while(1)
	{
		if(i > 126)
		{
			i = 33;
		}
			
		if(co >= 127)
		{
			++page;
			++page_count;
			if(page_count > 7){
					
				oled_reset();
				page = 0xb0;
				page_count=0;
			}
			xmem_write(page, 0x1000);
			co = 0;
		}
			
		write_char(i);
		//write_char(32); // print space
		++i;
		co += 8;
	}
}

extern int y_arrow;
extern int page_arrow;

/*
	uint8_t size_arrow;
	
	float x_per;
	float y_per;
	pos_t position;
	int calibrated = 0;
	dutyCircle = 50;

	(x_per) = 0;
	(y_per) = 0;


	stdout = &mystdout;

	USART_Init(UBRR);
	
	xmem_init();
	
	PWM_Init();
	ADC_init();
	
	sei(); // Enable all interrupt
	*/
void oled_movement_test()
{
		uint8_t size_arrow;
		
		float x_per;
		float y_per;
		pos_t position;
		int calibrated = 0;
	size_arrow = 1;
	page_arrow = 2;
	y_arrow = 0;
	position = 0;
	pushButton_init();
	oled_init();
	oled_reset();
	
	oled_home();
	//
	//oled_home();
	
	go_to_page(2);
	go_to_col(30);
	oled_print("Start");
	go_to_page(3);
	go_to_col(30);
	oled_print("PingPong");
	go_to_page(4);
	go_to_col(30);
	oled_print("End game");
	
	//oled_home();
	
	
	oled_print_arrow(page_arrow, y_arrow, 0);
	
	while (1)
	{
		joystick_analog_position(&x_per, &y_per, ADC_data, &calibrated);
		position = pos_read(&x_per, &y_per);
		
		// slider_position(&x_per, &y_per, ADC_data);
		switch(position)
		{
			case UP:
			printf("UP\n");
			oled_print_arrow(page_arrow, y_arrow, 1);
			page_arrow -= size_arrow;
			if(page_arrow < 0) page_arrow = 7;
			oled_print_arrow(page_arrow, y_arrow, 0);
			break;
			case DOWN:
			printf("DOWN\n");
			oled_print_arrow(page_arrow, y_arrow, 1);
			page_arrow += size_arrow;
			if(page_arrow > 7) page_arrow = 0;
			oled_print_arrow(page_arrow, y_arrow, 0);
			break;
			case RIGHT:
			printf("RIGHT\n");
			
			oled_print_arrow(page_arrow, y_arrow, 1);
			y_arrow += 5;
			oled_print_arrow(page_arrow, y_arrow, 0);
			break;
			
			case LEFT:
			
			printf("LEFT\n");
			oled_print_arrow(page_arrow, y_arrow, 1);
			y_arrow -= 5;
			oled_print_arrow(page_arrow, y_arrow, 0);
			break;
			
			case NEUTRAL:
			printf("NEUTRAL\n");
			break;
			default:
			printf("Not working ?\n");
			break;
		}
		
		_delay_ms(1);
	}	
}


void test_CAN()
{
	can_message message1;
	can_message message2;
	
	message1.id = 1;
	message1.data_length = 3;
	message1.data[0] = 'H';
	message1.data[1] = 'I';
	message1.data[2] = '!';
	
	message2.id = 2;
	message2.data_length = 3;
	message2.data[0] = 'B';
	message2.data[1] = 'Y';
	message2.data[2] = 'E';
	/*
	char data;
	data = mcp2515_read_status();
	
	printf("status before send 0x%02X \n", data);
	*/
		while(1){
			can_message_send(&message2);
			_delay_ms(100);
			
			can_message_send(&message1);
			_delay_ms(100);
				/*
				can_message read_message;
				
				read_message = can_data_recieve();
				_delay_ms(2);
				
				//data = mcp2515_read_status();
				
				//printf("status after read 0x%02X \n", data);
				printf("message data read %c%c%c %d\n", read_message.data[0], read_message.data[1], read_message.data[2], read_message.id);
				*/
		}

}