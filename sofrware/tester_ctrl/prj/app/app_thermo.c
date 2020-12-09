//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    wmotor_ctrl_none    = 0,
    wmotor_ctrl_up,
    wmotor_ctrl_down,
    wmotor_ctrl_stop,
}wmotor_ctrl_def;
//-----------------------------------------------------------------------------
typedef enum
{
    wmotor_ste_idle  = 0,
    wmotor_ste_cmd,
    wmotor_ste_uping,
    wmotor_ste_downing,
    wmotor_ste_braking,
}wmotor_states_def;
//-----------------------------------------------------------------------------
typedef struct
{
    wmotor_ctrl_def    wmotor_ctrl;
    wmotor_states_def  wmotor_states;
    sdt_int16u         slide_how_many;
    timerClock_def     timer_slide;
    timerClock_def     timer_brake;
}wmotor_para_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static wmotor_para_def wmotor_para;
//-----------------------------------------------------------------------------
#define motor_cw_out    7
#define motor_ccw_out   8
//-----------------------------------------------------------------------------
//加载重物
//-----------------------------------------------------------------------------
static void weight_moto_load(void)
{
     mde_ouput_port(motor_cw_out,sdt_true);
     mde_ouput_port(motor_ccw_out,sdt_false);
}
//-----------------------------------------------------------------------------
//解除重物
static void weight_moto_unload(void)
{
     mde_ouput_port(motor_ccw_out,sdt_true);
     mde_ouput_port(motor_cw_out,sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//停止负载搬运马达
static void stop_weight_moto(void)
{
     mde_ouput_port(motor_ccw_out,sdt_false);
     mde_ouput_port(motor_cw_out,sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void weight_motor_update(wmotor_ctrl_def in_ctrl_cmd,sdt_int16u in_time)
{
    wmotor_para.wmotor_ctrl = in_ctrl_cmd;
    wmotor_para.slide_how_many = in_time;
    wmotor_para.wmotor_states = wmotor_ste_cmd;
}
//-----------------------------------------------------------------------------
static sdt_bool pull_weight_motorIsIdle(void)
{
    if(wmotor_ste_idle == wmotor_para.wmotor_states)
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//-----------------------------------------------------------------------------
//马达动作任务
//-----------------------------------------------------------------------------
static void app_weight_motor_do_task(void)
{
    static sdt_bool cfged = sdt_false;
    
    if(cfged)
    {
        pbc_timerClockRun_task(&wmotor_para.timer_slide);
        pbc_timerClockRun_task(&wmotor_para.timer_brake);
        
        switch(wmotor_para.wmotor_states)
        {
            case wmotor_ste_idle:
            {
                break;
            }
            case wmotor_ste_cmd:
            {
                if(pbc_pull_timerIsCompleted(&wmotor_para.timer_brake))
                {
                    if(wmotor_ctrl_up == wmotor_para.wmotor_ctrl)
                    {
                        weight_moto_unload();
                        pbc_reload_timerClock(&wmotor_para.timer_slide,wmotor_para.slide_how_many);
                        wmotor_para.wmotor_states = wmotor_ste_uping;
                    }
                    else if(wmotor_ctrl_down == wmotor_para.wmotor_ctrl)
                    {
                        weight_moto_load();
                        pbc_reload_timerClock(&wmotor_para.timer_slide,wmotor_para.slide_how_many);
                        wmotor_para.wmotor_states = wmotor_ste_uping;
                    }
                    else if(wmotor_ctrl_stop == wmotor_para.wmotor_ctrl)
                    {
                        stop_weight_moto();
                        pbc_reload_timerClock(&wmotor_para.timer_brake,800);
                        wmotor_para.wmotor_states = wmotor_ste_braking;
                    }
                    else
                    {
                        wmotor_para.wmotor_states = wmotor_ste_idle;
                    }
                    wmotor_para.wmotor_ctrl = wmotor_ctrl_none;
                }
                break;
            }
            case wmotor_ste_uping:
            case wmotor_ste_downing:
            {
                if(pbc_pull_timerIsCompleted(&wmotor_para.timer_slide))
                {
                    stop_weight_moto();
                    pbc_reload_timerClock(&wmotor_para.timer_brake,800);
                    wmotor_para.wmotor_states = wmotor_ste_braking;
                }
                break;
            }
            case wmotor_ste_braking:
            {
                if(pbc_pull_timerIsCompleted(&wmotor_para.timer_brake))
                {
                    wmotor_para.wmotor_states = wmotor_ste_idle;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else
    {
        cfged = sdt_true;
        wmotor_para.timer_slide.timStatusBits = timerType_second;
        wmotor_para.timer_brake.timStatusBits = timerType_millisecond;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
//-----------------------------------------------------------------------------
typedef enum
{
    Y7013   = 0x00,
    Y7010,
    Y7015,
}product_type_def;
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static voltage_level_def local_voltage_level;
static product_type_def local_product;
static sdt_bool vp_selected = sdt_false;
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
#define key_start          0


#define key_stop           1
//-----------------------------------------------------------------------------
#define bms_emergency      1//紧急状态值
//-----------------------------------------------------------------------------
static sdt_bool emergercy = sdt_false;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void app_key_borad_task(void)
{
    if(Pull_KeyboardEvent_Task())
    {
        if(KeyPushDown & Pull_KeyVauleStatus(key_start,3000,250))
        {
            if(app_pull_vp_selected())
            {
                app_entry_strat_measure();
                app_push_local_gui_menu(mgm_measure);                
            }
        }
        else if(KeyPushDown & Pull_KeyVauleStatus(key_stop,3000,250))
        {
            app_entry_stopAndUnload();
        }
    }
//-----------------------------------------------------------------------------
    
    static sdt_int8u cnt = 0;
    
    sdt_bool rd_emy;
    rd_emy = mde_pull_input_port(bms_emergency);
    
    /*if(rd_emy != emergercy)
    {
        cnt ++;
        if(cnt > 8)
        {
            cnt = 0;
            emergercy = rd_emy;
        }
    }*/
    if(emergercy)
    {
        
    }
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
    tester_sme_abortAndUnload,
    tester_sme_unload,
    tester_sme_unloading,
    tester_sme_complete,
}tester_stateMachine_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LOAD_MOTO_RUNT   10  //20s负载搬运电机运行时间
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static tester_stateMachine_def tester_stateMachine;
static sdt_int32s measure_now;
static sdt_int32s measure_max;
static sdt_int16u time_second;
static sdt_int16u second_for_3500um;
static sdt_int16s temperature_now;
static sdt_int16s temperature_max;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_thermoMotor_ts(void)
{
    macro_createTimer(timer_loadWh,timerType_second,0);
    macro_createTimer(timer_measue_period,timerType_millisecond,0);
    macro_createTimer(timer_timeout,timerType_second,0);
    
    pbc_timerClockRun_task(&timer_loadWh);
    pbc_timerClockRun_task(&timer_measue_period);
    pbc_timerClockRun_task(&timer_timeout);
//-----------------------------------------------------------------------------
    if(emergercy)
    {
        stop_weight_moto();  //停电机
        thermoMotor_heat_disable();
        tester_stateMachine = tester_sme_idle;
        wmotor_para.wmotor_states = wmotor_ste_idle;
    }
//-----------------------------------------------------------------------------
    app_key_borad_task();
    app_weight_motor_do_task();
    select_voltage(local_voltage_level);
    
    switch(tester_stateMachine)
    {
        static sdt_int8u locked_max;
        
        case tester_sme_idle:
        {
            app_push_local_gui_sm(mgs_ms_idle);
            break;
        }
        case tester_sme_loadWeigth:
        {
            measure_now = 0;
            measure_max = 0;
            temperature_now = app_pull_pt100_temperature(0);
            temperature_max = temperature_now;
            time_second = 0;
            app_push_local_gui_sm(mgs_ms_loading);
            weight_motor_update(wmotor_ctrl_down,LOAD_MOTO_RUNT);
            tester_stateMachine = tester_sme_waitLoaded;
            break;
        }
        case tester_sme_waitLoaded:
        {
            if(pull_weight_motorIsIdle())
            {
                tester_stateMachine = tester_sme_strHeat;
            }
            break;
        }
        case tester_sme_strHeat:
        {
            thermoMotor_heat_enable();
            measure_now = 0;
            measure_max = 0;
            temperature_now = app_pull_pt100_temperature(0);
            temperature_max = temperature_now;    
            time_second = 0;
            locked_max = 0;
            second_for_3500um = 0;
            pbc_reload_timerClock(&timer_measue_period,1000);
            
            
            sdt_int16u timeout_heating;
            if(StoRunParamter.timeout_heating  < 180)
            {
                StoRunParamter.timeout_heating = 300;
            }
            else if(StoRunParamter.timeout_heating  > 1200)
            {
                StoRunParamter.timeout_heating  = 300;
            }            
            timeout_heating = StoRunParamter.timeout_heating;

            pbc_reload_timerClock(&timer_timeout,timeout_heating);
            app_pull_increment_um();  //measure clean
            tester_stateMachine = tester_sme_measure;
            app_push_local_gui_sm(mgs_ms_measuring);
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
                    if(measure_max <= measure_now)
                    {
                        measure_max = measure_now;
                        locked_max = 0;
                    }
                    else
                    {
                        locked_max ++;
                    }                    
                }
                if(0 == second_for_3500um)
                {
                    if(measure_now >= 3500)
                    {
                        second_for_3500um = time_second;
                    }
                }
                temperature_now = app_pull_pt100_temperature(0);
                if(temperature_max <= temperature_now)
                {
                    temperature_max = temperature_now;
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

            thermoMotor_heat_disable();
            tester_stateMachine = tester_sme_complete;
            break;
        }
        case tester_sme_abortAndUnload:
        {
            thermoMotor_heat_disable();
            tester_stateMachine = tester_sme_unload;
            break;
        }
        case tester_sme_unload:
        {
            app_push_local_gui_sm(mgs_ms_unloading);
            weight_motor_update(wmotor_ctrl_up,LOAD_MOTO_RUNT);
            tester_stateMachine = tester_sme_unloading;
            break;
        }
        case tester_sme_unloading:
        {
            if(pull_weight_motorIsIdle())
            {
                app_push_local_gui_sm(mgs_ms_complete);
                tester_stateMachine = tester_sme_idle;
            }
            break;
        }
        case tester_sme_complete:
        {
            app_push_local_gui_sm(mgs_ms_complete);
            if(pbc_pull_timerIsCompleted(&timer_measue_period))
            {
                pbc_reload_timerClock(&timer_measue_period,1000);
                time_second ++;
                measure_now += app_pull_increment_um();
                
                temperature_now = app_pull_pt100_temperature(0);
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int32s app_pull_stroke_max(void)
{
    return(measure_max);
}
//-----------------------------------------------------------------------------
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
sdt_int16s app_pull_ptcTemperature_now(void)
{
    return(temperature_now);
}
//-----------------------------------------------------------------------------
sdt_int16s app_pull_ptcTemperature_max(void)
{
    return(temperature_max);
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
    if(tester_sme_measure != tester_stateMachine)
    {
        tester_stateMachine = tester_sme_loadWeigth;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_entry_stop_measure(void)
{
    tester_stateMachine = tester_sme_abort;
}
void app_entry_stopAndUnload(void)
{
    if(tester_sme_unloading != tester_stateMachine)
    {
        tester_stateMachine = tester_sme_abortAndUnload;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_voltage_select(sdt_int16u in_voltage)
{
    if(in_voltage != local_voltage_level)
    {
        local_voltage_level = (voltage_level_def)in_voltage;
        StoRunParamter.select_voltage = in_voltage;
        app_push_once_save_sto_parameter();      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int16u app_pull_voltage_select(void)
{
    return((sdt_int16u)local_voltage_level);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_product_select(sdt_int16u in_type)
{
    if(in_type != local_product)
    {
        local_product = (product_type_def)in_type;
        StoRunParamter.select_product = in_type;
        app_push_once_save_sto_parameter();        
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int16u app_pull_porduct_select(void)
{
    return((sdt_int16u)local_product);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool app_pull_vp_selected(void)
{
    return(vp_selected);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_vp_select(sdt_bool in_select)
{
    vp_selected = in_select;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool app_pull_emergercy(void)
{
    return(emergercy);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_auto_unload(void)
{
    tester_stateMachine = tester_sme_unload;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int16u app_pull_second_3_5T(void)
{
    return(second_for_3500um);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++