//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\depend\bsp_digitInput.h"
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_int16u now_input_status;
#define max_input   7
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_input_port_task(void)
{
    static sdt_bool cfged = sdt_false;
    macro_createTimer(timer_period,timerType_millisecond,2);
    static sdt_int8u changed_cnt[max_input];

    pbc_timerClockRun_task(&timer_period);
    if(cfged)
    {
        if(pbc_pull_timerIsCompleted(&timer_period))
        {
            pbc_reload_timerClock(&timer_period,2);

            sdt_int16u rd_io = 0;
            if(bsp_pull_input_X0())
            {
                rd_io |= 0x0001;
            }
            if(bsp_pull_input_X1())
            {
                rd_io |= 0x0002;
            }
            if(bsp_pull_input_X2())
            {
                rd_io |= 0x0004;
            }
            if(bsp_pull_input_X3())
            {
                rd_io |= 0x0008;
            }
            if(bsp_pull_input_X4())
            {
                rd_io |= 0x0010;
            }
            if(bsp_pull_input_X5())
            {
                rd_io |= 0x0020;
            }
            if(bsp_pull_input_X6())
            {
                rd_io |= 0x0040;
            }
            sdt_int16u mask_bit = 0x0001;
            sdt_int16u rd_bit = 0;
            sdt_int16u now_bit = 0;
            sdt_int8u i;
            for(i = 0;i < max_input;i++)
            {
                mask_bit = 0x0001<<i;
                rd_bit = rd_io & mask_bit;
                now_bit = now_input_status & mask_bit;

                if(rd_bit ^ now_bit)
                {
                    changed_cnt[i]++;
                    if(changed_cnt[i] > 3)
                    {
                        changed_cnt[i] = 0;
                        now_input_status &= ~mask_bit;
                        now_input_status |= rd_bit;
                    }
                }                
            }
        }
    }
    else
    {
        cfged = sdt_true;
        bsp_input_port_cfg();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//7个输入IO
//-----------------------------------------------------------------------------
sdt_bool mde_pull_input_port(sdt_int8u in_port_num)
{

    sdt_bool rd_input = sdt_false;
    if(now_input_status & (0x0001<<in_port_num))
    {
        rd_input = sdt_true;
    }
    return(rd_input);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++