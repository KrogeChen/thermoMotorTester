#include "macrotypedef.h"
#include "math.h"

/*
	Read,Write Local address function:
  	int ReadLocal( const char *type, int addr, int nRegs, void *buf, int flag  );
	int WriteLocal( const char *type, int addr, int nRegs, void *buf , int flag );

	Parameter:     type     is the string of "LW","LB" etc;
								address is the Operation address ;
 								nRegs    is the length of read or write ;
								buf        is the buffer which store the reading or writing data;
 								flag       is 0,then codetype is BIN,is 1  then codetype is BCD;
	return value : 1  ,Operation success
 								0,  Operation fail.

 	eg: read the value of local lw200 and write it to the lw202,with the codetype BIN,
		The code is :

    	short buf[2] = {0};
		ReadLocal("LW", 200, 2, (void*)buf, 0);
		WriteLocal("LW", 202, 2, (void*)buf, 0);
*/
//100ms循环
//----------------------------------------------------------------
typedef enum

{   

    mgm_select           = 0x0000,//电压、产品选择

    mgm_measure          = 0x0001,//测量界面

    mgm_parameter_s      = 0x0002,//参数设定

    mgm_em_stop          = 0x0003,//急停
    mgm_none             = 0xffff,//初始值

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

    modbus_gui_menu_def     m_gui_menu;
    unsigned short          m_gui_bits;
    union

    {

        unsigned short            m_gui_sm;
        modbus_gui_s_measure_def  m_gui_s_measure;

    };
}modbus_gui_def;
//---------------------------------------------------------------
typedef union
{
    unsigned short buff[100];
    struct
    {
        unsigned short cfged;
        modbus_gui_menu_def        main_gui_menu;
        modbus_gui_s_measure_def   son_measure_menu; //测量子菜单
        
        modbus_gui_def  modbus_gui;
        unsigned short backup_key_ss;
        unsigned short locked_menu_cnt;
        unsigned short backup_second;
		
        unsigned short one_second;
        short test_s;
        float test_f;
    };
}pbulic_para_def;

pbulic_para_def  pbulic_para;
//-----------------------------------------------------------------
//窗口索引
#define WIN_SELECT          10
#define WIN_MEASURE         0
//--------------------------------------------------------------------
//测量状态值
#define MSS_S_IDLE                  0
#define MSS_S_DOWN_W                1
#define MSS_S_MEASURE               2
#define MSS_S_UP_W                  3
#define MSS_S_COMPLETE              4
//---------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++
#define  sdt_bit0     0x0001

#define  sdt_bit1     0x0002

#define  sdt_bit2     0x0004

#define  sdt_bit3     0x0008

#define  sdt_bit4     0x0010

#define  sdt_bit5     0x0020

#define  sdt_bit6     0x0040

#define  sdt_bit7     0x0080

#define  sdt_bit8     0x0100

#define  sdt_bit9     0x0200

#define  sdt_bit10    0x0400

#define  sdt_bit11    0x0800

#define  sdt_bit12    0x1000

#define  sdt_bit13    0x2000

#define  sdt_bit14    0x4000

#define  sdt_bit15    0x8000
//-----------------------------------------------------------------
#define regAddr_m_version        0x0000

#define regAddr_m_gui_menu       0x0001//gui 主菜单

#define regAddr_m_gui_sm         0x0002//gui 子菜单

#define regAddr_m_gui_bits       0x0003//gui 位标识

//-----------------------------------------------------------------------------

#define regAddr_m_states_bits    0x0004

#define bits_mSBits_gzero        sdt_bit0//光栅零点寻找完毕

#define bits_mSBits_selected     sdt_bit1//已完成电压、型号选择

#define bits_mSBits_doorOpen     sdt_bit2//门被打开

#define bits_mSBits_emergercy    sdt_bit3

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
#define regAddr_m_temperature_now  0x0016  //当前PTC温度
#define regAddr_m_temperature_max  0x0017  //最大PTC温度
#define regAddr_m_timeout_heating  0x0018  //加热时间
//++++++++++++++++++++++++++++++++++++++
//LW内存分配
//窗口参数:电压选择、产品选择、加热时间选择
#define chart_X_second_addr      0 //1 word,图表X轴 16bits,short
#define chart_Y_mm_addr          1 //2 word,图表Y轴 32bits,float
#define dis_measure_stroke_addr  3 //2 word,当前测量行程
#define dis_max_stroke_addr      5 //2 word,最大行程
#define dis_s_25_stroke_addr     7 //1 word,2.5行程时间
#define dis_s_35_stroke_addr     8 //1 word,3.5行程时间
#define par_volatge_sel_addr     9 //1 word,电压选择
#define par_product_sel_addr     10//1 word,产品选择
#define par_heat_time_addr       11//1 word,加热时间
#define window_index_addr        12//1 word,显示窗口索引
#define measure_states_addr      13//1 word,测量状态

#define measure_um_addr          14//1 word,光栅绝对值

#define public_ram_addr          100//100word,全局ram,用于存储全局变量
//--------------------------------------
//LB内存分配
#define key_sel_ok_addr       0
#define key_start_addr        1
#define key_stop_addr         2
#define key_auto_unload_addr  3
#define key_setup_addr        4

