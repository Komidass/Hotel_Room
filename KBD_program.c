/*******************************************************/
/* Author  : Bishoy Medhat                             */
/* Version : V1.0                                      */
/* Date    : 26 FEB 2019                               */
/*******************************************************/
/* Description                                         */
/* ------------                                        */
/* This file has the implementation of both private and*/
/* public function corresponding to Keypad module      */
/*******************************************************/

#include "types.h"
#include"BIT_MATH.h"
#include "DIO_REG.h"
#include "DIO.h"
#include "KBD_config.h"
#include "KBD_interface.h"
#include "KBD_private.h"

u8 keys[16];
u8 pressed;

u8 KBD_u8GetKeyPadState(u8* Copy_Au8KeysState/*[KBD_u8_KEYS_NB]*/)
{
	u8 LOCAL_u8ColIndex = 0;
	u8 LOCAL_u8RowIndex = 0;
	
	u8 Local_u8CurrentPinValue=0;
	u8 Local_u8KeyIndex=0;
	
	// check on Activation type
	#if KBD_u8_ACTIVATION_TYPE==KBD_u8_ACTIVE_COL
		for(LOCAL_u8ColIndex = 0; LOCAL_u8ColIndex < KBD_u8_COL; LOCAL_u8ColIndex ++ )
		{
			//activate current col
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], LOW);
			#else
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], HIGH);
			#endif
			
			//Check on active ROW
			
			for(LOCAL_u8RowIndex = 0; LOCAL_u8RowIndex < KBD_u8_ROWS; LOCAL_u8RowIndex ++)
			{
			    Local_u8CurrentPinValue =  DIO_GetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex]);
				
				Local_u8KeyIndex = LOCAL_u8ColIndex + (LOCAL_u8RowIndex*KBD_u8_COL);
				
				if(Local_u8CurrentPinValue == HIGH)
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#else
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#endif
				}else
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#else
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#endif
				}
			}
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], HIGH);
			#else
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], LOW);
			#endif
		}
	#else
		for(LOCAL_u8RowIndex = 0; LOCAL_u8RowIndex < KBD_u8_ROWS; LOCAL_u8RowIndex ++)
		{
			//activate current row
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], LOW);
			#else
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], HIGH);
			#endif
			
			//Check on active COL
			
			for(LOCAL_u8ColIndex = 0; LOCAL_u8ColIndex < KBD_u8_COL; LOCAL_u8ColIndex ++ )
			{
			    Local_u8CurrentPinValue =  DIO_GetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex]);
				
				Local_u8KeyIndex = LOCAL_u8RowIndex + (LOCAL_u8ColIndex*KBD_u8_ROWS);
				
				if(Local_u8CurrentPinValue == HIGH)
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#else
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#endif
				}else
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#else
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#endif
				}
			}
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], HIGH);
			#else
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], LOW);
			#endif
		}

	#endif

}
void KBD_u8Initialize(u8 group_nb) //initialize keypad active col pull up with Row 4 to be the the 8th pin in the port and col 4 to the 1st pin
	{
    u8 i;
		switch (group_nb)
		{
		case 0:
			DIO_SetPortDirection(PORTA_,0b00001111);
			DIO_Pull_Pin_Up(A4);
            DIO_Pull_Pin_Up(A5);
            DIO_Pull_Pin_Up(A6);
            DIO_Pull_Pin_Up(A7);

			for (i=0;i<4;i++)
			{
				KBD_Au8RowsPins[i] = A4 + i;
				KBD_Au8ColsPins[i] = A3 - i;
			}
			break;
		case 1:
			DIO_SetPortDirection(PORTB_,0b00001111);
            DIO_Pull_Pin_Up(B4);
            DIO_Pull_Pin_Up(B5);
            DIO_Pull_Pin_Up(B6);
            DIO_Pull_Pin_Up(B7);
			for (i=0;i<4;i++)
			{
				KBD_Au8RowsPins[i] = B4 + i;
				KBD_Au8ColsPins[i] = B3 - i;
			}
			break;
		case 2:
			DIO_SetPortDirection(PORTC_,0b00001111);
            DIO_Pull_Pin_Up(C4);
            DIO_Pull_Pin_Up(C5);
            DIO_Pull_Pin_Up(C6);
            DIO_Pull_Pin_Up(C7);
			for (i=0;i<4;i++)
			{
				KBD_Au8RowsPins[i] = C4 + i;
				KBD_Au8ColsPins[i] = C3 - i;
			}
			break;
		case 3:
			DIO_SetPortDirection(PORTD_,0b00001111);
            DIO_Pull_Pin_Up(D4);
            DIO_Pull_Pin_Up(D5);
            DIO_Pull_Pin_Up(D6);
            DIO_Pull_Pin_Up(D7);
			for (i=0;i<4;i++)
			{
				KBD_Au8RowsPins[i] = D4 + i;
				KBD_Au8ColsPins[i] = D3 - i;
			}
			break;
		}
	}

u8 KBD_keys_map(u8* keys)
{
    u8 key_index;
    for(key_index = 0;key_index < KBD_u8_ROWS*KBD_u8_COL;key_index++)
    {
        if (keys[key_index] == KBD_u8_PRESSED) return key_map[key_index];
    }
    return 0xff;
}

