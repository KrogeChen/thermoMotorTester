//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\snail_data_types.h"
#include "stm32f10x.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//PA12
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_led_dark(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_12);  
}
//-----------------------------------------------------------------------------
void bsp_led_light(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_12);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_led_runStatus_cfg(void)
{
    GPIO_InitTypeDef   GPIO_Init_Data;
        
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOB口时钟  
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_12;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_12);   //输出低电平  
//-----------------------------------------------------------------------------
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++