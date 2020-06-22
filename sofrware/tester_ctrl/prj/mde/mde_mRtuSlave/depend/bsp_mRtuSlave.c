//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
#include ".\snail_macro.h"
#include ".\snail_data_types.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart4_queue_rxd,64);
macro_creat_queueBasce(uart4_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void UART4_IRQHandler(void)
{
    if((SET==USART_GetFlagStatus(UART4,USART_FLAG_ORE))||\
       (SET==USART_GetFlagStatus(UART4,USART_FLAG_NE))||\
       (SET==USART_GetFlagStatus(UART4,USART_FLAG_FE)))
    {
        USART_GetFlagStatus(UART4,USART_FLAG_ORE);
        USART_ReceiveData(UART4);
    }
    else if(SET==USART_GetFlagStatus(UART4,USART_FLAG_PE))
    {
        USART_GetFlagStatus(UART4,USART_FLAG_PE);
        USART_ReceiveData(UART4);
    }
    else if(SET==USART_GetFlagStatus(UART4,USART_FLAG_RXNE))
    {
        sdt_int8u Read_reg;
        Read_reg = USART_ReceiveData(UART4);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart4_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart4_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart4_queue_rxd,n_bytes,Read_reg);
        }
    }
    if(SET==USART_GetITStatus(UART4,USART_IT_TXE))
    {
        if(SET==USART_GetFlagStatus(UART4,USART_FLAG_TXE))
        {
            sdt_int8u n_bytes,rd_byte_details;
            macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
            if(n_bytes)
            {
                macro_pull_queueBasce_data(uart4_queue_txd,n_bytes,rd_byte_details);
                USART_SendData(UART4,rd_byte_details);
            }
            else
            {
                USART_ITConfig(UART4,USART_IT_TXE,DISABLE);
            }
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart4_cfg(void)
{
    GPIO_InitTypeDef    GPIO_USART4INIT; 
    USART_InitTypeDef   USART4_INIT;
    NVIC_InitTypeDef    USART4_NVIC_INIT;

 //-----------------------------------------------------------------------------   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);  //开启串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //开启GPIOC口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOC口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
//-----------------------------------------------------------------------------  
    GPIO_USART4INIT.GPIO_Pin=GPIO_Pin_10;                   //PC10 U4_TXD
    GPIO_USART4INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART4INIT.GPIO_Mode=GPIO_Mode_AF_PP;            //输出复用推挽
    GPIO_Init(GPIOC,&GPIO_USART4INIT);
//-----------------------------------------------------------------------------     
    GPIO_USART4INIT.GPIO_Pin=GPIO_Pin_11;                  //PC11 U4_RXD
    GPIO_USART4INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART4INIT.GPIO_Mode=GPIO_Mode_IPU;               //输入上拉
    GPIO_Init(GPIOC,&GPIO_USART4INIT);
//-----------------------------------------------------------------------------  
    GPIO_USART4INIT.GPIO_Pin=GPIO_Pin_15;                   //PA15 TRSEL
    GPIO_USART4INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART4INIT.GPIO_Mode=GPIO_Mode_Out_PP;            //推挽输出
    GPIO_Init(GPIOA,&GPIO_USART4INIT);
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
//-----------------------------------------------------------------------------   
    USART_DeInit(UART4);
    USART4_INIT.USART_BaudRate=9600;
    USART4_INIT.USART_Parity=USART_Parity_No;
    USART4_INIT.USART_WordLength=USART_WordLength_8b;    

    USART4_INIT.USART_StopBits=USART_StopBits_1;
    USART4_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART4_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(UART4,&USART4_INIT);
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_Cmd(UART4,ENABLE);
//-----------------------------------------------------------------------------
    USART4_NVIC_INIT.NVIC_IRQChannel=UART4_IRQn;
    USART4_NVIC_INIT.NVIC_IRQChannelPreemptionPriority=0;  //主优先级
    USART4_NVIC_INIT.NVIC_IRQChannelSubPriority=0;         //子优先级
    USART4_NVIC_INIT.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&USART4_NVIC_INIT);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;              //TIM3 3.5T的时序管理
   // NVIC_InitTypeDef NVIC_InitStructure;                         //
//----------------------------------------------------------------------------- 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
//-----------------------------------------------------------------------------
    TIM_DeInit(TIM3);
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler =(72*2)-1;                    //72M 500k ,2us
    TIM_TimeBaseStructure.TIM_Period =0xffff  ;                      // 当定时器从0计数到999，即为1000次，为一个定时周期,1个unit 2us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//-----------------------------------------------------------------------------
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
    //NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;       
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    //NVIC_Init(&NVIC_InitStructure);  
//-----------------------------------------------------------------------------
    //TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    //TIM_ClearFlag(TIM3,TIM_FLAG_Update);               //清除溢出中断标志  
    //TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  
    TIM_Cmd(TIM3,ENABLE);                              //开启时钟  
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取一个字节的接收数据
//out: sdt_true 获取成功，sdt_falas 获取失败
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_oneByte_uart4_rxd(sdt_int8u* out_byte_details)
{
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart4_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart4_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        *out_byte_details = rd_byte_details;
        return(sdt_true);
    }
    else
    {
        
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:压入一个字节的数据到发送队列
//out: sdt_true 压入成功，sdt_false 压入失败
//-----------------------------------------------------------------------------
sdt_bool bsp_push_oneByte_uart4_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart4_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart4_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        USART_ITConfig(UART4,USART_IT_TXE,ENABLE);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int16u test[32];
sdt_int8u test_idx = 0;
sdt_bool bsp_uart4_busFree(sdt_int8u t_char_dis)
{
    static sdt_int16u rd_rxd_depart_cnt;
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = TIM3->CNT;
    free_cnt = rd_cnt;

    if(free_cnt > 1820)  //9600 3.5T 1040*3.25/2
    {
        test[test_idx] = free_cnt;
        test_idx ++;
        if(test_idx > 31)
        {
            test_idx = 0;
        }
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_restart_tim3(void)
{
   TIM3->CNT = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart4_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(UART4,USART_IT_TXE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart4_into_receive(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart4_into_transmit(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    static sdt_int32u bak_sys_fre = 0,bak_baud_rate = 0;
    static sdt_int8u bak_parity = 0,bak_stop_bits = 0;
    USART_InitTypeDef   USART4_INIT;

   // if()

    USART_DeInit(UART4);
    USART4_INIT.USART_BaudRate=9600;
    USART4_INIT.USART_Parity=USART_Parity_No;
    USART4_INIT.USART_WordLength=USART_WordLength_8b;    

    USART4_INIT.USART_StopBits=USART_StopBits_1;
    USART4_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART4_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(UART4,&USART4_INIT);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void get_queue_data(sdt_int8u* out_inx,sdt_int8u* out_otx,sdt_int8u* out_nbyte)
{
    __disable_interrupt();
    *out_inx = uart4_queue_rxd_in_idx;
    *out_otx = uart4_queue_rxd_out_idx;
    *out_nbyte = uart4_queue_rxd_bytes;
    __enable_interrupt();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++