//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
#include ".\snail_data_types.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PA4 PA5 PA6 PA7 PC4 PC5 PB0
//PA0 PA1 PC3 PC2 PC1 PC0 PC15
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_cfg(void)
{
    GPIO_InitTypeDef GPIO_Init_Data;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOA口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //开启GPIOC口时钟  

    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_4;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_5;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_5);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_6;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_6);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_7;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_7);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_4;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_4);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_5;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_0;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_0;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_1;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_3;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_3);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_2;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_2);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_1;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_1);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_0;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_0);   //输出低电平  
//-----------------------------------------------------------------------------
    GPIO_Init_Data.GPIO_Pin=GPIO_Pin_15;
    GPIO_Init_Data.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init_Data.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC,&GPIO_Init_Data);
    GPIO_ResetBits(GPIOC,GPIO_Pin_15);   //输出低电平  
//-----------------------------------------------------------------------------

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y0(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_4); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y1(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_5); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_5); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y2(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_6); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_6); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y3(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_7); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_7); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y4(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_4); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_4); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y5(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_5); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_5); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y6(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_0); 
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y7(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_0); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_0); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y8(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_1); 
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_1); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y9(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_3); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_3); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y10(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_2); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_2); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y11(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_1); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y12(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_0); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_output_Y13(sdt_bool in_new_put)
{
    if(in_new_put)
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_15); 
    }
    else
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_15); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++