//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef app_storage_H
#define app_storage_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef union
{
    sdt_int32u sto_data[32];
    struct
    {
        sdt_int32s  grating_up_site_um;        //上行到位位置值
        sdt_int32s  grating_down_site_um;      //下行到位位置值
        sdt_int32s  grating_zero_logic_um;     //逻辑零点值
        sdt_int16u  select_voltage;
        sdt_int16u  select_product;

    };
}StoRunParamter_Def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_read_run_parameter(void);
void app_sto_run_parameter_task(void);
void app_push_once_save_sto_parameter(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern StoRunParamter_Def  StoRunParamter;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
