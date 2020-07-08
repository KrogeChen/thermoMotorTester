//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  relay_12v          0
#define  relay_24v          1
#define  relay_36v          2
#define  relay_110v         3
#define  relay_220v         4
#define  relay_outn         5
#define  relay_act          6
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    voll_12v     = 0x00,
    voll_24v,
    voll_36v,
    voll_110v,
    voll_220v,
}voltage_level_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void select_voltage(voltage_level_def in_voltage)
{
    switch(in_voltage)
    {
        case voll_12v:
        {
            mde_ouput_port(relay_12v,sdt_true);
            mde_ouput_port(relay_24v,sdt_false);
            mde_ouput_port(relay_36v,sdt_false);
            mde_ouput_port(relay_110v,sdt_false);
            mde_ouput_port(relay_220v,sdt_false);
            mde_ouput_port(relay_outn,sdt_true);
            break;
        }
        case voll_24v:
        {
            mde_ouput_port(relay_12v,sdt_false);
            mde_ouput_port(relay_24v,sdt_true);
            mde_ouput_port(relay_36v,sdt_false);
            mde_ouput_port(relay_110v,sdt_false);
            mde_ouput_port(relay_220v,sdt_false);
            mde_ouput_port(relay_outn,sdt_true);
            break;
        }
        case voll_36v:
        {
            mde_ouput_port(relay_12v,sdt_false);
            mde_ouput_port(relay_24v,sdt_false);
            mde_ouput_port(relay_36v,sdt_true);
            mde_ouput_port(relay_110v,sdt_false);
            mde_ouput_port(relay_220v,sdt_false);
            mde_ouput_port(relay_outn,sdt_true);
            break;
        }
        case voll_110v:
        {
            mde_ouput_port(relay_12v,sdt_false);
            mde_ouput_port(relay_24v,sdt_false);
            mde_ouput_port(relay_36v,sdt_false);
            mde_ouput_port(relay_110v,sdt_true);
            mde_ouput_port(relay_220v,sdt_false);
            mde_ouput_port(relay_outn,sdt_true);
            break;
        }
        case voll_220v:
        {
            mde_ouput_port(relay_12v,sdt_false);
            mde_ouput_port(relay_24v,sdt_false);
            mde_ouput_port(relay_36v,sdt_false);
            mde_ouput_port(relay_110v,sdt_false);
            mde_ouput_port(relay_220v,sdt_true);
            mde_ouput_port(relay_outn,sdt_true);
            break;
        }
        default:
        {
            break;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//加载重物
//-----------------------------------------------------------------------------
static void weight_moto_load(void)
{
}
//-----------------------------------------------------------------------------
//解除重物
static void weight_moto_unload(void)
{
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//停止负载搬运马达
static void stop_weight_moto(void)
{
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//加热使能
//-----------------------------------------------------------------------------
static void thermoMotor_heat_enable(void)
{
    mde_ouput_port(relay_act,sdt_true);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//加热解除
//-----------------------------------------------------------------------------
static void thermoMotor_heat_disable(void)
{
    mde_ouput_port(relay_act,sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    tester_sme_idle   = 0x00,
    tester_sme_loadWeigth,
    tester_sme_waitLoaded,
    tester_sme_strHeat,
    tester_sme_measure,
    tester_sme_abort,
    tester_sme_unload,
}tester_stateMachine_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LOAD_MOTO_RUNT   20  //20s负载搬运电机运行时间
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static tester_stateMachine_def tester_stateMachine;
static sdt_int32s measure_now;
static sdt_int32s measure_max;
static sdt_int16u time_second;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_thermoMotor_ts(void)
{
    macro_createTimer(timer_loadWh,timerType_second,0);
    macro_createTimer(timer_measue_period,timerType_millisecond,0);
    macro_createTimer(timer_timeout,timerType_second,0);

    pbc_timerClockRun_task(&timer_loadWh);
    pbc_timerClockRun_task(&timer_measue_period);
    pbc_timerClockRun_task(&timer_timeout);
    switch(tester_stateMachine)
    {
        static sdt_int8u locked_max;
        
        case tester_sme_idle:
        {
            break;
        }
        case tester_sme_loadWeigth:
        {   
          
            select_voltage(voll_220v);
            weight_moto_load();
            pbc_reload_timerClock(&timer_loadWh,LOAD_MOTO_RUNT);
            tester_stateMachine = tester_sme_waitLoaded;
            break;
        }
        case tester_sme_waitLoaded:
        {
            if(pbc_pull_timerIsCompleted(&timer_loadWh))
            {
                stop_weight_moto();
                tester_stateMachine = tester_sme_strHeat;
            }
            break;
        }
        case tester_sme_strHeat:
        {
            thermoMotor_heat_enable();
            measure_now = 0;
            measure_max = 0;
            time_second = 0;
            locked_max = 0;
            pbc_reload_timerClock(&timer_measue_period,1000);
            pbc_reload_timerClock(&timer_timeout,600);
            app_pull_increment_um();  //measure clean
            tester_stateMachine = tester_sme_measure;
            break;
        }
        case tester_sme_measure:
        {
            if(pbc_pull_timerIsCompleted(&timer_measue_period))
            {
                pbc_reload_timerClock(&timer_measue_period,1000);
                time_second ++;
                measure_now += app_pull_increment_um();
                if(locked_max < 30)
                {
                    if(measure_max < measure_now)
                    {
                        measure_max = measure_now;
                        locked_max = 0;
                    }
                    else
                    {
                        locked_max ++;
                    }                    
                }
            }
            if(pbc_pull_timerIsCompleted(&timer_timeout))
            {
                tester_stateMachine = tester_sme_abort;
            }
            break;
        }
        case tester_sme_abort:
        {
            weight_moto_unload();
            thermoMotor_heat_disable();
            pbc_reload_timerClock(&timer_loadWh,LOAD_MOTO_RUNT);
            tester_stateMachine = tester_sme_unload;
            break;
        }
        case tester_sme_unload:
        {
            if(pbc_pull_timerIsCompleted(&timer_loadWh))
            {
                stop_weight_moto();
                tester_stateMachine = tester_sme_idle;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//获取行程测量值
sdt_int32s app_pull_stroke_measure(void)
{
    return(measure_now);
}
//-----------------------------------------------------------------------------
//获取行程运行时间
sdt_int16u app_pull_stroke_time(void)
{
    return(time_second);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//获取测量状态
//-----------------------------------------------------------------------------
sdt_bool app_pull_sme_state(void)
{
    if(tester_sme_measure == tester_stateMachine)
    {
        return(sdt_true);
    }
    return(sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_entry_strat_measure(void)
{
    tester_stateMachine = tester_sme_loadWeigth;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_entry_stop_measure(void)
{
    tester_stateMachine = tester_sme_abort;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
