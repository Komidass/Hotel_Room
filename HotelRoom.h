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

/*
 * Terminal commands
 */

#define Command_Room_Setup "setup"
#define Command_Check_In   "check-in"
#define Command_Cleaning   "cleaning"
#define Command_Checkout   "check-out"

#define MAX_OPERATION_LEN 20
#define MAX_ROOM_SIZE 9

extern void System(void);
static void HotelEnterRoomNumber(uint8_t Room_Number);
extern void HotelSystem(void);
extern void HotelSystemPrintSwitch(void);
extern void HotelPrintPassword(uint8_t password,uint8_t password_count);
extern void HotelSystemInputSwitch(uint8_t readchar);
extern void HotelTerminal (uint8_t* operation);
static bool RoomSearch(uint8_t room_num);
extern void HotelPrintDefault(void);



#endif /* HOTELROOM_H_ */
