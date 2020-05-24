/*
 * EEPROM.h
 *
 *  Created on: Mar 4, 2020
 *      Author: thomas
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#define EESIZE      *((volatile int *)0x400AF000)
#define EEBLOCK     *((volatile int *)0x400AF004)
#define EEOFFSET    *((volatile int *)0x400AF008)
#define EERDWR      *((volatile int *)0x400AF010)
#define EERDWRINC   *((volatile int *)0x400AF014)
#define EEDONE      *((volatile int *)0x400AF018)
#define EESUPP      *((volatile int *)0x400AF01C)
#define EEUNLOCK    *((volatile int *)0x400AF020)
#define EEPROT      *((volatile int *)0x400AF030)
#define EEPASS0     *((volatile int *)0x400AF034)
#define EEPASS1     *((volatile int *)0x400AF038)
#define EEPASS2     *((volatile int *)0x400AF03C)
#define EEDBGME     *((volatile int *)0x400AF080)

#define WORKING 0
#define WRBUSY  5
#define NOPERM  4

#define PRETRY 3
#define ERETRY 2
#define START  0

#define NO_ERROR    0
#define EESUP_ERROR 1
#define Read_Error 1
#define Write_Error 1
#define ME 0
#define KEY 0xE37B

#define EEPROM_LOCKED 1
#define EEPROM_UNLOCKED 0
u8 EEPROM_Init(void);
u8 EEPROM_READ(u32* Read_Data ,u32 Block_Add,u32 Word_Add,u32 Word_Num);
u8 EEPROM_Write(u32* Write_Data ,u32 Block_Add,u32 Word_Add,u32 Word_Num);
u8 EEPROM_Set_Password(u32* Password);
u8 EEPROM_Lock(void);
u8 EEPROM_Unlock(u32* Password);
void EEPROM_Mass_Erase(void);
u8 EEPROM_Get_Lock_State(void);

extern u8 Init_Error;
extern u8 Set_Password_Error;
extern u8 Lock_Error;
extern u8 Unlock_Error;
extern u8 Lock_State;



#endif /* EEPROM_H_ */
