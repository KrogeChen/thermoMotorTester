#ifndef app_thermo_H
#define app_thermo_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_thermoMotor_ts(void);
sdt_int16u app_pull_stroke_time(void);
sdt_bool app_pull_sme_state(void);
sdt_int32s app_pull_stroke_measure(void);
void app_entry_strat_measure(void);
void app_entry_stop_measure(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif