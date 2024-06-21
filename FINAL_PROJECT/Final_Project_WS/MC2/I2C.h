
/*
 * Module: I2C
 *
 * Description: Header file for the I2C driver
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

#define START         	  				 0x08
#define REPEATED_START	                 0x10
#define SALVEADDRESS_WRITE_WITH_ACK	 	 0x18//master transmitted slave address and write request with ack received from slave
#define SALVEADDRESS_WRITE_WITHOUT_ACK	 0x20//master transmitted slave address and write request without ack received from slave
#define SALVEADDRESS_READ_WITH_ACK	 	 0x40//master transmitted slave address and read request with ack received from slave
#define SALVEADDRESS_READ_WITHOUT_ACK	 0x48//master transmitted slave address and read request withOUT ack received from slave
#define DATA_RECIEVED_WITH_ACK           0X50//Master received data and send ACK to slave.
#define DATA_RECIEVED_WITHOUT_ACK        0X58//Master received data without sending ACK to slave.
#define SEND_DATA_WITH_ACK               0x28 //Master transmit data and ACK has been received from Slave
#define SEND_DATA_WITHOUT_ACK            0x30 //Master transmit data without receiving ack from slave



typedef struct{
 uint16 address;
 uint32 bit_rate;
}TWI_ConfigType;

void TWI_init(const TWI_ConfigType * Config_Ptr);

void TWI_start();
void TWI_stop();
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK();
uint8 TWI_readByteWithNACK();
uint8 TWI_getStatus();

#endif /* I2C_H_ */
