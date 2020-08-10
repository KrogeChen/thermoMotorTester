#ifndef app_thermo_H
#define app_thermo_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------------------------------------------
void app_thermoMotor_ts(void);
sdt_int16u app_pull_stroke_time(void);
sdt_bool app_pull_sme_state(void);
sdt_int32s app_pull_stroke_measure(void);
sdt_int32s app_pull_stroke_max(void);
void app_entry_strat_measure(void);
void app_entry_stop_measure(void);
void app_entry_stopAndUnload(void);
void app_push_voltage_select(sdt_int16u in_voltage);
sdt_int16u app_pull_voltage_select(void);
void app_push_product_select(sdt_int16u in_type);
sdt_int16u app_pull_porduct_select(void);
sdt_bool app_pull_vp_selected(void);
void app_push_vp_select(sdt_bool in_select);
sdt_bool app_pull_emergercy(void);
void app_push_auto_unload(void);
sdt_int16u app_pull_second_3_5T(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif