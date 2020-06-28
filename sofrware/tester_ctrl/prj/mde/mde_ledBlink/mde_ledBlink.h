#ifndef med_ledBlink_H
#define med_ledBlink_H
//-----------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void mde_ledBlink_task(void);
//-----------------------------------------------------------------------------
void mde_ledBlink_change_time(sdt_int8u in_solidNum,sdt_int16u in_period_time,sdt_int16u in_light_time);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
