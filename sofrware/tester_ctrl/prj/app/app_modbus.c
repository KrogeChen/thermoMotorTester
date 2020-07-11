//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
modbus_gui_def local_gui;
sdt_bool gui_need_update;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 通用应用task
//-----------------------------------------------------------------------------
sdt_int16u test_reg[256];
sdt_int8u test_reg_idx;
void app_modbus_task(void)
{
  
    static sdt_bool cfged = sdt_false;
    
    if(cfged)
    {
        mde_mRtu_task();
        
        sdt_int16u reg_addr,reg_length;
        mRtu_status_def rd_stauts = mRtuS_none;
        sdt_int16u reg_detailes;
        sdt_int32s rd_um;
        
        rd_stauts = pull_mRtu_register(0,&reg_addr,&reg_length);
        if(mRtuS_read == rd_stauts)
        {
            while(reg_length)
            {
                switch(reg_addr)
                {
                    case regAddr_m_version:
                    { 
                        reg_detailes = 0x0001;
                        break;
                    }
                    case regAddr_m_gui_menu:
                    {
                        reg_detailes = local_gui.m_gui_menu;
                        gui_need_update = sdt_false;
                        break;
                    }
                    case regAddr_m_gui_sm:
                    {
                        reg_detailes = local_gui.m_gui_sm;
                        break;
                    }
                    case regAddr_m_gui_bits:
                    {
                        reg_detailes = local_gui.m_gui_bits;
                        break;
                    }
                    case regAddr_m_states_bits:
                    {
                        reg_detailes = 0;
                        sdt_int32s rd_temp;
                        if(app_pull_site_um(&rd_temp))
                        {
                            reg_detailes |= bits_mSBits_gzero;
                        }
                        if(app_pull_vp_selected())
                        {
                            reg_detailes |= bits_mSBits_selected;
                        }
                        if(app_pull_emergercy())
                        {
                            reg_detailes |= bits_mSBits_emergercy;
                        }
                        break;
                    }
                    case regAddr_m_event_bits:
                    {
                        reg_detailes = 0x0000;
                        break;
                    }
                    case regAddr_m_msrSecond:
                    {
                        reg_detailes = app_pull_stroke_time();
                        break;
                    }
                    case regAddr_m_msrGt_um_0:
                    {
                        rd_um = app_pull_stroke_measure();
                        reg_detailes = rd_um >> 16;
                        break;
                    }
                    case regAddr_m_msrGt_um_1:
                    {
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_msrGt_max_0:
                    {
                        rd_um = app_pull_stroke_max();
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_msrGt_max_1:
                    {
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_grating_pds_0:
                    {
                        app_pull_site_um(&rd_um);
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_grating_pds_1:
                    {
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_logic_zero_0:
                    {
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_logic_zero_1:
                    {
                        reg_detailes = rd_um;
                        break;
                    }
                    case regAddr_m_select_voltage:
                    {
                        reg_detailes = app_pull_voltage_select();
                        break;
                    }
                    case regAddr_m_select_product:
                    {
                        reg_detailes = app_pull_porduct_select();
                        break;
                    }
                    default:
                    {
                        reg_detailes = 0;
                        break;
                    }
                }
                if(push_mRtu_readReg(0,reg_addr,reg_detailes))
                {
                    reg_addr ++;
                    reg_length --;
                }
                else
                {
                    break;
                }
            }
            mRtu_answer_event(0);
        }
        else if(mRtuS_write == rd_stauts)
        {
            while(reg_length)
            {
                sdt_int16u rd_wReg_details;
                if(pull_mRtu_writeReg(0,reg_addr,&rd_wReg_details))
                {
                    switch(reg_addr)
                    {
                        case regAddr_m_version:
                        { 
                            break;
                        }
                        case regAddr_m_gui_menu:
                        {
                            if(gui_need_update)
                            {
                            }
                            else
                            {
                                if(app_pull_vp_selected())
                                {
                                    local_gui.m_gui_menu = (modbus_gui_menu_def)reg_detailes;
                                }                              
                            }
                            break;
                        }
                        case regAddr_m_gui_sm:
                        {
                            //local_gui.m_gui_sm = reg_detailes;
                            break;
                        }
                        case regAddr_m_gui_bits:
                        {
                            //reg_detailes = local_gui.m_gui_bits;
                            break;
                        }
                        case regAddr_m_states_bits:
                        {
                            break;
                        }
                        case regAddr_m_event_bits:
                        {
                            if(rd_wReg_details & bits_mEBits_start)
                            {
                                app_entry_strat_measure();
                            }
                            if(rd_wReg_details & bits_mEBits_stop)
                            {
                                app_entry_stop_measure();
                            }
                            if(rd_wReg_details & bits_mEBits_load)
                            {
                            }
                            if(rd_wReg_details & bits_mEBits_unload)
                            {
                            }
                            if(rd_wReg_details & bits_mEBits_selectCMT)
                            {
                                app_push_vp_select(sdt_true);
                            }
                            break;
                        }
                        case regAddr_m_msrSecond:
                        {
                            break;
                        }
                        case regAddr_m_msrGt_um_0:
                        {
                            break;
                        }
                        case regAddr_m_msrGt_um_1:
                        {
                            break;
                        }
                        case regAddr_m_msrGt_max_0:
                        {
                            break;
                        }
                        case regAddr_m_msrGt_max_1:
                        {
                            break;
                        }
                        case regAddr_m_grating_pds_0:
                        {
                            break;
                        }
                        case regAddr_m_grating_pds_1:
                        {
                            break;
                        }
                        case regAddr_m_logic_zero_0:
                        {
                            break;
                        }
                        case regAddr_m_logic_zero_1:
                        {
                            break;
                        }
                        case regAddr_m_select_voltage:
                        {
                            app_push_voltage_select(rd_wReg_details);
                            break;
                        }
                        case regAddr_m_select_product:
                        {
                            app_push_product_select(rd_wReg_details);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    test_reg[test_reg_idx] = rd_wReg_details;
                    test_reg_idx ++;


                    reg_addr ++;
                    reg_length --;
                }
                else
                {
                    break;
                }
            }
            mRtu_answer_event(0);
        }
        else if(mRtuS_rwBoth == rd_stauts)
        {
            sdt_int16u w_reg_addr,w_reg_length;
            pull_mRtu_register_wb(0,&w_reg_addr,&w_reg_length);

            while(w_reg_length)
            {
                sdt_int16u rd_wReg_details;
                if(pull_mRtu_writeReg(0,w_reg_addr,&rd_wReg_details))
                {
                    test_reg[test_reg_idx] = rd_wReg_details;
                    test_reg_idx ++;
                    w_reg_addr ++;
                    w_reg_length --;
                }
                else
                {
                    break;
                }
            }
            test_reg_idx = 0;
            while(reg_length)
            {
                if(push_mRtu_readReg(0,reg_addr,test_reg[test_reg_idx]))
                {
                    test_reg_idx ++;
                    reg_addr ++;
                    reg_length --;
                }
                else
                {
                    break;
                } 
            }
            mRtu_answer_event(0);
        }      
    }
    else
    {
        cfged = sdt_true;
        mRtu_parameter_def parameter;
        parameter.mRtu_address = 0x01;
        parameter.mRtu_baudrate = 9600;
        parameter.mRtu_parity = mRtu_parity_none;
        parameter.mRtu_stopBits = mRtu_stopBits_one;
        parameter.mRtu_sysFrequency = 72000000;
        set_mRtu_parameter(0,&parameter);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_local_gui_sm(modbus_gui_s_measure_def in_gui_sm)
{
    local_gui.m_gui_sm = in_gui_sm;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_local_gui_menu(modbus_gui_menu_def in_menu)
{
    gui_need_update = sdt_true;
    local_gui.m_gui_menu = in_menu;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++