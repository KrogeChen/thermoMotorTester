//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
//-------------------------------------------------------------------------------
#include ".\depend\bsp_keyboard.h"
#include ".\mde_keyboard.h"
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_int16u   LastKeyWord;
static sdt_int16u   KeyWordOfChange;   //当前改变值
static sdt_int16u   KeyWordOfState;    //当前状态值
static sdt_int16u   MaskOnceKeyWord;   //屏蔽一次按键
static sdt_int16u   KeyInContinue;     //连续检测该键

macro_createTimer(KeyFLongDaley,timerType_millisecond,0);//首次长延时
macro_createTimer(KeyCShortDaley,timerType_millisecond,0);//连击短延时
//-------------------------------------------------------------------------------
sdt_bool Pull_KeyboardEvent_Task(void)
{
    macro_createTimer(KeyScanTime,timerType_millisecond,0);
    static sdt_int8u ChangeCnt;   //电平改变计数
    static sdt_int8u StateCnt;    //电平状态值计数
    sdt_int16u ReadKeyWord;
    
    pbc_timerClockRun_task(&KeyFLongDaley);
    pbc_timerClockRun_task(&KeyCShortDaley);
    pbc_timerClockRun_task(&KeyScanTime);
//-------------------------------------------------------------------------------
    if(pbc_pull_timerIsCompleted(&KeyScanTime))
    {
        pbc_reload_timerClock(&KeyScanTime,2);
        
        ReadKeyWord=Pull_KeyPinBits();
        if(ReadKeyWord^LastKeyWord)
        {
            StateCnt=0;
            ChangeCnt++;
            if(ChangeCnt>5)
            {
                ChangeCnt=0;
                KeyWordOfChange=ReadKeyWord^LastKeyWord;
                LastKeyWord=ReadKeyWord;
                KeyWordOfState=ReadKeyWord;
                return(sdt_true);
            }
        } 
        else
        {
            ChangeCnt=0;
            if(ReadKeyWord!=0)
            {
                StateCnt++;
                if(StateCnt>5)
                {
                    StateCnt=0;
                    KeyWordOfState=ReadKeyWord;
                    return(sdt_true);
                }
            }
            else
            {
                ChangeCnt=0;
                StateCnt=0;
                KeyWordOfState=0;
                MaskOnceKeyWord=0;
                KeyInContinue=0;
            }
        }
    }
    return(sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
KeyRetValue_Def Pull_KeyVauleStatus(sdt_int8u _In_KeyNumber,sdt_int16u _In_CosFristTime,sdt_int16u _In_CosRepetTime)
{
    sdt_int16u KeyInBits;
    
    KeyInBits = 0x0001;
    KeyInBits = KeyInBits<<_In_KeyNumber;
    
    if(MaskOnceKeyWord&KeyInBits)
    {
        return(KeyNone);
    }
    if(KeyInContinue&KeyInBits)  //处理该键的连续按键
    {
        if(KeyWordOfChange&KeyInBits)
        {
            KeyWordOfChange=0;
            if(KeyWordOfState&KeyInBits)
            {
            }
            else
            {
                return(KeyPushUp);
            }
        }
        if(KeyWordOfState&KeyInBits)
        {
            if((0==KeyFLongDaley.timClock)&&(0==KeyCShortDaley.timClock))
            {
                KeyCShortDaley.timClock=_In_CosRepetTime;
                return(KeyContinuousDown);
            }
        } 
    }
    else  //处理单击按键
    {
        if(KeyWordOfChange&KeyInBits)
        {
            KeyWordOfChange=0;
            if(MaskOnceKeyWord&KeyInBits)
            {
                MaskOnceKeyWord&=~KeyInBits;
                return(KeyNone);
            }    
            else if(KeyWordOfState&KeyInBits)
            {
                if(_In_CosFristTime==NOCONTINUE)
                {
                    KeyFLongDaley.timClock=0;
                    KeyCShortDaley.timClock=0;
                    return(KeyPushDown); 
                }
                else
                {
                    KeyInContinue|=KeyInBits;
                    KeyFLongDaley.timClock=_In_CosFristTime;
                    KeyCShortDaley.timClock=0;
                    return(KeyPushDown);  
                }                  
            }
            else
            {
                return(KeyPushUp);
            }
        }        
    }
    return(KeyNone);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//屏蔽一次按键
//-----------------------------------------------------------------------------
void Set_MaskOnceKeyBits(sdt_int16u _In_KeyPinBits)
{
    MaskOnceKeyWord|=_In_KeyPinBits;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Set_MaskOnceKeyNumber(sdt_int8u _In_KeyNumber)
{
    MaskOnceKeyWord|=(0x0001<<_In_KeyNumber);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void ReCapture_DownKeyNumber(sdt_int8u _In_KeyNumber)
{
    LastKeyWord&=~(0x0001<<_In_KeyNumber);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_pushPhysics_keyPins(sdt_int16u in_keyPins)
{
    bsp_pushPhysics_pins(in_keyPins);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++