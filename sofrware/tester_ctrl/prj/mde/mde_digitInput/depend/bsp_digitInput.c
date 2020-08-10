//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
#include ".\snail_data_types.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PB12 PB13 PB14 PB15 PC6 PC7 PC8
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_input_port_cfg(void)
{
    GPIO_InitTypeDef GPIO_Init_Data;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOB口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //开启GPIOC口时钟  

    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_12;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_14;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_15;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_6;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_7;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_8;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_input_X0(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
    {
        return(sdt_false);
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X1(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13))
    {
        return(sdt_false);
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X2(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14))
    {
        return(sdt_false);
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X3(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))
    {
        return(sdt_false); 
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X4(void)
{
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
    {
        return(sdt_false); 
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X5(void)
{
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
    {
        return(sdt_false);  
    }
    return(sdt_true);
}
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_input_X6(void)
{
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
    {
        return(sdt_false);
    }
    return(sdt_true);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++