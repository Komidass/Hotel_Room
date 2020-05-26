#include  "types.h"
#include  "BIT_MATH.h"
#include "DIO.h"
#include "DIO_REG.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"

volatile u32* DIO_OutRegisters [6] = {GPIO_PORTA_DATA_REG,GPIO_PORTB_DATA_REG,GPIO_PORTC_DATA_REG,GPIO_PORTD_DATA_REG,GPIO_PORTE_DATA_REG , GPIO_PORTF_DATA_REG};

volatile u32* DIO_DirRegisters [6] = {GPIO_PORTA_DIR_REG , GPIO_PORTB_DIR_REG , GPIO_PORTC_DIR_REG , GPIO_PORTD_DIR_REG, GPIO_PORTE_DIR_REG , GPIO_PORTF_DIR_REG};

volatile u32* DIO_AfselRegisters [6] = {GPIO_PORTA_AFSEL_REG , GPIO_PORTB_AFSEL_REG ,GPIO_PORTC_AFSEL_REG, GPIO_PORTD_AFSEL_REG, GPIO_PORTE_AFSEL_REG, GPIO_PORTF_AFSEL_REG};

volatile u32* DIO_DEN_Registers [6] = {GPIO_PORTA_DEN_REG,GPIO_PORTB_DEN_REG , GPIO_PORTC_DEN_REG , GPIO_PORTD_DEN_REG , GPIO_PORTE_DEN_REG , GPIO_PORTF_DEN_REG};

volatile u32* DIO_Lock_Registers [6] = {GPIO_PORTA_LOCK_REG,GPIO_PORTB_LOCK_REG,GPIO_PORTC_LOCK_REG,GPIO_PORTD_LOCK_REG,GPIO_PORTE_LOCK_REG,GPIO_PORTF_LOCK_REG};

volatile u32* DIO_Commit_Registers [6] = {GPIO_PORTA_CR_REG,GPIO_PORTB_CR_REG,GPIO_PORTC_CR_REG,GPIO_PORTD_CR_REG,GPIO_PORTE_CR_REG,GPIO_PORTF_CR_REG};
volatile u32* DIO_Amsel_Registers [6] = {GPIO_PORTA_AMSEL_REG , GPIO_PORTB_AMSEL_REG , GPIO_PORTC_AMSEL_REG , GPIO_PORTD_AMSEL_REG , GPIO_PORTE_AMSEL_REG , GPIO_PORTF_AMSEL_REG};

volatile u32* DIO_Port_Control_Registers [6] = {GPIO_PORTA_PCTL_REG,GPIO_PORTB_PCTL_REG,GPIO_PORTC_PCTL_REG,GPIO_PORTD_PCTL_REG,GPIO_PORTE_PCTL_REG,GPIO_PORTF_PCTL_REG};

volatile u32* DIO_Port_Pull_Up [6] = {GPIO_PORTA_PUR_REG , GPIO_PORTB_PUR_REG , GPIO_PORTC_PUR_REG , GPIO_PORTD_PUR_REG , GPIO_PORTE_PUR_REG , GPIO_PORTF_PUR_REG};

volatile u32* DIO_Port_Pull_Down [6] = {GPIO_PORTA_PDR_REG , GPIO_PORTB_PDR_REG , GPIO_PORTC_PDR_REG , GPIO_PORTD_PDR_REG , GPIO_PORTE_PDR_REG , GPIO_PORTF_PDR_REG};




void DIO_PortInit (u8 u8PortId){

        SET_BIT(*SYSCTL_RCGCGPIO_REG,u8PortId);

        // unlock the Port
        *DIO_Lock_Registers[u8PortId] = 0x4C4F434B;
        //commit registers
        *DIO_Commit_Registers [u8PortId] = 0xff;
        // digital enable
        *DIO_DEN_Registers[u8PortId] = 0xff;
        // not analog
         *DIO_Amsel_Registers[u8PortId] = 0x00;

}

void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir) {

        // alternative selcet for the port
        *DIO_AfselRegisters[u8PortId] = 0x00;

        // control reg
        *DIO_Port_Control_Registers[u8PortId] = 0x00;
        *DIO_DirRegisters[u8PortId] = u8PortDir;






}


void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal) {

    *DIO_OutRegisters [u8PortId] = u8PortVal;
}



void DIO_Pull_Pin_Up (u8 Pin){

    u8 u8PortId = Pin/8;
    u8  u8PinIdCopy = Pin%8;
    SET_BIT(*DIO_Port_Pull_Up[u8PortId],u8PinIdCopy);

}


void DIO_Pull_Pin_Down (u8 Pin){

    u8 u8PortId = Pin/8;
    u8  u8PinIdCopy = Pin%8;
    SET_BIT(*DIO_Port_Pull_Down[u8PortId],u8PinIdCopy);

}

void DIO_SetPinDirection (u8 Pin, u8 u8PinDirCopy){

            u8 u8PortId = Pin/8;
            u8  u8PinIdCopy = Pin%8;
            if ( u8PinDirCopy == OUTPUT )
                {
                SET_BIT(*DIO_DirRegisters[u8PortId],u8PinIdCopy);
                }

            if ( u8PinDirCopy == INPUT )
                {
                CLR_BIT(*DIO_DirRegisters[u8PortId],u8PinIdCopy);
                }


}

void DIO_SetPinValue(u8 Pin, u8 u8PinValCopy) {

    u8 u8PortIdCopy = Pin/8;
    u8  u8PinIdCopy = Pin%8;
    if (u8PinValCopy == HIGH)
            {
                SET_BIT(*DIO_OutRegisters[u8PortIdCopy],u8PinIdCopy);
            }

            else if (u8PinValCopy == LOW)
            {
                CLR_BIT(*DIO_OutRegisters[u8PortIdCopy],u8PinIdCopy);
            }

}

u8 DIO_GetPinValue(u8 Pin) {
    u8 u8PortIdCopy = Pin/8;
    u8  u8PinIdCopy = Pin%8;
    u8   u8ResultLocal= GET_BIT(*DIO_OutRegisters[u8PortIdCopy],u8PinIdCopy);
    return u8ResultLocal;
}