#define chart_pause_addr      20
#define chart_clear_addr      21
#define runing_states_addr    22
//++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++
int MacroEntry()
{
//-----------------------------------------------------------------------
//读取modbus数据
//-----------------------------------------------------------------------
	unsigned short ops_modbus_reg[32];
    unsigned short i;
    for(i = 0;i  < 32;i ++)
    {
        ops_modbus_reg[i] = modbus_rw[i];
    }
//-----------------------------------------------------------------------
    ReadLocal("LW",public_ram_addr,100,&pbulic_para.buff[0],0);
//-----------------------------------------------------------------------
//read keyboard
//-----------------------------------------------------------------------

    
	unsigned short key_select_ok;//选择完毕,电压、产品、加热时间
	ReadLocal("LB",key_sel_ok_addr,1,&key_select_ok,0);
	key_select_ok &= 0x0001;
	
	unsigned short key_start;
	ReadLocal("LB",key_start_addr,1,&key_start,0);
	key_start &= 0x0001;
	
	unsigned short key_stop;
	ReadLocal("LB",key_stop_addr,1,&key_stop,0);
	key_stop &= 0x0001;
	
	unsigned short key_auto_unload;
	ReadLocal("LB",key_auto_unload_addr,1,&key_auto_unload,0);
	key_auto_unload &= 0x0001;
    
    unsigned short key_setup;
    ReadLocal("LB",key_setup_addr,1,&key_setup,0);
    key_setup &= 0x0001;
//-----------------------------------------------------------------------
//read chart states
    unsigned short chart_clear,chart_pause;
    ReadLocal("LB",chart_pause_addr,1,&chart_pause,0);
    chart_pause &= 0x0001;
    ReadLocal("LB",chart_clear_addr,1,&chart_clear,0);
    chart_clear &= 0x0001;
    
    
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------
//显示框地址，测量值
    signed int rd_measure_um;
//    
    rd_measure_um = ops_modbus_reg[regAddr_m_msrGt_um_0];
    rd_measure_um = rd_measure_um<<16;
    rd_measure_um |= ops_modbus_reg[regAddr_m_msrGt_um_1];
    
    float s_measure_um;
//    
    s_measure_um = (float)rd_measure_um/1000;
    WriteLocal("LW",dis_measure_stroke_addr,2,&s_measure_um ,0);
//-----------------------------------------------------------------------
//最大值
    signed int rd_max_um;
    rd_max_um = ops_modbus_reg[regAddr_m_msrGt_max_0];
    rd_max_um = rd_max_um<<16;
    rd_max_um |= ops_modbus_reg[regAddr_m_msrGt_max_1];
    float rd_max_measure_um;
    rd_max_measure_um = (float)rd_max_um/1000;
    WriteLocal("LW",dis_max_stroke_addr,2,&rd_max_measure_um,0);
//-----------------------------------------------------------------------
    signed int rd_um;
    rd_um = ops_modbus_reg[regAddr_m_grating_pds_0];
    rd_um = rd_max_um<<16;
    rd_um |= ops_modbus_reg[regAddr_m_grating_pds_1];
    float rd_um_pds;
    rd_um_pds = (float)rd_um/1000;
    WriteLocal("LW",measure_um_addr,2,&rd_um,0);
    

//-----------------------------------------------------------------------
//3.5mm的时间
    unsigned short rd_35t_second;
    rd_35t_second = ops_modbus_reg[regAddr_m_second_3_5T];
    WriteLocal("LW",dis_s_35_stroke_addr,1,&rd_35t_second ,0);
//-----------------------------------------------------------------------
//测量时间 
    unsigned short m_second;
    m_second = ops_modbus_reg[regAddr_m_msrSecond];  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    #define  cfged_flag 0x8976
//-----------------------------------------------------------------------
    unsigned short show_states = MSS_S_IDLE;
    unsigned short local_win_index;
    unsigned short runing = 0;
    
    
//   pbulic_para.one_second ++;
//   if(pbulic_para.one_second > 9)
//   {
//       pbulic_para.one_second = 0;
//
//       pbulic_para.test_s ++;
//       pbulic_para.test_f += 0.05;
//   
//            
//   }
//   //pbulic_para.main_gui_menu = mgm_measure;
//   ops_modbus_reg[regAddr_m_gui_sm] = mgs_ms_measuring;
//   m_second = pbulic_para.test_s;
//   s_measure_um = pbulic_para.test_f;   
    
    
    
    
    if(cfged_flag == pbulic_para.cfged)
    {
        switch(pbulic_para.main_gui_menu)
        {
            case mgm_none:
            {
                //加载电压、产品选择、加热时间
                WriteLocal("LW",par_volatge_sel_addr,1,&ops_modbus_reg[regAddr_m_select_voltage] ,0);
                WriteLocal("LW",par_product_sel_addr,1,&ops_modbus_reg[regAddr_m_select_product] ,0);
                WriteLocal("LW",par_heat_time_addr,1,&ops_modbus_reg[regAddr_m_timeout_heating] ,0);
                pbulic_para.main_gui_menu = mgm_select;
                break;
            }
            case mgm_select:
            {
                local_win_index = WIN_SELECT;
                if(key_select_ok)
                {
                    key_select_ok = 0;
                    
                    ReadLocal("LW",par_volatge_sel_addr,1,&ops_modbus_reg[regAddr_m_select_voltage] ,0); //读取参数
                    ReadLocal("LW",par_product_sel_addr,1,&ops_modbus_reg[regAddr_m_select_product] ,0);
                    ReadLocal("LW",par_heat_time_addr,1,&ops_modbus_reg[regAddr_m_timeout_heating] ,0);
                    chart_clear = 1;    //清除一次图表
                    chart_pause = 1;
                    pbulic_para.main_gui_menu = mgm_measure;
                    ops_modbus_reg[regAddr_m_event_bits] = bits_mEBits_selectCMT;  //选择完成
                }
                break;
            }
            case mgm_measure:
            {
                local_win_index = WIN_MEASURE;
                if(key_setup)
                {
                    WriteLocal("LW",par_volatge_sel_addr,1,&ops_modbus_reg[regAddr_m_select_voltage] ,0);
                    WriteLocal("LW",par_product_sel_addr,1,&ops_modbus_reg[regAddr_m_select_product] ,0);
                    WriteLocal("LW",par_heat_time_addr,1,&ops_modbus_reg[regAddr_m_timeout_heating] ,0);
                    pbulic_para.main_gui_menu = mgm_select;
                    ops_modbus_reg[regAddr_m_gui_menu] = mgm_select;  //退回到选择界面
                }
                switch(ops_modbus_reg[regAddr_m_gui_sm])  //根据子菜单显示状态
                {
                    case mgs_ms_idle:
                    {
                        pbulic_para.son_measure_menu = ops_modbus_reg[regAddr_m_gui_sm];
                        show_states = MSS_S_IDLE;
                        runing = 0;
                    
                        if(key_start)
                        {
                            ops_modbus_reg[regAddr_m_event_bits] = bits_mEBits_start;
                        }
                        break;
                    }
                    case mgs_ms_loading:
                    {
                        if(pbulic_para.son_measure_menu != ops_modbus_reg[regAddr_m_gui_sm])
                        {
                            pbulic_para.son_measure_menu = ops_modbus_reg[regAddr_m_gui_sm];
                            chart_pause = 1;
                            chart_clear = 1;
                            m_second = 0;
                            s_measure_um = 0;
                            WriteLocal("LW",chart_X_second_addr,1,&m_second,0);
                            WriteLocal("LW",chart_Y_mm_addr,2,&s_measure_um,0);
                        }
                        runing = 1;
                        show_states = MSS_S_DOWN_W;
                        
  
                        break;
                    }
                    case mgs_ms_measuring:
                    {
                        
                        if(pbulic_para.son_measure_menu != ops_modbus_reg[regAddr_m_gui_sm])
                        {
                            pbulic_para.son_measure_menu = ops_modbus_reg[regAddr_m_gui_sm];
                            chart_pause = 0;
                            chart_clear = 0;
                            pbulic_para.backup_second = 0;
                            m_second = 0;
                            s_measure_um = 0;
                            WriteLocal("LW",chart_X_second_addr,1,&m_second,0);
                            WriteLocal("LW",chart_Y_mm_addr,2,&s_measure_um,0);
                        }
                        else
                        {
                            if(m_second != pbulic_para.backup_second)
                            {
                                pbulic_para.backup_second = m_second;
                                WriteLocal("LW",chart_X_second_addr,1,&m_second,0);
                                WriteLocal("LW",chart_Y_mm_addr,2,&s_measure_um,0);
                                
                                 //ReadLocal("LW",chart_Y_mm_addr,2,&s_measure_um,0);
                                
                                //WriteLocal("LW",dis_measure_stroke_addr,2,&s_measure_um ,0);
                                //WriteLocal("LW",dis_s_35_stroke_addr,1,&m_second ,0);
                            }
                        }
                        runing = 1;
                        show_states = MSS_S_MEASURE;
                        if(key_stop)
                        {
                            ops_modbus_reg[regAddr_m_event_bits] = bits_mEBits_stop;
                        }
                        break;
                    }
                    case mgs_ms_unloading:
                    {
                        show_states = MSS_S_UP_W;

                        break;
                    }
                    case mgs_ms_complete:
                    {
                        show_states = MSS_S_COMPLETE;

                        runing = 0;
                        if(m_second >= 600)
                        {
                            chart_pause = 1;
                        }
                        else
                        {
                            if(m_second != pbulic_para.backup_second)
                            {
                                pbulic_para.backup_second = m_second;
                                if(chart_pause)
                                {
                                    chart_pause = 0;
                                   //clear_chart = 0;
                                }
                                else
                                {
                                    WriteLocal("LW",chart_X_second_addr,1,&m_second,0);
                                    WriteLocal("LW",chart_Y_mm_addr,2,&s_measure_um,0);
                               }
                            }						
                        }

                        if(key_auto_unload)
                        {
                            ops_modbus_reg[regAddr_m_event_bits] = bits_mEBits_autoUnload;
                        }

                        if(key_start)
                        {
                            ops_modbus_reg[regAddr_m_event_bits] = bits_mEBits_start;
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case mgm_parameter_s:
            {
                break;
            }
            case mgm_em_stop:
            {
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
        pbulic_para.cfged = cfged_flag;
        pbulic_para.main_gui_menu = mgm_none;
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-----------------------------------------------------------------------
    WriteLocal("LB",chart_pause_addr,1,&chart_pause,0);
    WriteLocal("LB",chart_clear_addr,1,&chart_clear,0);
    WriteLocal("LB",runing_states_addr,1,&runing,0);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    WriteLocal("LW",measure_states_addr,1,&show_states,0);
    WriteLocal("LW",window_index_addr,1,&local_win_index,0);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    WriteLocal("LW",public_ram_addr,100,&pbulic_para.buff[0],0);
//-----------------------------------------------------------------------------------
    for(i = 0;i  < 32;i ++)
    {
        modbus_rw[i] = ops_modbus_reg[i];//modbus内容回写
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	return 0;
}
 