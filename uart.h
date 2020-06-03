

#ifndef UART_H_
#define UART_H_

#include "stdint.h"  // dy el library el feha el data types .... zay el uint32_t......badal ma ana a7otha fe .h file lw7dha w asameha std_types.h....
#include "tm4c123gh6pm.h"
#include "common_macros.h"



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(void);

void UART_sendByte(uint8_t data);

uint8_t UART_recieveByte(void);



#endif /* UART_H_ */
