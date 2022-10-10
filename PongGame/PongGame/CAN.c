#include "CAN.h"

void can_message_send(can_message *message)
{

	mcp2515_write(TXB0SIDH, message->id>>8);
	mcp2515_write(TXB0SIDL, (message->id & 0x0F));
	mcp2515_write(TXB0DLC, message->data_length);
	
	
	
	uint8_t i;
	for (i = 0; i < message->data_length ; i ++)
	{
		mcp2515_write(TXB0D0+i, message->data[i]); 
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0);

	//printf("end of main");
	//message transmitted when TXBnCTRL.TXREQ cleared and CANINTF.TXnIF set

}

can_message can_data_recieve()
{
	can_message message;
	message.id = (mcp2515_read(MCP_RXB0SIDH)<<8) + mcp2515_read(RXB0SIDL);
	message.data_length = mcp2515_read(RXB0DLC);
	
	uint8_t i;
	for (i = 0; i < message.data_length ; i ++)
	{
		 message.data[i] = mcp2515_read(RXB0D0+i);
	}
	
	mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00);
	
	return message;
}