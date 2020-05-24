

/**
 * main.c
 */
#include"BIT_MATH.h"
#include <stdint.h>
#include <stdbool.h>
#include "types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm_modified.h"
#include "driverlib/cpu.h"
#include "UART.h"
#include "EEPROM.h"
#include "HotelRoom.h"

uint8_t DebugVar = 0;

int main(void)
{


    /*
     * enable GPIOA ,GPIOF and UART0 modules
     */
    HWREG(SYSCTL_RCGCGPIO_R) = SYSCTL_RCGCGPIO_R5|SYSCTL_RCGCGPIO_R0;
    HWREG(SYSCTL_RCGCUART_R) = SYSCTL_RCGCUART_R0;
    /*
     * configure UART0 for PA0 and PA1
     */
    HWREG(GPIO_PORTA_AFSEL_R) = PIN0|PIN1;
    HWREG(GPIO_PORTA_PCTL_R) = (1 << 0) | (1 << 4);
    HWREG(GPIO_PORTA_DEN_R)= PIN0 | PIN1;

    HWREG(GPIO_PORTF_DEN_R) = 0xE;
    HWREG(GPIO_PORTF_DIR_R) = 0xE;
    UART0Init();
    UART0IntInit();
    uint8_t  Init_Error = EEPROM_Init();
    EEPROM_Mass_Erase();

    while(1)
    {
        HotelSystemInput();
    }

	return 0;
}
