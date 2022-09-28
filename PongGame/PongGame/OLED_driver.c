#include "OLED_driver.h"

void oled_init()
{

	xmem_write(0xae, 0x1000); // display off
	xmem_write(0xa1, 0x1000); //segment remap
	xmem_write(0xda, 0x1000); //common pads hardware: alternative
	xmem_write(0x12, 0x1000);
	xmem_write(0xc8, 0x1000); //common output scan direction:com63~com0
	xmem_write(0xa8, 0x1000); //multiplex ration mode:63
	xmem_write(0x3f, 0x1000);
	xmem_write(0xd5, 0x1000); //display divide ratio/osc. freq. mode
	xmem_write(0x80, 0x1000);
	xmem_write(0x81, 0x1000); //contrast control
	xmem_write(0x50, 0x1000);
	xmem_write(0xd9, 0x1000); //set pre-charge period
	xmem_write(0x21, 0x1000);
	xmem_write(0x20, 0x1000); //Set Memory Addressing Mode
	xmem_write(0x02, 0x1000);
	xmem_write(0xdb, 0x1000); //VCOM deselect level mode
	xmem_write(0x30, 0x1000);
	xmem_write(0xad, 0x1000); //master configuration
	xmem_write(0x00, 0x1000);
	xmem_write(0xa4, 0x1000); //out follows RAM content
	xmem_write(0xa6, 0x1000); //set normal display
	
	//xmem_write(0xb0, 0x1000);
	//xmem_write(0x00, 0x1000);

	//xmem_write(0xa5, 0x1000);
	
	xmem_write(0xaf, 0x1000); // display on
}
/*
void OLED_pos(int row, int col){
	
	xmem_write()
};
	*/
	