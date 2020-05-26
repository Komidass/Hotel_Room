# Hotel_Room
A terminal like hotel room system using the ARM-Cortex M4F
It communicates with the receptionist PC using UART and it with the guest using a 4x4 keypad

/**********************************************************************************************/

!!!!!!!!!!
commands :
!!!!!!!!!!

/**********************************************************************************************/
setup 

this command takes the number of rooms available in the hotel which are available for checking in.

example of usage :

setup 1,5,3

sets up the rooms availble to 1,5,3
NOTE: dont use room 0

/**********************************************************************************************/

check-in

this  command takes the  number of the room you want to check-in then asks for a 4 character password to set it up , then locks the room.
if the room number entered was not set up it gives the receptionist a warning.
if this command is used again before the check-out of the room it re-locks the room

example of usage :

check-in 1

/**********************************************************************************************/

cleaning 

this command takes the number of the room and unlocks it  for cleaning, if the room number entered is not the one which is checked in it gives the receptionist a warning.

example of usage :

cleaning 1

/**********************************************************************************************/

check-out

this command takes the number of the room and checks-out the room and makes it available again for checking-in, if the room number entered is not the one which is checked in it gives the receptionist a warning.

example of usage :

check-out 1

/**********************************************************************************************/
