//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_ledBlink.h"
#include ".\depend\bsp_ledBlink.h"
#include "..\pbc\pbc_sysTick\pbc_sysTick.h"
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct 
{
    sdt_int16u period_time;
    sdt_int16u light_time;
    timerClock_def timer_period;
    timerClock_def timer_light;
    void(*led_to_light)(void);
    void(*led_to_dark)(void);
}blink_oper_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void ledBlink_operation_task(blink_oper_def* lb_oper)
{
    pbc_timerMillRun_task(&lb_oper->timer_period);
    pbc_timerMillRun_task(&lb_oper->timer_light);
    if(pbc_pull_timerIsCompleted(&lb_oper->timer_period))
    {
        pbc_reload_timerClock(&lb_oper->timer_period,lb_oper->period_time);
        if(0 == lb_oper->light_time)
        {
            lb_oper->led_to_dark();
        }
        else
        {
            pbc_reload_timerClock(&lb_oper->timer_light,lb_oper->light_time);
            lb_oper->led_to_light();
        }
    }
    if(pbc_pull_timerIsCompleted(&lb_oper->timer_light))
    {
        lb_oper->led_to_dark();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static blink_oper_def  blink_oper_one;
//-----------------------------------------------------------------------------
static void sloid_cfg(void)
{
    bsp_lcd_runStatus_cfg();
    blink_oper_one.period_time = 1000;
    blink_oper_one.light_time = 500;
    blink_oper_one.led_to_dark = bsp_led_dark;
    blink_oper_one.led_to_light = bsp_led_light;
//-----------------------------------------------------------------------------
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++interface+++++++++++++++++++++++++++++++++++++++
void mde_ledBlink_task(void)
{
    static sdt_bool cfged = sdt_false;
    if(cfged)
    {
        ledBlink_operation_task(&blink_oper_one);
    }
    else
    {
        cfged = sdt_true;
        sloid_cfg();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_ledBlink_change_time(sdt_int8u in_num,sdt_int16u in_period_time,sdt_int16u in_light_time)
{
    if(0 == in_num)
    {
        blink_oper_one.period_time = in_period_time;
        blink_oper_one.light_time = in_light_time;
        pbc_reload_timerClock(&blink_oper_one.timer_period,0);
    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++