//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
#include ".\snail_macro.h"
#include ".\snail_data_types.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//A--PC9-- EXTI9;
//B--PA11--EXTI11;
//Z--PA12--EXTI12;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(pulse_queue,64);
static sdt_int8u pulse_abz;
#define pulseBits_a   0x04
#define pulseBits_b   0x02
#define pulseBits_z   0x01
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_gratingMeasure_cfg(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

/* Enable GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Configure PC.09 pin as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

/* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure PA.11 pin as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* Configure PA.12 pin as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
//-------------------------------------------------------------------------------
//  get A B Z first status
    pulse_abz = 0;
    if(GPIOC->IDR & 0x0200)  //PC9
    {
        pulse_abz |= pulseBits_a;
    }
    if(GPIOA->IDR & 0x0800)  //PA11
    {
        pulse_abz |= pulseBits_b;
    }
    if(GPIOA->IDR & 0x1000) //PA12
    {
        pulse_abz |= pulseBits_z;
    }
//-------------------------------------------------------------------------------
    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* Connect EXTI9 Line to PC.09 pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
    
    /* Configure EXTI9 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
   
    /* Enable and set EXTI9-5 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /* Configure EXTI11 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Connect EXTI11 Line to PA.11 pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
    
    /* Configure EXTI14 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
   
    /* Connect EXTI11 Line to PA.12 pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);

    /* Enable and set EXTI15-10Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//------------------------------------------------------------------------------
}
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetFlagStatus(EXTI_Line9))
    {
        if(GPIOC->IDR & 0x0200) //PC9 //读取端口状态
        {
            pulse_abz |= pulseBits_a;

        }
        else
        {
            pulse_abz &= ~pulseBits_a;
        }
        macro_push_queueBasce_data(pulse_queue,pulse_abz);
        EXTI_ClearITPendingBit(EXTI_Line8); 
    }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{   
    if(EXTI_GetFlagStatus(EXTI_Line11))
    {
        if(GPIOA->IDR & 0x0800) //PA11 //读取端口状态
        {
            pulse_abz |= pulseBits_b;
        }
        else
        {
            pulse_abz &= ~pulseBits_b;
        }
        macro_push_queueBasce_data(pulse_queue,pulse_abz);
        EXTI_ClearITPendingBit(EXTI_Line11); 
    }
    
    if(EXTI_GetFlagStatus(EXTI_Line12))
    {
        if(GPIOA->IDR & 0x1000) //PA12 //读取端口状态
        {
            pulse_abz |= pulseBits_z;
        }
        else
        {
            pulse_abz &= ~pulseBits_z;
        }
        macro_push_queueBasce_data(pulse_queue,pulse_abz);
        EXTI_ClearITPendingBit(EXTI_Line12); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_pulse_status(sdt_int8u* pulse_ABZ)
{
   sdt_int8u nBytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(pulse_queue,nBytes);
    __enable_interrupt();
    if(nBytes)
    {
        __disable_interrupt();
        sdt_int8u rd_data;
        macro_pull_queueBasce_data(pulse_queue,rd_data);
        __enable_interrupt();
        *pulse_ABZ = rd_data;
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++