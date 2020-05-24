/*
 * HotelRoom.c
 *
 *  Created on: May 18, 2020
 *      Author: tho
 */
#include"BIT_MATH.h"
#include "types.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm_modified.h"
#include "driverlib/cpu.h"
#include "UART.h"
#include "EEPROM.h"
#include "HotelRoom.h"

extern uint8_t DebugVar;
uint8_t state = 0;
uint8_t statebeginning = 1;
uint32_t password = 0;
uint8_t room_number = 0;
uint8_t password_count;
uint8_t Set_Password_Error;
uint8_t readchar  = 0xff;
uint8_t Lock_Error;
uint8_t Lock_State;
uint8_t Unlock_Error;
static void HotelPrintDefault(void)
{
    UartClearTerminal();
    SysCtlDelay(500);
    UARTPrintString("**************************\n\r");
    UARTPrintString("The Five Seasons Hotel\n\r");
    UARTPrintString("**************************\n\r");
}


extern void HotelSystem(void)
{

}


extern void HotelSystemInput(void)
{
    switch (state) {
        case State_Enter_Room_Number:
            if (statebeginning)
            {
                HotelPrintDefault();
                UARTPrintString("please enter number of room\n\r");
                statebeginning = 0;
            }
            break;

        case State_Set_Room_Password:
            if(statebeginning)
            {
                HotelPrintDefault();
                UARTPrintString("please set a  4 character password for room ");
                UARTPrintChar(room_number);
                UARTPrintString("\n\r");
                statebeginning = 0;

            }
            break;

        case State_Set_Room_Status:
            if(statebeginning)
            {
                HotelPrintDefault();
                UARTPrintString("Please select the state of room ");
                UARTPrintChar(room_number);
                UARTPrintString("\n\r1- Room Occupied  2-Room is being cleaned  3-Room is free\n\r");
                statebeginning = 0;
            }
            break;

        default:
            break;
    }
}

extern void HotelPrintPassword(uint8_t password,uint8_t password_count)
{
    uint8_t x ;
    UARTPrintChar(password);
    UARTPrintChar('\r');
    SysCtlDelay(16000000 /(5*3));
    for ( x = 0; x < password_count; x++)
    {
        UARTPrintChar('*');
    }
}






