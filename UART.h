/*
 * UART.h
 *
 *  Created on: May 17, 2020
 *      Author: tho
 */

#ifndef UART_H_
#define UART_H_

extern void UART0Init(void);
extern void UARTPrintChar (uint8_t character);
extern uint8_t UARTReadChar (void);
extern void UARTPrintString (uint8_t* string);
extern void UartClearTerminal (void);
extern void UART0IntInit(void);
extern void UartNewLine (void);



#endif /* UART_H_ */
