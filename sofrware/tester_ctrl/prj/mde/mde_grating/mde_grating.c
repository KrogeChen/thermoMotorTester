//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
#include ".\depend\bsp_grating.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
    sdt_int32s  site_pulse;
    sdt_int32s  diff_pulse;
    sdt_int8u   now_pulse_AB;
    sdt_bool    now_pulse_Z;
    sdt_bool    zero_finish;
    sdt_bool (*pull_pulse_status)(sdt_int8u* pulse_ABZ);
}grating_oper_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void grating_task(grating_oper_def* mix_oper)
{
    sdt_int8u rd_pulse_ABZ;
    sdt_int8u rd_pulse_AB;
    sdt_bool rd_pulse_Z;
    sdt_bool dir_add = sdt_false;

    while(1)
    {
        sdt_bool new_pulse;
        new_pulse = mix_oper->pull_pulse_status(&rd_pulse_ABZ);
        if(new_pulse)
        {
            rd_pulse_AB = (rd_pulse_ABZ & 0x06) >> 1;
            if(rd_pulse_ABZ & 0x01)
            {
                rd_pulse_Z = sdt_true;
            }
            else
            {
                rd_pulse_Z = sdt_false;
            }
            switch(mix_oper->now_pulse_AB)
            {
                case 0:
                {
                    if(rd_pulse_AB == 0x02)
                    {
                        dir_add = sdt_true;
                        mix_oper->site_pulse ++;
                        mix_oper->diff_pulse ++;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    else if(rd_pulse_AB == 0x01)
                    {
                        dir_add = sdt_false;
                        mix_oper->site_pulse --;
                        mix_oper->diff_pulse --;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    break;
                }
                case 1:
                {
                    if(rd_pulse_AB == 0x00)
                    {
                        dir_add = sdt_true;
                        mix_oper->site_pulse ++;
                        mix_oper->diff_pulse ++;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    else if(rd_pulse_AB == 0x03)
                    {
                        dir_add = sdt_false;
                        mix_oper->site_pulse --;
                        mix_oper->diff_pulse --;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    break;
                }
                case 2:
                {
                    if(rd_pulse_AB == 0x03)
                    {
                        dir_add = sdt_true;
                        mix_oper->site_pulse ++;
                        mix_oper->diff_pulse ++;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    else if(rd_pulse_AB == 0x00)
                    {
                        dir_add = sdt_false;
                        mix_oper->site_pulse --;
                        mix_oper->diff_pulse --;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    break;
                }
                case 3:
                {
                    if(rd_pulse_AB == 0x01)
                    {
                        dir_add = sdt_true;
                        mix_oper->site_pulse ++;
                        mix_oper->diff_pulse ++;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    else if(rd_pulse_AB == 0x02)
                    {
                        dir_add = sdt_false;
                        mix_oper->site_pulse --;
                        mix_oper->diff_pulse --;
                        mix_oper->now_pulse_AB = rd_pulse_AB;
                    }
                    break;
                }
                default:
                {
                    mix_oper->now_pulse_AB = 0;
                    break;
                }
            }
            if(mix_oper->now_pulse_Z)
            {
                if(rd_pulse_Z)
                {
                }
                else
                {
                    if(dir_add)
                    {
                    }
                    else
                    {
                        mix_oper->site_pulse = 0;
                        mix_oper->zero_finish = sdt_true;
                    }
                }
                mix_oper->now_pulse_Z = rd_pulse_Z;
            }
            else
            {
                if(rd_pulse_Z)
                {
                    if(dir_add)
                    {
                        mix_oper->site_pulse = 0;
                        mix_oper->zero_finish = sdt_true;
                    }
                    else
                    { 
                    }
                }
                else
                {
                }
                mix_oper->now_pulse_Z = rd_pulse_Z;
            }
        }
        else
        {
            break;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define max_solid    1
//-----------------------------------------------------------------------------
static grating_oper_def grating_oper_solid[max_solid];
//-----------------------------------------------------------------------------
static void grating_solid_cfg(void)
{
    bsp_gratingMeasure_cfg();
    grating_oper_solid[0].pull_pulse_status = bsp_pull_pulse_status;
    grating_oper_solid[0].zero_finish = sdt_false;
}
//++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++++
//name:光栅测量任务
//-----------------------------------------------------------------------------
void mde_gratingMeasure_task(void)
{
    static sdt_bool cfged = sdt_false;

    if(cfged)
    {
        sdt_int8u i;
        for(i = 0;i < max_solid;i ++)
        {
            grating_task(&grating_oper_solid[i]);
        }
    }
    else
    {
        cfged = sdt_true;
        grating_solid_cfg();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_pull_differentPulse(sdt_int8u in_solidNum,sdt_int32s* out_diff_pulse)
{
    if(in_solidNum < max_solid)
    {
        *out_diff_pulse = grating_oper_solid[in_solidNum].diff_pulse;
        grating_oper_solid[in_solidNum].diff_pulse = 0;
    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool mde_pull_sitePulse(sdt_int8u in_solidNum,sdt_int32s* out_site_pulse)
{
    if(in_solidNum < max_solid)
    {
        *out_site_pulse = grating_oper_solid[in_solidNum].site_pulse;
        return(grating_oper_solid[in_solidNum].zero_finish);
    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++