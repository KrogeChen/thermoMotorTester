//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
StoRunParamter_Def  StoRunParamter;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_bool cfged = sdt_false;
//-------------------------------------------------------------------------------
static void sto_run_parameter_cfg(void)
{
    mde_storage_block_set_length_w(0,sizeof(StoRunParamter));
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_read_run_parameter(void)
{
    if(cfged)
    {     
    }
    else
    {
        cfged = sdt_true;
        sto_run_parameter_cfg();
    }
    //mde_write_storage_block(0,&StoRunParamter.sto_data[0]);
    if(mde_read_storage_block(0,&StoRunParamter.sto_data[0]))
    {
        app_push_voltage_select(StoRunParamter.select_voltage);
        app_push_product_select(StoRunParamter.select_product);
    }
    else
    {
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_createTimer(timer_notSave,(timerType_millisecond | timStatusBits_onceTriggered),0);
//-------------------------------------------------------------------------------
void app_sto_run_parameter_task(void)
{
    if(cfged)
    {     
    }
    else
    {
        cfged = sdt_true;
        sto_run_parameter_cfg();
    }
    
    pbc_timerClockRun_task(&timer_notSave);
    if(pbc_pull_timerIsOnceTriggered(&timer_notSave))
    {
        StoRunParamter_Def rd_sto;
        sdt_int32u i;
        sdt_bool enable_write = sdt_false;
        
        if(mde_read_storage_block(0,&rd_sto.sto_data[0]))
        {
            for(i = 0;i < (sizeof(StoRunParamter)/4);i ++)
            {
                if(rd_sto.sto_data[i] != StoRunParamter.sto_data[i])//数据有变化存储
                {
                    enable_write = sdt_true;
                    break;
                }
            }
        }
        else
        {
            enable_write = sdt_true;
        }
        if(enable_write)
        {
            mde_write_storage_block(0,&StoRunParamter.sto_data[0]);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_once_save_sto_parameter(void)
{
    pbc_reload_timerClock(&timer_notSave,3000);//3s后存储一次
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++