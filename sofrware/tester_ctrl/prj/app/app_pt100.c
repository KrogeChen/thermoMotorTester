//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_pt100_task(void)
{
    mde_mutil_pt100_task();
    macro_createTimer(timer_around,timerType_millisecond,0);

    pbc_timerClockRun_task(&timer_around);
    if(pbc_pull_timerIsCompleted(&timer_around))
    {
        pbc_reload_timerClock(&timer_around,1000);
        mde_push_start_conver(0);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int16s app_pull_pt100_temperature(sdt_int8u in_way)
{
    sdt_int16s rd_temperature = 0;
    if(0 == in_way)
    {
        rd_temperature = (sdt_int16s)mde_pull_temperature(0,1);
    }
    else if(1 == in_way)
    {
        rd_temperature = (sdt_int16s)mde_pull_temperature(0,0);
    }
    else if(2 == in_way)
    {
        rd_temperature = (sdt_int16s)mde_pull_temperature(0,3);
    }
    else if(3 == in_way)
    {
        rd_temperature = (sdt_int16s)mde_pull_temperature(0,2);
    }
    return(rd_temperature);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++