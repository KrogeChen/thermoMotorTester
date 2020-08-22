//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\snail_macro.h"
#include ".\snail_data_types.h"
#include "stm32f10x.h"
#include ".\bsp_mutilpt100.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PB9 -- select0
//PB8 -- select1
//PB7 -- select2
//PB6 -- DRDY
//PB5 -- DOUT(MISO)
//PB4 -- DIN(MOSI)
//PB3 -- SCLK
//--------------------------------------------------------------------------------------------------------------------------
#define sel_0_GPIO    GPIOB
#define sel_0_Pin     GPIO_Pin_9
#define sel_1_GPIO    GPIOB
#define sel_1_Pin     GPIO_Pin_8
#define sel_2_GPIO    GPIOB
#define sel_2_Pin     GPIO_Pin_7
#define DRDY_GPIO     GPIOB
#define DRDY_Pin      GPIO_Pin_6
#define DOUT_GPIO     GPIOB
#define DOUT_Pin      GPIO_Pin_5
#define DIN_GPIO      GPIOB
#define DIN_Pin       GPIO_Pin_4
#define SCLK_GPIO     GPIOB
#define SCLK_Pin      GPIO_Pin_3
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_mutilpt100_cfg(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOB口时钟

    GPIO_InitTypeDef    gpit_init; 
 //-----------------------------------------------------------------------------   
//-----------------------------------------------------------------------------  
    gpit_init.GPIO_Pin   = sel_0_Pin;                     //PB9
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_Out_PP;              //推挽输出
    GPIO_Init(sel_0_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = sel_1_Pin;                     //PB8
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_Out_PP;              //推挽输出
    GPIO_Init(sel_1_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = sel_2_Pin;                     //PB7
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_Out_PP;              //推挽输出
    GPIO_Init(sel_2_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = DRDY_Pin;                      //PB6
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_IPU;                 //输入上拉
    GPIO_Init(DRDY_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = DOUT_Pin;                     //PB5
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_IPU;                //输入上拉
    GPIO_Init(DOUT_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = DIN_Pin;                     //PB4
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_Out_PP;             //推挽输出
    GPIO_Init(DIN_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    gpit_init.GPIO_Pin   = SCLK_Pin;                     //PB3
    gpit_init.GPIO_Speed = GPIO_Speed_2MHz;
    gpit_init.GPIO_Mode  = GPIO_Mode_Out_PP;             //推挽输出
    GPIO_Init(SCLK_GPIO,&gpit_init);
//-----------------------------------------------------------------------------
    bsp_push_select_4051(0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------------------------------------------------------------------
void bsp_push_select_4051(sdt_int8u in_way)
{
    switch(in_way)
    {
        case 0:
        {
            GPIO_ResetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_ResetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_ResetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 1:
        {
            GPIO_SetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_ResetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_ResetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 2:
        {
            GPIO_ResetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_SetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_ResetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 3:
        {
            GPIO_SetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_SetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_ResetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 4:
        {
            GPIO_ResetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_ResetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_SetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 5:
        {
            GPIO_SetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_ResetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_SetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 6:
        {
            GPIO_ResetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_SetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_SetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        case 7:
        {
            GPIO_SetBits(sel_0_GPIO,sel_0_Pin);
            GPIO_SetBits(sel_1_GPIO,sel_1_Pin);
            GPIO_SetBits(sel_2_GPIO,sel_2_Pin);
            break;
        }
        default:
        {
            break;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_ads1220_DRDY(void)
{
    if(DRDY_GPIO->IDR & DRDY_Pin)
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: SCLK 电平设置
//in: sdt_true 高电平，
void bsp_push_ads1220_SCLK(sdt_bool in_newState)
{
    if(in_newState)
    {
        GPIO_SetBits(SCLK_GPIO,SCLK_Pin);
    }
    else
    {
        GPIO_ResetBits(SCLK_GPIO,SCLK_Pin);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: MOSI 电平设置
//in: sdt_true 高电平，
void bsp_push_ads1220_MOSI(sdt_bool in_newState)
{
    if(in_newState)
    {
        GPIO_SetBits(DIN_GPIO,DIN_Pin);
    }
    else
    {
        GPIO_ResetBits(DIN_GPIO,DIN_Pin);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: CS 电平设置
//in: sdt_true 高电平，
void bsp_push_ads1220_CS(sdt_bool in_newState)
{
    if(in_newState)
    {

    }
    else
    {

    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 获取MOSI的电平
//out:  sdt_ture 高电平，sdt_false 低电平
sdt_bool bsp_pull_ads1220_MISO(void)
{
    if(DOUT_GPIO->IDR & DOUT_Pin)
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
