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
//200ms循环
//----------------------------------------------------------------
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
        modbus_gui_def  modbus_gui;
        unsigned short backup_key_ss;
        unsigned short locked_menu_cnt;
        unsigned short backup_second;
		
        short test_s;
        float test_f;
    };
}sc_parameter_def;

sc_parameter_def  sc_parameter;
//-----------------------------------------------------------------
//窗口索引
#define win_ix_rg_site      "LW"
#define win_ix_rg_addr      50
#define WIN_SELECT          10
#define WIN_MEASURE         0
//--------------------------------------------------------------------
//测量状态值
#define measure_states_rg_stie     "LW"
#define measure_states_rg_addr      19
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
//++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++
void get_remote_gui(void)
{
    
}
//++++++++++++++++++++++++++++++++++++++
void read_sc_parameter(void)
{
   // 
    sc_parameter.test_f +=0.001;
  // WriteLocal("LW",300,100,&sc_parameter.buff[0],0);
}
//++++++++++++++++++++++++++++++++++++++
int MacroEntry()
{
//read keyboard
//-----------------------------------------------------------------------
	#define key_sel_ok_site     "LB"
	#define key_sel_ok_addr      100
	unsigned short key_select;
	ReadLocal(key_sel_ok_site,key_sel_ok_addr,1,&key_select,0);
	key_select &= 0x0001;
	
	unsigned short key_start;
	ReadLocal("LB",2,1,&key_start,0);
	key_start &= 0x0001;
	
	unsigned short key_stop;
	ReadLocal("LB",3,1,&key_stop,0);
	key_stop &= 0x0001;
	
	unsigned short key_auto_unload;
	ReadLocal("LB",1,1,&key_auto_unload,0);
	key_auto_unload &= 0x0001;
//-----------------------------------------------------------------------
    unsigned short voltage_select_win;
	ReadLocal("LW",100,1,&voltage_select_win,0);
	unsigned short product_select_win
	ReadLocal("LW",101,1,&voltage_select_win,0);
	
//-----------------------------------------------------------------------
//全局变量数据
    ReadLocal("LW",1000,100,&sc_parameter.buff[0],0);
//-----------------------------------------------------------------------
//modbus数据
	unsigned short modbus_reg[20];
    unsigned short i;
    for(i = 0;i  < 20;i ++)
    {
        modbus_reg[i] = modbus_rw[i];
    }
//-----------------------------------------------------------------------
//同步远程数据

    if(0 == sc_parameter.locked_menu_cnt)
    {
        sc_parameter.modbus_gui.m_gui_menu = (modbus_gui_menu_def)modbus_reg[regAddr_m_gui_menu];  //加载控制板主菜单
        sc_parameter.modbus_gui.m_gui_sm =  (modbus_gui_menu_def)modbus_reg[regAddr_m_gui_sm];     //加载控制板子菜单
    }
    else
    {
        sc_parameter.locked_menu_cnt --;
    }

    //voltage_select_win = modbus_reg[regAddr_m_select_voltage];
	//product_select_win = modbus_reg[regAddr_m_select_product];
//---------------------------------------------------------------------------------------------
    #define measure_um_rg_stie        "LW"//显示框地址，测量值
    #define measure_um_rg_addr        10
	
    signed int rd_measure_um;
    rd_measure_um = modbus_reg[regAddr_m_msrGt_um_0];
    rd_measure_um = rd_measure_um<<16;
    rd_measure_um |= modbus_reg[regAddr_m_msrGt_um_1];
    float s_measure_um;
    s_measure_um = (float)rd_measure_um/1000;
    WriteLocal(measure_um_rg_stie,measure_um_rg_addr,2,&s_measure_um ,0);
//---------------------------------------------------------------------------------------------
    rd_measure_um = modbus_reg[regAddr_m_msrGt_max_0];
    rd_measure_um = rd_measure_um<<16;
    rd_measure_um |= modbus_reg[regAddr_m_msrGt_max_1];
    float rdf_measure_um;
    rdf_measure_um = (float)rd_measure_um/1000;
    WriteLocal("LW",12,2,&rdf_measure_um ,0);//最大值
//---------------------------------------------------------------------------------------------
    unsigned short rd_35t_second;
    rd_35t_second = modbus_reg[regAddr_m_second_3_5T];
    WriteLocal("LW",14,1,&rd_35t_second ,0);//3.5mm的时间
//---------------------------------------------------------------------------------------------
    unsigned short m_second;
    m_second = modbus_reg[regAddr_m_msrSecond]; //测量时间
//---------------------------------------------------------------------------------------------
    unsigned short win_menu;
    ReadLocal(win_ix_rg_site,win_ix_rg_addr,1,&win_menu,0);//窗口索引
//---------------------------------------------------------------------------------------------
    WriteLocal("LW",30,1,&sc_parameter.modbus_gui.m_gui_s_measure ,0);//test code
	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    unsigned short show_states = MSS_S_IDLE;
//---------------------------------------------------------------------------------------------
    switch(sc_parameter.modbus_gui.m_gui_menu)//主菜单
    {
         case mgm_select:
         { 
             if(WIN_SELECT != win_menu)
             {
                 win_menu  = WIN_SELECT;
             }

             WriteLocal("LW",500,1,&key_select ,0);  //test code
             if(key_select)
             {
                 win_menu = WIN_MEASURE;
                 modbus_rw[regAddr_m_event_bits] = bits_mEBits_selectCMT;
                 modbus_rw[regAddr_m_gui_menu] = mgm_measure;
				 modbus_rw[regAddr_m_select_voltage] = voltage_select_win;
				 modbus_rw[regAddr_m_select_product] = product_select_win;
                 sc_parameter.modbus_gui.m_gui_menu = mgm_measure;
                 key_select = 0;
                 
                 sc_parameter.locked_menu_cnt =10;
             }
             break;
         }
         case mgm_measure:
         {

             if(WIN_MEASURE != win_menu)
             {
                 win_menu  = WIN_MEASURE;
             }

			 switch(sc_parameter.modbus_gui.m_gui_s_measure)//测量子菜单
			 {
                case mgs_ms_idle:
				{
                    show_states = MSS_S_IDLE;

                    run_states = 0;
               

					if(key_start)
					{
						modbus_rw[regAddr_m_event_bits] = bits_mEBits_start;
					}
				    break;
				}
				case mgs_ms_loading:
				{
                    show_states = MSS_S_DOWN_W;
					
                    run_states = 1;
                    pause_chart = 1;
                    clear_chart = 1;
					break;
				}
				case mgs_ms_measuring:
				{
                    show_states = MSS_S_MEASURE;
					
                    if(m_second != sc_parameter.backup_second)
                    {
                        if(pause_chart)
                        {
                            pause_chart = 0;
                           //clear_chart = 0;
                        }
                        else
                        {
                            WriteLocal("LW",0,1,&m_second,0);
                            WriteLocal("LW",1,2,&s_measure_um,0);
                        }
                    }

                    if(key_stop)
                    {
                        modbus_rw[regAddr_m_event_bits] = bits_mEBits_stop;
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

                    run_states = 0;
					if(m_second >= 600)
				    {
						pause_chart = 1;
					}
					else
					{
						if(m_second != sc_parameter.backup_second)
						{
							if(pause_chart)
							{
								pause_chart = 0;
						       //clear_chart = 0;
							}
							else
							{
								WriteLocal("LW",0,1,&m_second,0);       //X轴数据
								WriteLocal("LW",1,2,&s_measure_um,0);   //Y轴数据
						   }
						}						
					}

                    if(key_auto_unload)
                    {
                        modbus_rw[regAddr_m_event_bits] = bits_mEBits_autoUnload;
                    }

                    if(key_start)
                    {
                        modbus_rw[regAddr_m_event_bits] = bits_mEBits_start;
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    WriteLocal(measure_states_rg_stie,measure_states_rg_addr,1,&show_states,0);
    WriteLocal(win_ix_rg_site,win_ix_rg_addr,1,&win_menu,0);
    WriteLocal(key_sel_ok_site,key_sel_ok_addr,1,&key_select,0);
    WriteLocal("LW",1000,100,&sc_parameter.buff[0],0);
	return 0;
}
 