
/*
 * Module: EEPROM
 *
 * Description: Source file for the EEPROM driver
 */

#include"EEPROM.h"
#include"I2C.h"
#include <util/delay.h>
uint8 EEPROM_writeByte(uint16 address,uint8 data)
{

	TWI_start();
	if(TWI_getStatus() != START)
	{
		return ERROR;
	}
	//send first A10,A9,A8
	TWI_writeByte((uint8)(0xA0 | ((address & 0x0700)>>7)));
	if(TWI_getStatus() != SALVEADDRESS_WRITE_WITH_ACK)
	{
		return ERROR;
	}
	//Send the address
	TWI_writeByte((uint8)(address));
	if(TWI_getStatus() != SEND_DATA_WITH_ACK )
	{
		return ERROR;
	}
	//send data
	TWI_writeByte(data);
	if(TWI_getStatus() != SEND_DATA_WITH_ACK )
	{
		return ERROR;
	}
	TWI_stop();
	_delay_ms(10);
	return SUCCESS;
}
uint8 EEPROM_readByte(uint16 address,uint8 * data)
{
	TWI_start();
	if(TWI_getStatus() != START)
	{
		return ERROR;
	}
	//send first A10,A9,A8
	TWI_writeByte((uint8)(0xA0 | ((address & 0x0700)>>7)));
	if(TWI_getStatus() != SALVEADDRESS_WRITE_WITH_ACK)
	{
		return ERROR;
	}
	//Send the address
	TWI_writeByte((uint8)(address));
	if(TWI_getStatus() != SEND_DATA_WITH_ACK )
	{
		return ERROR;
	}
	TWI_start();
	if(TWI_getStatus() != REPEATED_START)
	{
		return ERROR;
	}
	TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7) | 1));
	if(TWI_getStatus() != SALVEADDRESS_READ_WITH_ACK)
	{
		return ERROR;
	}
	*data=TWI_readByteWithNACK();
	if(TWI_getStatus() != DATA_RECIEVED_WITHOUT_ACK )
	{
		return ERROR;
	}
	TWI_stop();
	_delay_ms(10);
	return SUCCESS;
}
