#ifndef app_modbus_H
#define app_modbus_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{   
    mgm_select           = 0x00,//电压、产品选择
    mgm_measure          = 0x01,//测量界面
    mgm_parameter_s      = 0x02,//参数设定
    mgm_em_stop          = 0x03,//急停
}modbus_gui_menu_def;
//-----------------------------------------------------------------------------
//测量子菜单
typedef enum
{
    mgs_ms_idle         = 0x00,
    mgs_ms_loading      = 0x01,//加负载
    mgs_ms_measuring    = 0x02,//测量中
    mgs_ms_unloading    = 0x03,
    mgs_ms_complete     = 0x04,
}modbus_gui_s_measure_def;
//-----------------------------------------------------------------------------
typedef struct
{
    modbus_gui_menu_def  m_gui_menu;
    sdt_int16u           m_gui_bits;
    union
    {
        sdt_int16u  m_gui_sm;
        modbus_gui_s_measure_def  m_gui_s_measure;
    };

}modbus_gui_def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define regAddr_m_version        0x0000
#define regAddr_m_gui_menu       0x0001//gui 主菜单
#define regAddr_m_gui_sm         0x0002//gui 子菜单
#define regAddr_m_gui_bits       0x0003//gui 位标识
//-----------------------------------------------------------------------------
#define regAddr_m_states_bits    0x0004
#define bits_mSBits_gzero        sdt_bit0//光栅零点寻找完毕
#define bits_mSBits_selected     sdt_bit1//已完成电压、型号选择
#define bits_mSBits_doorOpen     sdt_bit2//门被打开
#define bits_mSBits_emergercy    sdt_bit3//
//-----------------------------------------------------------------------------
#define regAddr_m_event_bits      0x0005   
//-----------------------------------------------------------------------------
#define bits_mEBits_start         sdt_bit0//开始测量
#define bits_mEBits_stop          sdt_bit1//停止测量
#define bits_mEBits_load          sdt_bit2//加载
#define bits_mEBits_unload        sdt_bit3
#define bits_mEBits_selectCMT     sdt_bit4//选择完毕
#define bits_mEBits_heat          sdt_bit5//加热
#define bits_mEBits_unheat        sdt_bit6//不加热
#define bits_mEBits_autoUnload    sdt_bit7//自动卸载
//-----------------------------------------------------------------------------
#define regAddr_m_msrSecond        0x0006
#define regAddr_m_msrGt_um_0       0x0007
#define regAddr_m_msrGt_um_1       0x0008
#define regAddr_m_msrGt_max_0      0x0009
#define regAddr_m_msrGt_max_1      0x000A
#define regAddr_m_grating_pds_0    0x000B//物理位置,read
#define regAddr_m_grating_pds_1    0x000C
#define regAddr_m_logic_zero_0     0x000D//逻辑零点,rw
#define regAddr_m_logic_zero_1     0x000E
#define regAddr_m_select_voltage   0x000F//电压等级
#define regAddr_m_select_product   0x0010//产品类型
#define regAddr_m_second_3_5T      0x0011//3.5行程时间
#define regAddr_m_pt100_tway_0     0x0012//温度值0通道  
#define regAddr_m_pt100_tway_1     0x0013
#define regAddr_m_pt100_tway_2     0x0014
#define regAddr_m_pt100_tway_3     0x0015

//-----------------------------------------------------------------------------
void app_modbus_task(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_local_gui_menu(modbus_gui_menu_def in_menu);
void app_push_local_gui_sm(modbus_gui_s_measure_def in_gui_sm);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif