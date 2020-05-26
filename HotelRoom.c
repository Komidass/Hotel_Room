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
#include "string.h"


extern uint8_t DebugVar;
volatile uint8_t state = 0;
uint8_t statebeginning = 1;
uint32_t password = 0;
uint8_t room_number = 0;
uint8_t password_count;
uint8_t Set_Password_Error;
uint8_t readchar  = 0xff;
uint8_t Lock_Error;
uint8_t Lock_State;
uint8_t Unlock_Error;
uint8_t Room_Numbers[MAX_ROOM_SIZE] = {0};
uint8_t RoomCheckedIn = 0;
bool    occupied = 0;
//extern volatile uint8_t* uart_input_buffer;
extern void HotelPrintDefault(void)
{
    UartClearTerminal();
    SysCtlDelay(500);
    UARTPrintString("**************************\n\r");
    UARTPrintString("The Five Seasons Hotel\n\r");
    UARTPrintString("**************************\n\r");
}

static bool RoomSearch(uint8_t room_num)
{
    uint8_t loop_count = 0;
    for (loop_count = 0;loop_count < MAX_ROOM_SIZE ;loop_count++)
    {
        if(Room_Numbers[loop_count] == room_num) return 1;

    }
    return 0;
}



extern void HotelTerminal (uint8_t* operation)
{
    uint8_t loop_count = 0;
    uint8_t* command;
    uint8_t* argument;
    uint8_t* token;
    token = strtok(operation," ");
    command = token;
    token = strtok(NULL," ");
    argument = token;
    if (strcmp(command, Command_Room_Setup) == 0)
    {
        token = strtok(argument, ",");
        while (token != NULL)
        {
            Room_Numbers[loop_count] = token[0];
            token = strtok(NULL, ",");
            loop_count ++;
        }
        UartNewLine();
        UARTPrintString("setting up rooms was successful");
        UartNewLine();
    }
    else if (strcmp(command, Command_Check_In) == 0)
    {
        if (occupied && (RoomCheckedIn == argument[0]))
        {
            Lock_Error = EEPROM_Lock();
            UartNewLine();
            if (EEPROM_Get_Lock_State() == EEPROM_LOCKED) UARTPrintString("room is now locked");
            UartNewLine();
        }
        else
        {
            if (RoomSearch(argument[0]))
            {
                occupied = 1;
                RoomCheckedIn = argument[0];
                UartNewLine();
                UARTPrintString("Please setup a 4 number password for room ");
                UARTPrintChar(RoomCheckedIn);
                UartNewLine();
                for (loop_count = 0;loop_count < 4 ; loop_count ++)
                {
                    readchar = UARTReadChar();
                    password |= ((0x00|readchar) << loop_count*8);
                    HotelPrintPassword(readchar, loop_count+1);
                }
                Set_Password_Error = EEPROM_Set_Password(&password);
                Lock_Error = EEPROM_Lock();
                UartNewLine();
                if (EEPROM_Get_Lock_State() == EEPROM_LOCKED) UARTPrintString("Password successfully set and room is now locked");
                UartNewLine();
            }
            else
            {
                UartNewLine();
                UARTPrintString("Please enter a correct room number");
                UartNewLine();
            }
        }


    }
    else if (strcmp(command, Command_Cleaning) == 0)
    {
        if ((RoomCheckedIn == argument[0]) && occupied)
        {
            Unlock_Error = EEPROM_Unlock(&password);
            UartNewLine();
            if (EEPROM_Get_Lock_State() != EEPROM_LOCKED) UARTPrintString("Room is now unlocked for cleaning");
            UartNewLine();
        }
        else
        {
            UartNewLine();
            UARTPrintString("Room number is incorrect or room is not occupied");
            UartNewLine();
        }
    }
    else if (strcmp(command, Command_Checkout) == 0)
    {
        if ((RoomCheckedIn == argument[0]) && occupied)
        {
            EEPROM_Mass_Erase();
            UartNewLine();
            UARTPrintString("Room check out successful");
            password = 0;
            RoomCheckedIn = 0;
            occupied = 0;
        }
        else
        {
            UartNewLine();
            UARTPrintString("Room number is incorrect or room is not occupied");
            UartNewLine();
        }
    }
    else
    {
        UartNewLine();
        UARTPrintString("\n\rUnrecognized command");
        UartNewLine();
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



