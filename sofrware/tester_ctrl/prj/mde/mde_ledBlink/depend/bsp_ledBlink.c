//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\snail_data_types.h"
#include "stm32f10x.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//PA12
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_led_dark(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_13);  
}
//-----------------------------------------------------------------------------
void bsp_led_light(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
//-----------------------------------------------------------------------------
void bsp_led_s_dark(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_14);  
}
//-----------------------------------------------------------------------------
void bsp_led_s_light(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_14);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_led_runStatus_cfg(void)
{
    GPIO_InitTypeDef   GPIO_Init_Data;
        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //开启GPIOC口时钟  
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_14;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_14);   //输出低电平  
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++