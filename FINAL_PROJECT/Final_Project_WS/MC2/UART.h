
/*
 * Module: UART
 *
 * Description: Header file for the UART driver
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"


typedef enum{
	BIT_DATA_5,BIT_DATA_6,BIT_DATA_7,BIT_DATA_8,BIT_DATA_9=7
}UART_BitData;

typedef enum{
	STOP_BIT_1,STOP_BIT_2
}UART_StopBit;

typedef enum{
	NONE,RESERVED,EVEN,ODD
}UART_Parity;

typedef struct{
		UART_BitData bit_data;
		UART_Parity parity;
		UART_StopBit stop_bit;
		uint32 baud_rate;
}UART_ConfigType;

void UART_init(const UART_ConfigType *Config_Ptr);

void UART_SendByte(uint8 data);

uint8 UART_RecieveByte();

void UART_SendString();

void UART_RecieveString();

#endif /* UART_H_ */
