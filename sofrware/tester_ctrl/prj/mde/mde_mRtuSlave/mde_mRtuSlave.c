//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_mRtuSlave.h"
#include "..\pbc\pbc_crc16\pbc_crc16.h"
#include "..\pbc\pbc_sysTick\pbc_sysTick.h"
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//modbus 从机模块,负责报文的接收和应答控制
//支持命令: 0x03 0x06 0x10 0x17
//支持多个实例
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    mRunS_idle           = 0x00,
    mRunS_receive_wait   = 0x01,
    mRunS_receive_first  = 0x02,
    mRunS_receive_data   = 0x03,
    mRunS_receive_end    = 0x04,
    mRunS_transmitStr    = 0x05,
    mRunS_transmitData   = 0x06,
    mRunS_transmitStop   = 0x07,
    mRunS_transmit_end   = 0x08,

}modbus_runStatus_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//modbus操作结构体
//-----------------------------------------------------------------------------
typedef struct
{
    modbus_runStatus_def  moo_runStutus;
    sdt_int8u  receive_buff[256];
    sdt_int8u  rev_index;
    sdt_int8u  transmit_buff[256];
    sdt_int16u transmit_regAddrStr;
    sdt_int8u  transmit_length;
    timerClock_def timer_revTimeOut;

    sdt_bool (*pull_receive_byte)(sdt_int8u* out_rByte);
    sdt_bool (*pull_busFree)(void);


}modbus_oper_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
modbus_oper_def modbus_oper_one;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:potocol command
//-----------------------------------------------------------------------------
sdt_bool modbus_receive_protocol(modbus_oper_def* mix_oper)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 
//-----------------------------------------------------------------------------
void modbus_operation_task(modbus_oper_def* mix_oper)
{
    pbc_timerMillRun_task(&mix_oper->timer_revTimeOut);
    switch(mix_oper->moo_runStutus)
    {
        case mRunS_idle:
        {
            mix_oper->moo_runStutus = mRunS_receive_wait;
            break;
        }
        case mRunS_receive_wait:
        {
            sdt_int8u receive_byte;
            if(mix_oper->pull_receive_byte(&receive_byte))
            {
                mix_oper->receive_buff[0] = receive_byte;
                mix_oper->rev_index = 1;
                mix_oper->moo_runStutus = mRunS_receive_data;
            }
            break;
        }
        case mRunS_receive_data:
        {
            while(1)
            {
                sdt_int8u receive_byte;
                if(mix_oper->pull_receive_byte(&receive_byte))
                {
                    mix_oper->receive_buff[mix_oper->rev_index] = receive_byte;
                    mix_oper->rev_index ++;
                }
                else
                {
                    if(mix_oper->pull_busFree())
                    {
                        if(modbus_receive_protocol(mix_oper))
                        {
                            pbc_reload_timerClock(&mix_oper->timer_revTimeOut,1500);
                            mix_oper->moo_runStutus = mRunS_receive_end;
                        }
                        else
                        {
                            mix_oper->moo_runStutus = mRunS_receive_wait;
                        }
                        
                    }
                    break;
                }
            }
            break;
        }
        case mRunS_receive_end:
        {
            if(pbc_pull_timerIsCompleted(&mix_oper->timer_revTimeOut))
            {
                mix_oper->moo_runStutus = mRunS_receive_wait;
            }
            break;
        }
        default:
        {
            mix_oper->moo_runStutus = mRunS_idle;
            break;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void modbus_solid_cfg(void)
{
    modbus_oper_one.timer_revTimeOut.timStatusBits = timerType_millisecond;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:写入一个寄存器的数据到缓存
//-----------------------------------------------------------------------------
sdt_bool make_readReg_buff(modbus_oper_def* mix_oper,sdt_int16u in_reg_addr,sdt_int16u in_regDetails)
{
    if(in_regDetails < (mix_oper->transmit_regAddrStr))
    {
        return(sdt_false);
    }
    else
    {
        sdt_int8u buff_index;
        if(0x03 == mix_oper->transmit_buff[1])
        {
            buff_index = 3;
        }
        else if (0x17 == mix_oper->transmit_buff[1])
        {
            buff_index = 3;
        }
        else
        {
            while(1);
        }
        
        sdt_int16u dis_r = in_regDetails - (mix_oper->transmit_regAddrStr);
        while(dis_r)
        {
            buff_index = buff_index + 2;
            dis_r = dis_r-1;
        }
        mix_oper->transmit_length += 2;
        mix_oper->transmit_buff[2] += 2;  //byte count
        mix_oper->transmit_buff[buff_index] = in_regDetails >> 8;
        mix_oper->transmit_buff[buff_index+1] = in_regDetails;
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void enable_answer_message(modbus_oper_def* mix_oper)
{
    if(mix_oper->transmit_length >253)
    {
        mix_oper->moo_runStutus = mRunS_idle; //overflow
    }
    else
    {
        Crc16CalculateOfByte(&mix_oper->transmit_buff[0],(sdt_int16u)mix_oper->transmit_length,&mix_oper->transmit_buff[mix_oper->transmit_length]);//crc
        mix_oper->transmit_length += 2;
        mix_oper->moo_runStutus = mRunS_transmitStr;       
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++interface+++++++++++++++++++++++++++++++++++
//name:mRtu任务
//-----------------------------------------------------------------------------
void mde_mRtu_task(void)
{
    sdt_bool cfged = sdt_false;

    if(cfged)
    {
        modbus_operation_task(&modbus_oper_one);
    }
    else
    {
        cfged = sdt_true;
        modbus_solid_cfg();
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
//in: in_reg_addr 寄存器地址，in_RegDetails 寄存器内容
//out: sdt_true 推入成功,sdt_false 推入失败
//-----------------------------------------------------------------------------
sdt_bool push_mRtu_readReg(sdt_int8u in_solidNum,sdt_int16u in_reg_addr,sdt_int16u in_RegDetails)
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
        enable_answer_message(&modbus_oper_one);
    }
    else
    {
        while(1);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++