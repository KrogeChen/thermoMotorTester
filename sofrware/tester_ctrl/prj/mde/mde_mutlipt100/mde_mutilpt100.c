//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//基于ADS1220+4051 的PT100测量模块
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
#include ".\depend\bsp_mutilpt100.h"
#include ".\mde_mutilpt100.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//pt100阻值表，1mr,-50-300 度
static const sdt_int32u pt100_res[] =
{
    80306, 80703, 81100, 81497, 81894, 82290, 82686, 83083, 83479, 83875,   //-50  -41
    84271, 84666, 85062, 85457, 85852, 86248, 86643, 87037, 87432, 87827,   //-40  -31
    88221, 88616, 89010, 89404, 89798, 90192, 90586, 90979, 91373, 91766,   //-30  -21
    92160, 92553, 92946, 93339, 93731, 94124, 94517, 94909, 95301, 95693,   //-20  -11
    96085, 96477, 96869, 97261, 97652, 98044, 98435, 98827, 99218, 99609,   //-10   -1
    100000,100390,100781,101172,101562,101952,102342,102733,103123,103512,  // 0     9
    103902,104292,104681,105071,105460,105849,106238,106627,107016,107405,  //10    19
    107793,108182,108570,108958,109346,109734,110122,110510,110898,111285,  //20    29
    111673,112060,112447,112834,113221,113608,113995,114381,114768,115154,  //30    39
    115541,115927,116313,116699,117085,117470,117856,118241,118627,119012,  //40    49
    119397,119782,120167,120552,120937,121321,121706,122090,122474,122858,  //50    59
    123242,123626,124010,124393,124777,125160,125544,125927,126310,126693,  //60    69
    127076,127458,127841,128223,128606,128988,129370,129752,130134,130516,  //70    79
    130898,131279,131661,132042,132423,132804,133185,133566,133947,134328,  //80    89
    134708,135089,135469,135849,136229,136609,136989,137369,137748,138128,  //90    99
    138507,138886,139265,139644,140023,140402,140781,141159,141538,141916,  //100  109
    142294,142673,143051,143428,143806,144184,144561,144939,145316,145693,  //110  119
    146070,146447,146824,147201,147578,147954,148330,148707,149083,149459,  //120  129
    149835,150211,150586,150962,151337,151713,152088,152463,152838,153213,  //130  139
    153588,153962,154337,154711,155086,155460,155834,156208,156582,156956,  //140  149
    157329,157703,158076,158449,158823,159196,159568,159941,160314,160687,  //150  159
    161059,161431,161804,162176,162548,162920,163291,163663,164035,164406,  //160  169
    164777,165149,165520,165891,166262,166632,167003,167373,167744,168114,  //170  179
    168484,168854,169224,169594,169964,170333,170703,171072,171442,171811,  //180  189
    172180,172549,172917,173286,173655,174023,174391,174760,175128,175496,  //190  199
    175864,176231,176599,176966,177334,177701,178068,178435,178802,179169,  //200  209
    179536,179902,180269,180635,181002,181368,181734,182100,182465,182831,  //210  219
    183197,183562,183928,184293,184658,185023,185388,185752,186117,186482,  //220  229
    186846,187210,187575,187939,188303,188666,189030,189394,189757,190121,  //230  239
    190484,190847,191210,191573,191936,192298,192661,193023,193386,193748,  //240  249
    194110,194472,194834,195196,195557,195919,196280,196642,197003,197364,  //250  259
    197725,198086,198447,198807,199168,199528,199888,200248,200609,200968,  //260  269
    201328,201688,202048,202407,202766,203126,203485,203844,204203,204561,  //270  279
    204920,205279,205637,205995,206354,206712,207070,207427,207785,208143,  //280  289
    208500,208858,209215,209572,209929,210286,210643,211000,211356,211713,  //290  299
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//模拟spi模块
typedef struct 
{
    void(*mpp_push_spi_CS)(sdt_bool in_newState);
    void(*mpp_push_spi_SCLK)(sdt_bool in_newState);
    void(*mpp_push_spi_MOSI)(sdt_bool in_newState);
    sdt_bool(*mpp_pull_spi_MISO)(void);
}sim_spi_oop_def;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取一个字节，从spi总线
//--------------------------------------------------------------------------------------------------------------------------
static sdt_int8u sim_spi_read_one_byte(sim_spi_oop_def* pMix_oop)
{
    sdt_int8u read_byte = 0;
    sdt_int8u mask_bit = 0x80;
    pMix_oop->mpp_push_spi_SCLK(sdt_false);

    while(mask_bit)
    {
        pMix_oop->mpp_push_spi_SCLK(sdt_true);
        if(pMix_oop->mpp_pull_spi_MISO())
        {
            read_byte |= mask_bit;
        }
        pMix_oop->mpp_push_spi_SCLK(sdt_false); 
        mask_bit = mask_bit >> 1;       
    }
    return(read_byte);
}
//--------------------------------------------------------------------------------------------------------------------------
//写入一个字节的数据到spi总线
//--------------------------------------------------------------------------------------------------------------------------
static void sim_spi_write_one_byte(sim_spi_oop_def* pMix_oop,sdt_int8u in_byte)
{
    sdt_int8u mask_bit = 0x80;
    pMix_oop->mpp_push_spi_SCLK(sdt_false);
    while(mask_bit)
    {
        pMix_oop->mpp_push_spi_SCLK(sdt_true);
        if(in_byte & mask_bit)
        {
            pMix_oop->mpp_push_spi_MOSI(sdt_true);
        }
        else
        {
            pMix_oop->mpp_push_spi_MOSI(sdt_false);
        }
        pMix_oop->mpp_push_spi_SCLK(sdt_false); 
        mask_bit = mask_bit >> 1;       
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//写入ads1220寄存器内容
//--------------------------------------------------------------------------------------------------------------------------
static void ads1220_write_register(sim_spi_oop_def* pMix_oop,sdt_int8u in_reg_addr,sdt_int8u in_reg_length,sdt_int8u* pIn_details)
{
    if(((in_reg_addr + in_reg_length) > 4) || (0 == in_reg_length))
    { //illegal
    }
    else
    {
        sdt_int8u command = 0x40;
        sdt_int8u i;
        command |= (in_reg_addr << 2);
        command |= (in_reg_length - 1);
        sim_spi_write_one_byte(pMix_oop,command);
        for(i = 0;i < in_reg_length;i++)
        {
            sim_spi_write_one_byte(pMix_oop,*pIn_details);
            pIn_details++;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取ads1220寄存器内容
//--------------------------------------------------------------------------------------------------------------------------
static void ads1220_read_register(sim_spi_oop_def* pMix_oop,sdt_int8u in_reg_addr,sdt_int8u in_reg_length,sdt_int8u* pOut_details)
{
    if(((in_reg_addr + in_reg_length) > 4) || (0 == in_reg_length))
    { //illegal
    }
    else
    {
        sdt_int8u command = 0x20;
        sdt_int8u i;
        command |= (in_reg_addr << 2);
        command |= (in_reg_length - 1);
        sim_spi_write_one_byte(pMix_oop,command);
        for(i = 0;i < in_reg_length;i++)
        {
            *pOut_details = sim_spi_read_one_byte(pMix_oop);
            pOut_details++;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取adc转换值
//--------------------------------------------------------------------------------------------------------------------------
static sdt_int32u ads1220_read_adc_value(sim_spi_oop_def* pMix_oop)
{
    sdt_int8u rd_adc[3] = {0,0,0};
    sdt_int32u adc_value = 0;

    rd_adc[0] = sim_spi_read_one_byte(pMix_oop);
    rd_adc[1] = sim_spi_read_one_byte(pMix_oop);
    rd_adc[2] = sim_spi_read_one_byte(pMix_oop);
    adc_value  = (sdt_int32u)rd_adc[0] << 16;
    adc_value |= (sdt_int32u)rd_adc[1] << 8;
    adc_value |= (sdt_int32u)rd_adc[2];
    return(adc_value);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//状态机
typedef enum
{
    mupts_idle            = 0x00,
    mupts_ref_select,             //测量基准电阻
    mupts_mesRef_str,
    mupts_mesRef_waiteCov,
    mupts_ch0_sll0,
    mupts_ch0_sll0_str,
    mupts_ch0_sll0_watieCov,
    mupts_ch0_sll1,
    mupts_ch0_sll1_str,
    mupts_ch0_sll1_watieCov,
    mupts_ch1_sll0,
    

}mutil_pt100_state_def;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
    sdt_int32u              rd_adc_value[5];
    sdt_int8u               try_count;
    mutil_pt100_state_def   mutil_pt100_state;
    sdt_int32u              ref_adc_value;
    timerClock_def          timer_wayChg;
    sim_spi_oop_def         mmp_spi;
    sdt_bool(*mpp_pull_DRDY)(void);
    void(*mpp_select_way)(sdt_int8u in_new_way);
}mutil_pt100_oop_def;
#define  TIME_CHANGE_MS   10
//--------------------------------------------------------------------------------------------------------------------------
//多通道PT100任务
static void mutil_pt100_oop_task(mutil_pt100_oop_def* pMix_oop)
{
    pbc_timerMillRun_task(&pMix_oop->timer_wayChg);
    switch(pMix_oop->mutil_pt100_state)
    {
        case mupts_idle:
        {
            break;
        }
        case mupts_ref_select:
        {
            pMix_oop->mpp_select_way(7);   //选择通道7
            sdt_int8u reg_0 = 0x25;
            ads1220_write_register(&pMix_oop->mmp_spi,0,1,&reg_0);   //AIN0  AIN3
            pbc_reload_timerClock(&pMix_oop->timer_wayChg,TIME_CHANGE_MS);
            pMix_oop->try_count = 0;
            pMix_oop->mutil_pt100_state = mupts_mesRef_str;
            break;
        }
        case mupts_mesRef_str:
        {
            if(pbc_pull_timerIsCompleted(&pMix_oop->timer_wayChg))
            {
                sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08); //start conversation
                pMix_oop->mutil_pt100_state = mupts_mesRef_waiteCov;
            }
            break;
        }
        case mupts_mesRef_waiteCov:
        {
            if(sdt_false == pMix_oop->mpp_pull_DRDY())  //低电平有效
            {
                pMix_oop->rd_adc_value[pMix_oop->try_count] = ads1220_read_adc_value(&pMix_oop->mmp_spi);
                pMix_oop->try_count ++;
                if(pMix_oop->try_count > 4)
                {
                    pMix_oop->mutil_pt100_state = mupts_ch0_sll0;
                }
                else
                {
                    sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08);  //restart
                }
            }
            break;
        }
        case mupts_ch0_sll0:
        {
            pMix_oop->mpp_select_way(0);   //选择通道7
            sdt_int8u reg_0 = 0x45;
            ads1220_write_register(&pMix_oop->mmp_spi,0,1,&reg_0);   //AIN1  AIN3
            pbc_reload_timerClock(&pMix_oop->timer_wayChg,TIME_CHANGE_MS);
            pMix_oop->try_count = 0;
            pMix_oop->mutil_pt100_state = mupts_ch0_sll0_str;
            break;
        }
        case mupts_ch0_sll0_str:
        {
            if(pbc_pull_timerIsCompleted(&pMix_oop->timer_wayChg))
            {
                sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08); //start conversation
                pMix_oop->mutil_pt100_state = mupts_ch0_sll0_watieCov;
            }
            break;
        }
        case mupts_ch0_sll0_watieCov:
        {
            if(sdt_false == pMix_oop->mpp_pull_DRDY())  //低电平有效
            {
                pMix_oop->rd_adc_value[pMix_oop->try_count] = ads1220_read_adc_value(&pMix_oop->mmp_spi);
                pMix_oop->try_count ++;
                if(pMix_oop->try_count > 4)
                {
                    pMix_oop->mutil_pt100_state = mupts_ch0_sll1;
                }
                else
                {
                    sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08);  //restart
                }
            }
            break;
        }
        case mupts_ch0_sll1:
        {
            sdt_int8u reg_0 = 0x55;
            ads1220_write_register(&pMix_oop->mmp_spi,0,1,&reg_0);   //AIN2  AIN3
            pbc_reload_timerClock(&pMix_oop->timer_wayChg,TIME_CHANGE_MS);
            pMix_oop->try_count = 0;
            pMix_oop->mutil_pt100_state = mupts_ch0_sll1_str;
            break;
        }
        case mupts_ch0_sll1_str:
        {
            if(pbc_pull_timerIsCompleted(&pMix_oop->timer_wayChg))
            {
                sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08); //start conversation
                pMix_oop->mutil_pt100_state = mupts_ch0_sll1_watieCov;
            }
            break;
        }
        case mupts_ch0_sll1_watieCov:
        {
            if(sdt_false == pMix_oop->mpp_pull_DRDY())  //低电平有效
            {
                pMix_oop->rd_adc_value[pMix_oop->try_count] = ads1220_read_adc_value(&pMix_oop->mmp_spi);
                pMix_oop->try_count ++;
                if(pMix_oop->try_count > 4)
                {
                    pMix_oop->mutil_pt100_state = mupts_ch1_sll0;
                }
                else
                {
                    sim_spi_write_one_byte(&pMix_oop->mmp_spi,0x08);  //restart
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int8u rd_cfg[4];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//配置ADS1220
static void ads1220_cfg(mutil_pt100_oop_def* pMix_oop)
{
    static sdt_int8u ads1220_reg_cfg[4];

    ads1220_reg_cfg[0] = 0x25;  //AIN0,AIN3,GIAN = 4
    ads1220_reg_cfg[1] = 0x60;  //175sps
    ads1220_reg_cfg[2] = 0x26;
    ads1220_reg_cfg[3] = 0xc0;
    ads1220_write_register(&pMix_oop->mmp_spi,0x00,0x04,&ads1220_reg_cfg[0]);


    ads1220_read_register(&pMix_oop->mmp_spi,0x00,0x04,&rd_cfg[0]);
    if((ads1220_reg_cfg[0] == rd_cfg[0]) && (ads1220_reg_cfg[1] == rd_cfg[1]) &&\
       (ads1220_reg_cfg[2] == rd_cfg[2]) && (ads1220_reg_cfg[3] == rd_cfg[3]))
    {

    }
    else
    {//error

    }
}
//+++++++++++++++++++++++++++++++solid++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define max_solid    1
//--------------------------------------------------------------------------------------------------------------------------
static mutil_pt100_oop_def mutil_pt100_solid[max_solid];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void mutil_pt100_solid_cfg(void)
{
    bsp_mutilpt100_cfg();
//--------------------------------------------------------------------------------------------------------------------------
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_CS = bsp_push_ads1220_CS;
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_SCLK = bsp_push_ads1220_SCLK;
    mutil_pt100_solid[0].mmp_spi.mpp_push_spi_MOSI = bsp_push_ads1220_MOSI;
    mutil_pt100_solid[0].mmp_spi.mpp_pull_spi_MISO = bsp_pull_ads1220_MISO;
    mutil_pt100_solid[0].mpp_pull_DRDY = bsp_pull_ads1220_DRDY;
    mutil_pt100_solid[0].mpp_select_way = bsp_push_select_4051;
    bsp_push_select_4051(7);
    ads1220_cfg(&mutil_pt100_solid[0]);
//---------------------------------------------------------------------------------------------------------------------------
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:mRtu任务
//--------------------------------------------------------------------------------------------------------------------------
void mde_mutil_pt100_task(void)
{
    static sdt_bool cfged = sdt_false;

    if(cfged)
    {
        sdt_int8u i;
        for(i = 0;i < max_solid;i ++)
        {
            mutil_pt100_oop_task(&mutil_pt100_solid[i]);
        }
    }
    else
    {
        cfged = sdt_true;
        mutil_pt100_solid_cfg();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_push_start_conver(sdt_int8u in_solidNum)
{
    mutil_pt100_solid[in_solidNum].mutil_pt100_state = mupts_ref_select;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++