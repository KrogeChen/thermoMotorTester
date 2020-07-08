//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef bsp_digitInput_H
#define bsp_digitInput_H
//-----------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:IO配置
//in: 
//out: 
//-----------------------------------------------------------------------------
void bsp_input_port_cfg(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_input_X0(void);
sdt_bool bsp_pull_input_X1(void);
sdt_bool bsp_pull_input_X2(void);
sdt_bool bsp_pull_input_X3(void);
sdt_bool bsp_pull_input_X4(void);
sdt_bool bsp_pull_input_X5(void);
sdt_bool bsp_pull_input_X6(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++