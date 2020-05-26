

/**
 * main.c
 */
#include"BIT_MATH.h"
#include <stdint.h>
#include <stdbool.h>
#include "types.h"
#include "DIO.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm_modified.h"
#include "driverlib/cpu.h"
#include "UART.h"
#include "EEPROM.h"
#include "HotelRoom.h"
#include "stdlib.h"
#include "KBD_interface.h"

uint8_t keys[16];
uint8_t pressed;
uint8_t DebugVar = 0;
//extern volatile uint8_t* uart_input_buffer;
extern bool occupied;

int main(void)
{

    /*
     * enable GPIOA ,GPIOF,GPIOB and UART0 modules
     */
    HWREG(SYSCTL_RCGCGPIO_R) = SYSCTL_RCGCGPIO_R5|SYSCTL_RCGCGPIO_R0|SYSCTL_RCGCGPIO_R1;
    HWREG(SYSCTL_RCGCUART_R) = SYSCTL_RCGCUART_R0;
    /*
     * configure UART0 for PA0 and PA1
     */
    HWREG(GPIO_PORTA_AFSEL_R) = PIN0|PIN1;
    HWREG(GPIO_PORTA_PCTL_R) = (1 << 0) | (1 << 4);
    HWREG(GPIO_PORTA_DEN_R)= PIN0 | PIN1;

    HWREG(GPIO_PORTF_DEN_R) = 0xE;
    HWREG(GPIO_PORTF_DIR_R) = 0xE;
    HWREG(GPIO_PORTB_DEN_R) = 0xff;
    UART0Init();
    UART0IntInit();
    KBD_u8Initialize(PORTB_);
    uint8_t  Init_Error = EEPROM_Init();
    EEPROM_Mass_Erase();
    HWREGBITW(GPIO_PORTF_DATA_R,1) = 1;
    HotelPrintDefault();
    uint8_t pass_count = 0;
    uint32_t password = 0;
    while(1)
    {
        if (occupied && (pressed != 0xff))
        {


            SysCtlDelay(16000000/5);
            password |= ((0x00|pressed) << pass_count*8);
            HotelPrintPassword(pressed, pass_count+1);
            pass_count ++;
            if (pass_count == 4)
            {
                EEPROM_Unlock(&password);
                password = 0;
                pass_count = 0;
                UartNewLine();
                if (EEPROM_Get_Lock_State() == EEPROM_LOCKED)
                {
                    UARTPrintString("Guest entered an incorrect password and room is still locked");
                }
                else
                {
                    UARTPrintString("Guest entered a correct password and room is now unlocked");
                }
                UartNewLine();
            }

        }
        KBD_u8GetKeyPadState(keys);
        pressed = KBD_keys_map(keys);
        if (EEPROM_Get_Lock_State() == EEPROM_LOCKED)
        {
            HWREGBITW(GPIO_PORTF_DATA_R,1) = 1;
            HWREGBITW(GPIO_PORTF_DATA_R,3) = 0;
        }
        else
        {
            HWREGBITW(GPIO_PORTF_DATA_R,1) = 0;
            HWREGBITW(GPIO_PORTF_DATA_R,3) = 1;
        }
    }

	return 0;
}
