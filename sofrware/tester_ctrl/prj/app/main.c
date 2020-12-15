//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
#include "math.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//sdt_int16u slope_angle;

int main (void)
{
//    double k_slope;
//    sdt_int32s nearly_2500um,nearly_1000um,second_for_2500um,second_for_1000um;
//    nearly_2500um = 2500;
//    nearly_1000um = 1000;
//    second_for_2500um = 40;
//    second_for_1000um = 20;
//    
//    #define pix_mul  45//X Y的像素倍率
//    double val;
//    val =180/3.14159;  //弧度角度转换系数
//    
//    k_slope = ((double)(nearly_2500um - nearly_1000um)/1000*pix_mul)/(double)(second_for_2500um - second_for_1000um);
//    slope_angle = (sdt_int16u)((atan(k_slope)*val)*10);
                        
    mde_watchdog_cfg();
    mde_systemClock_cfg();
//-----------------------------------------------------------------------------
    pbc_createTask_one(app_general_task,0);
    pbc_createTask_one(app_modbus_task,0);
//-----------------------------------------------------------------------------
    pbc_sysTickTaskProcess();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++