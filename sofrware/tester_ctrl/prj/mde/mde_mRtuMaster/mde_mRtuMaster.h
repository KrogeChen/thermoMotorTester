#ifndef med_mRtuMaster_H
#define med_mRtuMaster_H
//-----------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
typedef enum 
{
    mRtuS_master_none       = 0x00,
    mRtuS_master_complete   = 0x01,
    mRtuS_master_timeout    = 0x02,
    mRtuS_master_poterr     = 0x03,
}mRtu_master_status_def;
//-----------------------------------------------------------------------------
typedef enum
{
    mRtu_master_parity_none  = 0x00,
    mRtu_master_parity_even  = 0x01,
    mRtu_master_parity_odd   = 0x02,
}mRtu_master_parity_def;
//-----------------------------------------------------------------------------
typedef enum
{
    mRtu_master_stopBits_one = 0x00,
    mRtu_master_stopBits_two = 0x01,
}mRtu_master_stopBits_def;
//-----------------------------------------------------------------------------
typedef struct mde_mRtu_master
{
    sdt_int32u                 mRtu_baudrate;
    sdt_int32u                 mRtu_sysFrequency;
    mRtu_master_parity_def     mRtu_parity;
    mRtu_master_stopBits_def   mRtu_stopBits;
}mRtu_master_parameter_def;

//++++++++++++++++++++++++++++++++++task+++++++++++++++++++++++++++++++++++++++
//name:mRtu任务
//-----------------------------------------------------------------------------
void mde_mRtu_master_task(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//name:发送0x03命令
//主机发送一次0x03命令的报文
//in:  in_solidNum    --实例号，
//     in_slave_addr  --从机地址，
//     in_reg_addr    --读取的寄存器首地址，
//     in_reg_length  --读取的寄存器长度
//-----------------------------------------------------------------------------
void mde_mRtu_master_cmd0x03_transmit(sdt_int8u in_solidNum,sdt_int8u in_slave_addr,\
                                      sdt_int16u in_reg_addr,sdt_int16u in_reg_length);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++