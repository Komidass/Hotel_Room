/*
 * UART.c
 *
 *  Created on: May 17, 2020
 *      Author: tho
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm_modified.h"
#include "driverlib/cpu.h"
#include "HotelRoom.h"
extern uint8_t DebugVar;




void UART0_INT_Handler(void)
{

    DebugVar = 1;
    //was there a receive interrupt ?
    if (HWREGBITW(UART0_MIS_R,4) == 1)
    {
        //clear the interrupt flag
        HWREGBITW(UART0_ICR_R,4) = 1;
        while (HWREGBITW(UART0_FR_R,4 ) == 1)
        {

        }

        if (HWREG(UART0_DR_R) == 't')
        {

        }

    }
}
extern void UARTPrintChar (uint8_t character)
{
    while (HWREGBITW(UART0_FR_R,5) == 1)
    {

    }
    HWREG(UART0_DR_R) = character;
}
extern uint8_t UARTReadChar (void)
{
    uint8_t character;
    while (HWREGBITW(UART0_FR_R,4 ) == 1)
    {

    }
    character =  HWREG(UART0_DR_R);
    return character;
}
/*
 *  this function configures UART0 and enables it's interrupt
 */
extern void UARTPrintString (uint8_t* string)
{
    while (*string != '\0')
    {
        UARTPrintChar(*string);
        string ++;
    }
}
extern void UART0Init(void)
{
    /*
     * Disabling the UART module
     * Setting up the UART for UART0 , with the same frequency that I set for the MCU
     * with 9600 baudrate with the integer part equal to 104 and the fraction part equal to 11
     * and sending 8 bits , one stop bit and no parity bit
     *
     * calculating the baud rate divisor BDR for 16Mhz and 9600 baud rate:
     * BRD = 16,000,000 / (16 * 9600) = 104.166666667
     * DIVINT = 104
     * UARTFBRD[DIVFRAC] = integer(0.166666667 * 64 + 0.5) = 11
     * Re-enabling the UART module
     */

    HWREG(UART0_CTL_R) = 0x00;
    HWREG(UART0_IBRD_R) = 104;
    HWREG(UART0_FBRD_R) = 11;
    HWREG(UART0_LCRH_R) = 0x60;
    HWREG(UART0_CC_R) = 0x0;
    HWREG(UART0_CTL_R) = (1 << 9)|(1 << 8)|(1 << 0);


}

extern void UART0IntInit(void)
{
    /*
     * UART0 interrupt initializing
     */
    //UART0 receive interrupt enable from UART0 interrupt mask reg
    HWREGBITW(UART0_IM_R,4) = 1;
    //from NVIC IRQ table UART0 is 5
    //HWREGBITW(NVIC_EN0_R,5) = 1;
    HWREG(NVIC_EN0_R) = (1 << 5);
    //enable uart,receive,transmit
    //enable global interrupt
    CPUcpsie();
}
extern void UartClearTerminal (void)
{
    UARTPrintChar(12);
}





