//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_mRtuSlave.h"
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++interface+++++++++++++++++++++++++++++++++++
//name:设置modbus参数
//-----------------------------------------------------------------------------
void set_mRtu_parameter(sdt_int8u in_solidNum,mRtu_parameter_def in_parameter)
{
    if(0 == in_solidNum)
    {

    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取modbus register 当前状态
//in: *out_reg_addr 地址指针，*out_length 长度指针
//out: mRtuS_none 无,mRtuS_read 读数据,mRtuS_write 写数据
//-----------------------------------------------------------------------------
mRtu_status_def pull_mRtu_register(sdt_int8u in_solidNum,sdt_int16u* out_reg_addr,sdt_int16u* out_length)
{
    mRtu_status_def the_mRtu_status = mRtuS_none;

    if(0 == in_solidNum)
    {

    }
    else
    {
        while(1);
    }

    return(the_mRtu_status);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:modbus读取命令
//fun:把modbus需要读取的数据，推入modbus模块
//in: in_reg_addr 寄存器地址，in_length 长度，*in_pRegDetails 寄存器内容指针
//out: sdt_true 推入成功,sdt_false 推入失败
//-----------------------------------------------------------------------------
sdt_bool push_mRtu_readReg(sdt_int8u in_solidNum,sdt_int16u in_reg_addr,sdt_int16u in_length,sdt_int16u* in_pRegDetails)
{
    sdt_bool complete = sdt_false;

    if(0 == in_solidNum)
    {

    }
    else
    {
        while(1);
    }

    return(complete);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:modbus写入命令
//fun:从模块中获取需要写入的寄存器内容
//in: in_reg_addr 寄存器地址，in_length 长度，*out_pRregDetails 寄存器内容指针
//out: sdt_true 获取成功,sdt_false 获取失败
//-----------------------------------------------------------------------------
sdt_bool pull_mRtu_writeReg(sdt_int8u in_solidNum,sdt_int16u in_reg_addr,sdt_int16u in_length,sdt_int16u* out_pRregDetails)
{
    sdt_bool complete = sdt_false;

    if(0 == in_solidNum)
    {

    }
    else
    {
        while(1);
    }

    return(complete);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:应答事件
//fun:modbus总线开始应答
//-----------------------------------------------------------------------------
void mRtu_answer_event(sdt_int8u in_solidNum)
{
    if(0 == in_solidNum)
    {

    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++