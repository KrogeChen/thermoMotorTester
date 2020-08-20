//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_mRtuMaster.h"
#include "..\..\pbc\pbc_dataConvert\pbc_dataConvert.h"
#include "..\..\pbc\pbc_crc16\pbc_crc16.h"
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
#include ".\depend\bsp_mRtuMaster.h"
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//modbus 主机模块,负责报文的发送和接收控制
//支持命令: 0x03 0x06 0x10 0x17
//支持多个实例
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    mmRunS_idle             = 0x00,
    mmRunS_transmit_str,
    mmRunS_transmit_35T,
    mmRunS_transmit_data,
    mmRunS_transmit_stop,    
    mmRunS_transmit_end,
    mmRunS_receive_wait,
    mmRunS_receive_data,
    mmRunS_receive_end,

    
}modbus_master_runState_def;

//modbus操作结构体
//-----------------------------------------------------------------------------
typedef struct
{
   // mRtu_parameter_def  mRtu_parameter;
    mRtu_master_status_def      mmRtu_status;
    modbus_master_runState_def  mmoo_runStutus;


    sdt_int8u  receive_buff[256];
    sdt_int8u  rev_index;
    sdt_int8u  transmit_buff[256];
    sdt_int8u  transmit_length;
    sdt_int8u  transmit_index;
    timerClock_def timer_revTimeOut;

    sdt_int16u  readReg_addr;
    sdt_int8u   readReg_length;
    sdt_int16u  writeReg_addr;
    sdt_int8u   writeReg_length;

    void (*phy_into_receive)(void);
    sdt_bool (*pull_receive_byte)(sdt_int8u* out_rByte);
    sdt_bool (*pull_busFree)(sdt_int8u t_char_dis);
    void (*restart_busFree_timer)(void);

    void (*phy_into_transmit_status)(void);
    sdt_bool (*push_transmit_byte)(sdt_int8u in_tByte);
    sdt_bool (*pull_transmit_complete)(void);
}modbus_master_oper_def;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_bool modbus_master_receive_protocol(modbus_master_oper_def* mix_mm_oper);
//--------------------------------------------------------------------------------------------------------------------------
//主收发任务模块
//--------------------------------------------------------------------------------------------------------------------------
static void modbus_master_oop_task(modbus_master_oper_def* mix_mm_oper)
{
    pbc_timerMillRun_task(&mix_mm_oper->timer_revTimeOut);
    switch(mix_mm_oper->mmoo_runStutus)
    {
        case mmRunS_idle:
        {
            break;
        }
        case mmRunS_transmit_str:
        {
            mix_mm_oper->phy_into_transmit_status();
            mix_mm_oper->restart_busFree_timer();
            mix_mm_oper->mmoo_runStutus = mmRunS_transmit_35T;
            break;
        }
        case mmRunS_transmit_35T:
        {
            if(mix_mm_oper->pull_busFree(35))
            {
                mix_mm_oper->mmoo_runStutus = mmRunS_transmit_data;
                mix_mm_oper->transmit_index = 0;
            }
            break;
        }
        case mmRunS_transmit_data:
        {
            if(mix_mm_oper->transmit_length != 0)
            {
                sdt_bool push_succeed;
                while(1)
                {
                    push_succeed = mix_mm_oper->push_transmit_byte(mix_mm_oper->transmit_buff[mix_mm_oper->transmit_index]);
                    if(push_succeed)
                    {
                        mix_mm_oper->transmit_index ++;
                        mix_mm_oper->transmit_length --;
                        if(0 == mix_mm_oper->transmit_length)
                        {
                            mix_mm_oper->mmoo_runStutus = mmRunS_transmit_stop;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        }
        case mmRunS_transmit_stop:
        {
            if(mix_mm_oper->pull_transmit_complete())
            {
                mix_mm_oper->restart_busFree_timer();
                mix_mm_oper->mmoo_runStutus = mmRunS_transmit_end;
            }
            break;
        }
        case mmRunS_transmit_end:
        {
            if(mix_mm_oper->pull_busFree(25)) //标准3.5T，使用2.5T的结束符，放宽检测条件
            {
                mix_mm_oper->phy_into_receive();
                mix_mm_oper->mmoo_runStutus = mmRunS_receive_wait;//转入接收等待，设置超时
                pbc_reload_timerClock(&mix_mm_oper->timer_revTimeOut,100); //100ms timeout
            }
            break;
        }
        case mmRunS_receive_wait:
        {
            sdt_int8u receive_byte;
            if(mix_mm_oper->pull_receive_byte(&receive_byte))
            {
                mix_mm_oper->receive_buff[0] = receive_byte;
                mix_mm_oper->rev_index = 1;
                mix_mm_oper->mmoo_runStutus = mmRunS_receive_data;
                mix_mm_oper->restart_busFree_timer();
            }
            else if(pbc_pull_timerIsCompleted(&mix_mm_oper->timer_revTimeOut))
            {
                mix_mm_oper->mmRtu_status = mRtuS_master_timeout;  //超时
                mix_mm_oper->mmoo_runStutus = mmRunS_idle;
            }
            break;
        }
        case mmRunS_receive_data:
        {
            while(1)
            {
                sdt_int8u receive_byte;
                if(mix_mm_oper->pull_receive_byte(&receive_byte))
                {
                    mix_mm_oper->receive_buff[mix_mm_oper->rev_index] = receive_byte;
                    mix_mm_oper->rev_index ++;
                    mix_mm_oper->restart_busFree_timer();
                }
                else
                {
                    if(mix_mm_oper->pull_busFree(20))  //标准3.5T,检测2.0T视为报文完成
                    {
                        if(modbus_master_receive_protocol(mix_mm_oper))
                        {
                            mix_mm_oper->mmRtu_status = mRtuS_master_complete;
                            mix_mm_oper->mmoo_runStutus = mmRunS_idle;
                        }
                        else
                        {
                            mix_mm_oper->mmRtu_status = mRtuS_master_poterr; 
                            mix_mm_oper->mmoo_runStutus = mmRunS_idle;  //产生接收错误
                        }
                    }
                    break; 
                }
            }
            break;
        }

        default:
        {
            mix_mm_oper->mmoo_runStutus = mmRunS_idle;
            break;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//接收协议处理
//--------------------------------------------------------------------------------------------------------------------------
static sdt_bool modbus_master_receive_protocol(modbus_master_oper_def* mix_mm_oper)
{
    sdt_int8u rd_length;

    rd_length = mix_mm_oper->rev_index;
    if(rd_length < 6)
    {
        return(sdt_false);
    }
    else
    { 
        if((mix_mm_oper->transmit_buff[0]== mix_mm_oper->receive_buff[0]) && (mix_mm_oper->transmit_buff[1]== mix_mm_oper->receive_buff[1]))  //address and command is ok
        {
            sdt_int8u crc_value[2];
            Crc16CalculateOfByte(&mix_mm_oper->receive_buff[0],(rd_length-2),&crc_value[0]);
            if((crc_value[1] == mix_mm_oper->receive_buff[rd_length-2]) && (crc_value[0] == mix_mm_oper->receive_buff[rd_length-1]))//crc is ok
            {
                
                if(0x03 == mix_mm_oper->receive_buff[1])
                {
                  // mix_mm_oper->readReg_addr = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[2]);
                  // mix_mm_oper->readReg_length = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[4]);

                  // mix_mm_oper->transmit_buff[0] = mix_mm_oper->mRtu_parameter.mRtu_address;
                  // mix_mm_oper->transmit_buff[1] = 0x03;
                  // mix_mm_oper->transmit_buff[2] = mix_mm_oper->readReg_length * 2;//byte count
                  // mix_mm_oper->transmit_length = 3;

                  // mix_mm_oper->mRtu_status = mRtuS_read;
                }
                else if(0x06 == mix_mm_oper->receive_buff[1])
                {

                }
                else if(0x10 == mix_mm_oper->receive_buff[1])
                {

                }
                else if(0x17 == mix_mm_oper->receive_buff[1])
                {
                 // mix_mm_oper->readReg_addr = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[2]);
                 // mix_mm_oper->readReg_length = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[4]);
                 // mix_mm_oper->writeReg_addr = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[6]);
                 // mix_mm_oper->writeReg_length = pbc_arrayToInt16u_bigEndian(&mix_mm_oper->receive_buff[8]);
                 // 
                 // mix_mm_oper->transmit_buff[0] = mix_mm_oper->mRtu_parameter.mRtu_address;
                 // mix_mm_oper->transmit_buff[1] = 0x17;
                 // mix_mm_oper->transmit_buff[2] = mix_mm_oper->readReg_length * 2;
                 // mix_mm_oper->transmit_length = 3;

                 // mix_mm_oper->mRtu_status = mRtuS_rwBoth;
                }
                else
                {
                    
                }
                return(sdt_true);
            }
        }
    }
    return(sdt_false);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void append_crc_to_message(modbus_master_oper_def* mix_mm_oper)
{
    sdt_int8u crc_value[2];
        
    Crc16CalculateOfByte(&mix_mm_oper->transmit_buff[0],(sdt_int16u)mix_mm_oper->transmit_length,&crc_value[0]);//crc
    mix_mm_oper->transmit_buff[mix_mm_oper->transmit_length] = crc_value[1];
    mix_mm_oper->transmit_buff[mix_mm_oper->transmit_length+1] = crc_value[0];
    mix_mm_oper->transmit_length += 2;
}
//+++++++++++++++++++++++++++++++solid++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define max_solid    1
//--------------------------------------------------------------------------------------------------------------------------
static modbus_master_oper_def modbus_master_solid[max_solid];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void modbus_master_solid_cfg(void)
{
//--------------------------------------------------------------------------------------------------------------------------
    bsp_uart5_cfg();
    modbus_master_solid[0].pull_receive_byte = bsp_pull_oneByte_uart5_rxd;
    modbus_master_solid[0].push_transmit_byte = bsp_push_oneByte_uart5_txd;
    modbus_master_solid[0].pull_busFree = bsp_uart5_busFree;
    modbus_master_solid[0].restart_busFree_timer = bsp_restart_tim4;
    modbus_master_solid[0].phy_into_receive = bps_uart5_into_receive;
    modbus_master_solid[0].phy_into_transmit_status = bps_uart5_into_transmit;
    modbus_master_solid[0].pull_transmit_complete =bsp_pull_uart5_txd_cmp;
//---------------------------------------------------------------------------------------------------------------------------
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:mRtu任务
//--------------------------------------------------------------------------------------------------------------------------
void mde_mRtu_master_task(void)
{
    static sdt_bool cfged = sdt_false;

    if(cfged)
    {
        sdt_int8u i;
        for(i = 0;i < max_solid;i ++)
        {
            modbus_master_oop_task(&modbus_master_solid[i]);
        }
    }
    else
    {
        cfged = sdt_true;
        modbus_master_solid_cfg();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_mRtu_master_cmd0x03_transmit(sdt_int8u in_solidNum,sdt_int8u in_slave_addr,\
                                      sdt_int16u in_reg_addr,sdt_int16u in_reg_length)
{
    modbus_master_solid[in_solidNum].transmit_buff[0] = in_slave_addr;
    modbus_master_solid[in_solidNum].transmit_buff[1] = 0x03;
    modbus_master_solid[in_solidNum].transmit_buff[2] = in_reg_addr >> 8;
    modbus_master_solid[in_solidNum].transmit_buff[3] = in_reg_addr;
    modbus_master_solid[in_solidNum].transmit_buff[4] = in_reg_length >> 8;
    modbus_master_solid[in_solidNum].transmit_buff[5] = in_reg_length;
    modbus_master_solid[in_solidNum].transmit_length = 6;
    append_crc_to_message(&modbus_master_solid[in_solidNum]);
    modbus_master_solid[in_solidNum].mmoo_runStutus = mmRunS_transmit_str;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
