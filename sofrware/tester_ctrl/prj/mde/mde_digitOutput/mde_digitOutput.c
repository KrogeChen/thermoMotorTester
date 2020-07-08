//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\depend\snail_data_types.h"
#include ".\depend\bps_digitOutput.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//14个输出IO
//-----------------------------------------------------------------------------
void mde_ouput_port(sdt_int8u in_port_num,sdt_bool in_new_put)
{
    static sdt_bool cfged = sdt_false;

    while(1)
    {
        if(cfged)
        {
            if(0 == in_port_num)
            {
                bsp_output_Y0(in_new_put);
            }else if(1 == in_port_num)
            {
                bsp_output_Y1(in_new_put);
            }else if(2 == in_port_num)
            {
                bsp_output_Y2(in_new_put);
            }else if(3 == in_port_num)
            {
                bsp_output_Y3(in_new_put);
            }else if(4 == in_port_num)
            {
                bsp_output_Y4(in_new_put);
            }else if(5 == in_port_num)
            {
                bsp_output_Y5(in_new_put);
            }else if(6 == in_port_num)
            {
                bsp_output_Y6(in_new_put);
            }else if(7 == in_port_num)
            {
                bsp_output_Y7(in_new_put);
            }else if(8 == in_port_num)
            {
                bsp_output_Y8(in_new_put);
            }else if(9 == in_port_num)
            {
                bsp_output_Y9(in_new_put);
            }else if(10 == in_port_num)
            {
                bsp_output_Y10(in_new_put);
            }else if(11 == in_port_num)
            {
                bsp_output_Y11(in_new_put);
            }else if(12 == in_port_num)
            {
                bsp_output_Y12(in_new_put);
            }else if(13 == in_port_num)
            {
                bsp_output_Y13(in_new_put);
            }
            break;
        }
        else
        {
            bsp_output_cfg();
            cfged = sdt_true;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++