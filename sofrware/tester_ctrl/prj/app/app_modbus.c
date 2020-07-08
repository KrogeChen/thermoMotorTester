//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
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
                    case regAddr_m_statesW:
                    {
                        reg_detailes = 0;
                        if(app_pull_sme_state())
                        {
                            reg_detailes |= bits_mSW_measureIsRun;
                        }
                        break;
                    }
                    case regAddr_m_ctrlW:
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
                        case regAddr_m_statesW:
                        {
                            break;
                        }
                        case regAddr_m_ctrlW:
                        {
                            if(rd_wReg_details & bits_mCW_start)
                            {
                                app_entry_strat_measure();
                            }
                            if(rd_wReg_details & bits_mCW_stop)
                            {
                                app_entry_stop_measure();
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