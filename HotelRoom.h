/*
 * HotelRoom.h
 *
 *  Created on: May 18, 2020
 *      Author: tho
 */

#ifndef HOTELROOM_H_
#define HOTELROOM_H_

/*
 *  States of the FSM
 */
#define State_Enter_Room_Number 0
#define State_Enter_Room_Number_Input 1
#define State_Set_Room_Password 2
#define State_Set_Room_Password_Input 3
#define State_Set_Room_Status 4
#define State_Set_Room_Status_Input 5
#define State_Guest_Enter_Password 6

#define Room_Occupied '1'
#define Room_Cleaning '2'
#define Room_Free '3'

extern void System(void);
static void HotelEnterRoomNumber(uint8_t Room_Number);
extern void HotelSystem(void);
extern void HotelSystemInput(void);
extern void HotelPrintPassword(uint8_t password,uint8_t password_count);



#endif /* HOTELROOM_H_ */
