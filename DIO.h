/*
 * DIO.h
 *
 *  Created on: Feb 26, 2020
 *      Author: PI
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

/* Port Defines */
#define PORTA_   0
#define PORTB_   1
#define PORTC_   2
#define PORTD_   3
#define PORTE_   4
#define PORTF_   5

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0


#define A0  0
#define A1  1
#define A2  2
#define A3  3
#define A4  4
#define A5  5
#define A6  6
#define A7  7
#define B0  8
#define B1  9
#define B2  10
#define B3  11
#define B4  12
#define B5  13
#define B6  14
#define B7  15
#define C0  16
#define C1  17
#define C2  18
#define C3  19
#define C4  20
#define C5  21
#define C6  22
#define C7  23
#define D0  24
#define D1  25
#define D2  26
#define D3  27
#define D4  28
#define D5  29
#define D6  30
#define D7  31
#define E0  32
#define E1  33
#define E2  34
#define E3  35
#define E4  36
#define E5  37
#define E6  38
#define E7  39
#define F0  40
#define F1  41
#define F2  42
#define F3  43
#define F4  44
#define F5  45
#define F6  46
#define F7  47


void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir) ;
void DIO_PortInit (u8 u8PortId);
void DIO_Pull_Pin_Up (u8 Pin);
void DIO_Pull_Pin_Down (u8 Pin);
void DIO_SetPinDirection (u8 Pin, u8 u8PinDirCopy);

void DIO_SetPinValue(u8 Pin, u8 u8PinValCopy);
u8 DIO_GetPinValue(u8 Pin) ;
void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal) ;



#endif /* INC_DIO_H_ */
