//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//基于ADS1220+4051 的PT100测量模块
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
#include ".\depend\bsp_mutilpt100.h"
#include ".\mde_mutilpt100.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//模拟spi模块
typedef struct 
{
    void(*mpp_push_spi_CS)(sdt_bool in_newState);
    void(*mpp_push_spi_SCLK)(sdt_bool in_newState);
    void(*mpp_push_spi_MOSI)(sdt_bool in_newState);
    sdt_bool(*mpp_pull_spi_MISO)(void);
}sim_spi_oop_def;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取一个字节，从spi总线
//--------------------------------------------------------------------------------------------------------------------------
static sdt_int8u sim_spi_read_one_byte(sim_spi_oop_def* pMix_oop)
{
    sdt_int8u read_byte = 0;
    sdt_int8u mask_bit = 0x80;
    pMix_oop->mpp_push_spi_SCLK(sdt_false);

    while(mask_bit)
    {
        pMix_oop->mpp_push_spi_SCLK(sdt_true);
        if(pMix_oop->mpp_pull_spi_MISO())
        {
            read_byte |= mask_bit;
        }
        pMix_oop->mpp_push_spi_SCLK(sdt_false); 
        mask_bit = mask_bit >> 1;       
    }
    return(read_byte);
}
//--------------------------------------------------------------------------------------------------------------------------
//写入一个字节的数据到spi总线
//--------------------------------------------------------------------------------------------------------------------------
static void sim_spi_write_one_byte(sim_spi_oop_def* pMix_oop,sdt_int8u in_byte)
{
    sdt_int8u mask_bit = 0x80;
    pMix_oop->mpp_push_spi_SCLK(sdt_false);
    while(mask_bit)
    {
        pMix_oop->mpp_push_spi_SCLK(sdt_true);
        if(in_byte & mask_bit)
        {
            pMix_oop->mpp_push_spi_MOSI(sdt_true);
        }
        else
        {
            pMix_oop->mpp_push_spi_MOSI(sdt_false);
        }
        pMix_oop->mpp_push_spi_SCLK(sdt_false); 
        mask_bit = mask_bit >> 1;       
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//写入ads1220寄存器内容
//--------------------------------------------------------------------------------------------------------------------------
static void ads1220_write_register(sim_spi_oop_def* pMix_oop,sdt_int8u in_reg_addr,sdt_int8u in_reg_length,sdt_int8u* pIn_details)
{
    if(((in_reg_addr + in_reg_length) > 4) || (0 == in_reg_length))
    { //illegal
    }
    else
    {
        sdt_int8u command = 0x40;
        sdt_int8u i;
        command |= (in_reg_addr << 2);
        command |= (in_reg_length - 1);
        sim_spi_write_one_byte(pMix_oop,command);
        for(i = 0;i < in_reg_length;i++)
        {
            sim_spi_write_one_byte(pMix_oop,*pIn_details);
            pIn_details++;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取ads1220寄存器内容
//--------------------------------------------------------------------------------------------------------------------------
static void ads1220_read_register(sim_spi_oop_def* pMix_oop,sdt_int8u in_reg_addr,sdt_int8u in_reg_length,sdt_int8u* pOut_details)
{
    if(((in_reg_addr + in_reg_length) > 4) || (0 == in_reg_length))
    { //illegal
    }
    else
    {
        sdt_int8u command = 0x20;
        sdt_int8u i;
        command |= (in_reg_addr << 2);
        command |= (in_reg_length - 1);
        sim_spi_write_one_byte(pMix_oop,command);
        for(i = 0;i < in_reg_length;i++)
        {
            *pOut_details = sim_spi_read_one_byte(pMix_oop);
            pOut_details++;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取adc转换值
//--------------------------------------------------------------------------------------------------------------------------
static sdt_int32u ads1220_read_adc_value(sim_spi_oop_def* pMix_oop)
{
    sdt_int8u rd_adc[3] = {0,0,0};
    sdt_int32u adc_value = 0;

    rd_adc[0] = sim_spi_read_one_byte(pMix_oop);
    rd_adc[1] = sim_spi_read_one_byte(pMix_oop);
    rd_adc[2] = sim_spi_read_one_byte(pMix_oop);
    adc_value  = (sdt_int32u)rd_adc[0] << 16;
    adc_value |= (sdt_int32u)rd_adc[1] << 8;
    adc_value |= (sdt_int32u)rd_adc[2];
    return(adc_value);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//状态机
typedef enum
{
    mupts_idle       = 0x00,
    mupts_ref_select,    //测量基准电阻
    mupts_mesRef_str,
    mupts_mesRef_waiteCov,

}mutil_pt100_state_def;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
    
    mutil_pt100_state_def  mutil_pt100_state;
    sdt_int32u ref_adc_value;
    timerClock_def timer_wayChg;
    sim_spi_oop_def mmp_spi;
    sdt_bool(*mpp_pull_DRDY)(void);
    void(*mpp_select_way)(sdt_int8u in_new_way);
}mutil_pt100_oop_def;

//--------------------------------------------------------------------------------------------------------------------------
//多通道PT100任务
static void mutil_pt100_oop_task(mutil_pt100_oop_def* pMix_oop)
{
    pbc_timerMillRun_task(&pMix_oop->timer_wayChg);
    switch(pMix_oop->mutil_pt100_state)
    {
        case mupts_idle:
        {
            break;
        }
        case mupts_ref_select:
        {
            pMix_oop->mpp_select_way(7);   //选择通道7
            sdt_int8u reg_0 = 0x20;
            ads1220_write_register(&pMix_oop->mmp_spi,0,1,&reg_0);   //AIN0  AIN3
            pbc_reload_timerClock(&pMix_oop->timer_wayChg,10);
            pMix_oop->mutil_pt100_state = mupts_mesRef_str;
            break;
        }
        case mupts_mesRef_str:
        {
            if(pbc_pull_timerIsCompleted(&pMix_oop->timer_wayChg))
            {
                sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08); //strat conversation
                pMix_oop->mutil_pt100_state = mupts_mesRef_waiteCov;
            }
            break;
        }
        case mupts_mesRef_waiteCov:
        {
            if(sdt_false == pMix_oop->mpp_pull_DRDY())  //低电平有效
            {
                
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void ads1220_read_reg(mutil_pt100_oop_def* pMix_oop,sdt_int8u* pOut_bytes,sdt_int8u in_length)
{
     sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x43);
     sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x20);
     sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x80);
     sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x26);
     sim_spi_write_one_byte(&pMix_oop->mmp_spi,0xc0);
    static sdt_int8u test_bytes[4] = {0xff,0xff,0xff,0xff};
    sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x23);
    test_bytes[0] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    test_bytes[1] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    test_bytes[2] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    test_bytes[3] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);

    static sdt_int8u adc_value[3];
    static sdt_int32u adc_32 = 0;
    sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08);
    while(sdt_true == pMix_oop->mpp_pull_DRDY())
    {
    }
    adc_value[0] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    adc_value[1] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    adc_value[2] = sim_spi_read_one_byte(&pMix_oop->mmp_spi);
    adc_32 = (sdt_int32u)adc_value[0] << 16;
    adc_32 |= (sdt_int32u)adc_value[1] << 8;
    adc_32 |= (sdt_int32u)adc_value[2];
    pOut_bytes[0] = test_bytes[0];   
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//配置ADS1220
static void ads1220_cfg(mutil_pt100_oop_def* pMix_oop)
{
    static sdt_int8u out_byts[4];
    ads1220_read_reg(pMix_oop,&out_byts[0],2);
}
//+++++++++++++++++++++++++++++++solid++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define max_solid    1
//--------------------------------------------------------------------------------------------------------------------------
static mutil_pt100_oop_def mutil_pt100_solid[max_solid];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void mutil_pt100_solid_cfg(void)
{
    bsp_mutilpt100_cfg();
//--------------------------------------------------------------------------------------------------------------------------
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_CS = bsp_push_ads1220_CS;
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_SCLK = bsp_push_ads1220_SCLK;
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_MOSI = bsp_push_ads1220_MOSI;
    mutil_pt100_solid[0].mmp_spi.mpp_pull_spi_MISO = bsp_pull_ads1220_MISO;
    mutil_pt100_solid[0].mpp_pull_DRDY = bsp_pull_ads1220_DRDY;
    mutil_pt100_solid[0].mpp_select_way = bsp_push_select_4051;
    bsp_push_select_4051(7);
    ads1220_cfg(&mutil_pt100_solid[0]);
//---------------------------------------------------------------------------------------------------------------------------
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:mRtu任务
//--------------------------------------------------------------------------------------------------------------------------
void mde_mutil_pt100_task(void)
{
    static sdt_bool cfged = sdt_false;

    if(cfged)
    {
        sdt_int8u i;
        for(i = 0;i < max_solid;i ++)
        {
            mutil_pt100_oop_task(&mutil_pt100_solid[i]);
        }
    }
    else
    {
        cfged = sdt_true;
        mutil_pt100_solid_cfg();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++