#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stdint.h"  // dy el library el feha el data types .... zay el uint32_t......badal ma ana a7otha fe .h file lw7dha w asameha std_types.h....
#include "common_macros.h"
#include "tm4c123gh6pm.h"


#define N_col 4
#define N_row 4
#define KeyPad_Rows_DATA        GPIO_PORTD_DATA_R 
#define KeyPad_Rows_DIR         GPIO_PORTD_DIR_R
#define KeyPad_Columns_DIR      GPIO_PORTC_DIR_R 
#define KeyPad_Columns_Data     GPIO_PORTC_DATA_R

/***  functions proto types *///
uint32_t Keypad_getPressedKey(void);
#endif /*KEYPAD_H_*/
