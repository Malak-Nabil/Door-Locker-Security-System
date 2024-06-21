
/*
 * Module: I2C
 *
 * Description: Source file for the I2C driver
 */

#include"I2C.h"
#include <avr/io.h>
#include"gpio.h"
#include"common_macros.h"

void TWI_init(const TWI_ConfigType * Config_Ptr)
{

	//TWPS=00 using prescaler 1
	TWSR=00; //Initialized to 0 before starting I2C communication to make sure that there are no prior status bits set.
	TWAR=(TWAR & 0X00) | (Config_Ptr->address);
	TWBR=(F_CPU/(Config_Ptr->bit_rate))-16;
	TWCR|=(1<<TWEN);

}

void TWI_start()
{

	TWCR =(1<<TWSTA) | (1<<TWINT) | (1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){}
}

void TWI_stop()
{
	TWCR =(1<<TWSTO) | (1<<TWINT) | (1<<TWEN);


}

void TWI_writeByte(uint8 data)
{
	TWDR=data;//clear the flag by itself ,sets register TWWC
	TWCR =(1<<TWINT) | (1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){}
}
uint8 TWI_readByteWithACK()
{
	TWCR=(1<<TWEA) | (1<<TWEN) | (1<<TWINT) ;

	while(BIT_IS_CLEAR(TWCR,TWINT)){}/*Without waiting for the TWINT flag,
	                                   you might read the data before it is received completely*/
	return TWDR;
}
uint8 TWI_readByteWithNACK()
{
	TWCR=(1<<TWEN) | (1<<TWINT) ;

	while(BIT_IS_CLEAR(TWCR,TWINT)){}/*Without waiting for the TWINT flag,
									   you might read the data before it is received completely*/
	return TWDR;

}
uint8 TWI_getStatus()
{
	uint8 status;
	status=TWSR & 0xF8; //status checking independent of prescaler setting
	return status;

}
