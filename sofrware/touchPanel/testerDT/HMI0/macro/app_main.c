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
//200msѭ��
//----------------------------------------------------------------
#define reg_version   0
#define reg_ststeW    1
#define reg_ctrlW      2
#define reg_second   3
#define reg_um_0     4
#define reg_um_1     5
//---------------------------------------------------------------
#define rs_idle                0
#define rs_waiting_run   1
#define rs_running          2
//---------------------------------------------------------------
#define max_m35_S     160
#define max_sk_MM      5.5
#define min_sk_MM       4.5
//---------------------------------------------------------------
typedef union
{
    unsigned short buff[100];
    struct
    {
        float test_f;
    };
}sc_parameter_def;

sc_parameter_def  sc_parameter;
void read_sc_parameter(void)
{
   // 
    sc_parameter.test_f +=0.001;
  // WriteLocal("LW",300,100,&sc_parameter.buff[0],0);
}
int MacroEntry()
{
    signed int rd_um = 0;
   
   float test = 0;
   signed short tt = 10;
   ReadLocal("LW",300,100,&sc_parameter.buff[0],0);
   read_sc_parameter();
  WriteLocal("LW",300,100,&sc_parameter.buff[0],0);
   test = sizeof(sc_parameter);
   WriteLocal("LW",202,2,&sc_parameter.test_f ,0);
   //WriteLocal("LW",0,2, &tt,0);
    
    rd_um =  modbus_reg[reg_um_0];
    rd_um = rd_um << 16;
    rd_um |= modbus_reg[reg_um_1];
   
   
    
    if(rs_idle == run_state)
    {
        if(key_st)
        {
             run_state = rs_waiting_run;
             chart_clear = 1;
             sign_pass = 0;
             sign_notgood = 0;
             sign_notgood_tim = 0;
             sign_notgood_sk = 0;
            grating_second = 0;
            grating_um = 0;
            max_m_um = 0;
            get_s_3_5mm = 0;
            m35_second = 0;
            modbus_reg[reg_ctrlW] = 0x0001;
            state_txt=1;
        }
    }
    else if(rs_waiting_run == run_state)
    {
        if(modbus_reg[reg_ststeW] & 0x0001)
        {
            run_state = rs_running;
            state_txt=2;
        }
        if(0 == key_st)
        {
             run_state = rs_idle;
             modbus_reg[reg_ctrlW] = 0x0002;
             state_txt=0;
        }
    }
    else if(rs_running == run_state)
    {
       //grating_um = grating_um+0.02;
       //grating_second = grating_second+1;
        grating_um = (float)rd_um / 1000;
        grating_second = modbus_reg[reg_second];     
        
        if(0 == get_s_3_5mm)
        {
             if(grating_um >= 3.5)
             {
                  get_s_3_5mm = 1;
                  m35_second = grating_second; 
						if(m35_second < max_m35_S)
						{
						}
						else
						{
							sign_notgood_tim = 1;
						}
             }
        }

        if(max_m_um < grating_um)
        {
             max_m_um = grating_um;
            if(max_m_um > max_sk_MM)
            {
                sign_notgood_sk = 1;
            }
        }

        if(grating_second > 600)
        {
            key_st = 0;
        }
        if(0 == key_st)
        {
            run_state = rs_idle;
             state_txt=0;
            modbus_reg[reg_ctrlW] = 0x0002;

         
            if((max_m_um > max_sk_MM) || (max_m_um < min_sk_MM))
            {
                sign_notgood_sk = 1;
            }

            if((0 == sign_notgood_tim) && (0 ==sign_notgood_sk))
            {
                sign_pass = 1;
            }
            else
            {
                sign_notgood = 1;
            }
        }
    }
    else
    {
         run_state = rs_idle;
    }
	 return 0;
}
 