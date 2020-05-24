#include "types.h"
#include "BIT_MATH.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "EEPROM.h"
#include "EEPROM_P.h"

u8 EEPROM_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    SysCtlDelay(2);
    Wait_EEDONE_Working();
    if(GET_BIT(EESUPP,PRETRY)|GET_BIT(EESUPP,ERETRY))
    {
        return EESUP_ERROR;
    }
    SysCtlPeripheralReset(SYSCTL_PERIPH_EEPROM0);
    Wait_EEDONE_Working();
    if(GET_BIT(EESUPP,PRETRY)|GET_BIT(EESUPP,ERETRY))
    {
        return EESUP_ERROR;
    }
    return NO_ERROR;

}

static void Wait_EEDONE_Working(void)
        {
            while(GET_BIT(EEDONE,WORKING))
            {

            }
        }

u8 EEPROM_READ(u32* Read_Data ,u32 Block_Add,u32 Word_Add,u32 Word_Num)

{
    u32 counter;
    EEBLOCK = Block_Add;
    EEOFFSET = Word_Add;

    if(EEBLOCK != Block_Add) return Read_Error;


    if(EEOFFSET != Word_Add) return Read_Error;


    for(counter = 0;counter< Word_Num;counter++)
    {
        *Read_Data = EERDWRINC;
        if (*Read_Data == 0xffffffff) return Read_Error;
        *Read_Data++;
        if(Word_Num && (EEOFFSET == 0))
        {
            EEBLOCK +=1;
        }
    }
    return NO_ERROR;

}

u8 EEPROM_Write(u32* Write_Data ,u32 Block_Add,u32 Word_Add,u32 Word_Num)
{
    u32 counter;
    EEBLOCK = Block_Add;
    EEOFFSET = Word_Add;

    while(GET_BIT(EEDONE,WRBUSY))
    {

    }

    for(counter = 0;counter< Word_Num;counter++)
    {
        EERDWRINC = *Write_Data;
        if (GET_BIT(EEDONE,NOPERM)) return Read_Error;
        *Write_Data++;
        SysCtlDelay(5);
        while(GET_BIT(EEDONE,WRBUSY))
        {

        }
        if(Word_Num && (EEOFFSET == 0))
        {
            EEBLOCK +=1;
        }
    }
    while(GET_BIT(EEDONE,WORKING))
    {

    }
    return NO_ERROR;

}



u8 EEPROM_Set_Password(u32* Password)
{
    EEBLOCK = 1;
    if(EEBLOCK != 1) return Write_Error;

   //
    if(GET_BIT(EEDONE,NOPERM) == 1)  return Write_Error;
    if(EEPASS0 == 0x1)  return Write_Error;
    EEPASS0 = *Password;
    while(GET_BIT(EEDONE,WORKING))
    {

    }
    return NO_ERROR;

}

u8 EEPROM_Lock(void)
{
    EEBLOCK = 1;
    if(EEBLOCK != 1) return Write_Error;
    EEUNLOCK = 0xffffffff;
    if (EEUNLOCK == 1) return Write_Error;
    if (EEUNLOCK == 0) return NO_ERROR;
    return NO_ERROR;
}

u8 EEPROM_Unlock(u32* Password)
{
    EEBLOCK = 1;
    if(EEBLOCK != 1) return Write_Error;

    EEUNLOCK = 0xffffffff;
    EEUNLOCK = *Password;

    while(GET_BIT(EEDONE,WORKING))
    {

    }

    if (EEUNLOCK == 0) return Write_Error;
    if (EEUNLOCK == 1) return NO_ERROR;

    return NO_ERROR;

}
void EEPROM_Mass_Erase(void)
{

    EEDBGME = 0xE37B0001;
    while(GET_BIT(EEDBGME,ME)|GET_BIT(EEDONE,WORKING))
    {

    }
    SysCtlPeripheralReset(SYSCTL_PERIPH_EEPROM0);
    SysCtlDelay(2);
    Wait_EEDONE_Working();
}
u8 EEPROM_Get_Lock_State(void)
{
    EEBLOCK = 1;
    if(EEUNLOCK == 0) return EEPROM_LOCKED;
    if(EEUNLOCK == 1) return EEPROM_UNLOCKED;

}

