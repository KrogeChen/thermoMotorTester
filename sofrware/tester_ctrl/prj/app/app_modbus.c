//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 通用应用task
//-----------------------------------------------------------------------------
void app_modbus_task(void)
{
    mde_mRtu_task();
    
    sdt_int16u reg_addr,reg_length;
    mRtu_status_def rd_stauts;

    rd_stauts = pull_mRtu_register(0,&reg_addr,&reg_length);
    if(mRtuS_read == rd_stauts)
    {
        while(reg_length)
        {
            if(push_mRtu_readReg(0,reg_addr,0x00))
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
                w_reg_addr ++;
                w_reg_length --;
            }
            else
            {
                break;
            }
        }
        while(reg_length)
        {
            if(push_mRtu_readReg(0,reg_addr,0x00))
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
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++