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
            else
            {
                readchar = UARTReadChar();
                room_number = readchar;
                state = State_Set_Room_Password;
                statebeginning = 1;
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
            else
            {
                readchar = UARTReadChar();
                password |= ((0x00|readchar) << password_count*8);
                password_count++;
                HotelPrintPassword(readchar, password_count);
                if (password_count == 4)
                {
                    Set_Password_Error = EEPROM_Set_Password(&password);
                    Lock_Error = EEPROM_Lock();
                    Lock_State = EEPROM_Get_Lock_State();
                    if (Set_Password_Error == NO_ERROR) UARTPrintString("\n\rPassword succefully set\n\r");
                    password_count = 0;
                    state = State_Set_Room_Status;
                    statebeginning = 1;
                }

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
            else
            {
                readchar = UARTReadChar();
                UARTPrintChar(readchar);
                UARTPrintString("\n\r");
                switch (readchar) {
                    case Room_Occupied:
                    if(Lock_State == EEPROM_LOCKED) UARTPrintString("Room is locked\n\r");
                        break;
                    case Room_Cleaning:
                        Unlock_Error = EEPROM_Unlock(&password);
                        if(Unlock_Error == NO_ERROR) UARTPrintString("Room is unlocked for cleaning\n\r");
                        break;
                    case Room_Free:
                        EEPROM_Mass_Erase();
                        UARTPrintString("Room ");
                        UARTPrintChar(room_number);
                        UARTPrintString(" is now free\n\r");
                        password = 0;
                        room_number = 0;
                        SysCtlDelay(16000000*4/3);
                        state = State_Enter_Room_Number;
                        statebeginning = 1;
                        break;
                     default:
                        statebeginning = 1;
                        break;

                }
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






