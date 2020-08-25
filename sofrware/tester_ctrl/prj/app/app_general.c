//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void test_output(void)
{

    macro_createTimer(timer_t,timerType_millisecond,0);
    
    
    pbc_timerClockRun_task(&timer_t);
    
    if(pbc_pull_timerIsCompleted(&timer_t))
    {
        pbc_reload_timerClock(&timer_t,1000);
        static sdt_bool out_s;
        
        if(out_s)
        {
            mde_ouput_port(6,sdt_true);
            out_s = sdt_false;
        }
        else
        {
            mde_ouput_port(6,sdt_false);
            out_s = sdt_true;
        }
    }
    
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 通用应用task
//-----------------------------------------------------------------------------
void app_general_task(void)
{
    static sdt_bool sys_cfged = sdt_false;

    if(sys_cfged)
    {
        mde_input_port_task();
        mde_ledBlink_task();
        app_grating_task();
        app_thermoMotor_ts();
        app_sto_run_parameter_task();
        app_electrimeter_task();
        app_pt100_task();
    }
    else
    {
        sys_cfged = sdt_true;
        mde_systemClock_cfg();
        app_read_run_parameter();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++