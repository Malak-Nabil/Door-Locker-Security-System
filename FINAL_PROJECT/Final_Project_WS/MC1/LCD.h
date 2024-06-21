/*
 * Module: LCD
 *
 * Description:Header file for the LCD driver
 */

#ifndef LCD_H_
#define LCD_H_


#include "std_types.h"

/*Definitions*/
/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define DATA_BITS_MODE 8

#if((DATA_BITS_MODE != 4) && (DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD Ports and Pins*/
#define RS_PORT_ID                 PORTA_ID
#define RS_PIN_ID                  PIN1_ID

#define E_PORT_ID                  PORTA_ID
#define E_PIN_ID                   PIN2_ID

#define DATA_PORT_ID               PORTC_ID


#if (DATA_BITS_MODE == 4)

#define DB4_PIN_ID                 PIN0_ID
#define DB5_PIN_ID                 PIN1_ID
#define DB6_PIN_ID                 PIN2_ID
#define DB7_PIN_ID                 PIN3_ID
#endif

/* LCD Commands */
#define CLEAR_COMMAND              		 0x01
#define GO_TO_HOME                		 0x02
#define TWO_LINES_EIGHT_BITS_MODE  	     0x38
#define TWO_LINES_FOUR_BITS_MODE         0x28
#define TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define CURSOR_OFF                       0x0C
#define CURSOR_ON                        0x0E
#define SET_CURSOR_LOCATION              0x80

/*functions prototype*/
/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */

void LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void send_command(uint8 command);

/*
 * Description :
 * Display the required character on the screen
 */
void display_character(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void display_string(const char *Str);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void move_cursor(uint8 row,uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void display_stringRowColumn(uint8 row,uint8 col,const uint8 *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void integer_To_String(uint8 data);

/*
 * Description :
 * Send the clear screen command
 */
void clear_screen(void);

#endif /* H_ */



