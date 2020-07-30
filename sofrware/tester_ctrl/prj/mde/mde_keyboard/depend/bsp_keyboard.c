//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
#include "stm32f10x.h"
#include "..\mde_keyboard.h"
#include "..\..\mde_digitInput\mde_digitInput.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PG7 PG6 PG5 PG4 --Key1..3
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//static sdt_int16u  physics_keyPin;    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define KeyGroup_PinBits0  (KeyAloneBit1+KeyAloneBit2)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_int16u Pull_KeyPinBits(void)
{
    sdt_int16u ReadPinBits;
    sdt_int16u ReadKeyWordBits;
    
    ReadPinBits=0;
    ReadKeyWordBits=0;
    
    if(mde_pull_input_port(0))
    {
        ReadPinBits |= sdt_bit0;
    }
    if(mde_pull_input_port(2))
    {
        ReadPinBits |= sdt_bit1;
    }
    
    
   // ReadPinBits = physics_keyPin;
    ReadKeyWordBits= ReadPinBits;
//-----------------------------------------------------------------------------
    /*
    if((ReadPinBits&(KeyGroup_PinBits0))==(KeyGroup_PinBits0))  //组合键配置
    {
        ReadKeyWordBits|=KeyGroupBit0;
        Set_MaskOnceKeyBits(KeyGroup_PinBits0);  
    }*/
    return(ReadKeyWordBits);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void BSP_Keyboard_Cfg(void)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void bsp_pushPhysics_pins(sdt_int16u in_keyPins)
{
    //physics_keyPin = in_keyPins;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++