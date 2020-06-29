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

        rd_stauts = pull_mRtu_register(0,&reg_addr,&reg_length);
        if(mRtuS_read == rd_stauts)
        {
            while(reg_length)
            {
                 sdt_int32s rd_um;
                app_pull_site_um(&rd_um);
                if(push_mRtu_readReg(0,reg_addr,(sdt_int16s)rd_um))
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