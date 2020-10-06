//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
#include "iostm8l052r8.h"
#include ".\Fifo_Macros.h"
#include "intrinsics.h"
//-------------------------------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
_Creat_my_fifo(Uart_Rxd,16);
_Creat_my_fifo(Uart_Txd,16);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PHY use uart3 PG0--U3RX  PG1--U3TX
//tr_select  PG2
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//input floating
#define macro_trsCfg    //PG_DDR |= (0x04); PG_CR1 &= (~0x04); PG_CR2 &= (~0x04); PG_ODR &= (~0x04)
#define macro_trs_receive   //PG_DDR |= (0x04);
#define macro_trs_transmit  //PG_DDR &= (~0x04);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Recfg_Buadrate_USART3(sdt_int32u ClockFreqValue)
{
    static sdt_int32u ClkFreBakup;
    sdt_int32u DifferentFre;
    sdt_int32u BaudRate_Mantissa;
    
    if(ClkFreBakup>ClockFreqValue)
    {
        DifferentFre=ClkFreBakup-ClockFreqValue;
    }
    else
    {
        DifferentFre=ClockFreqValue-ClkFreBakup;
    }
    if(DifferentFre>8000)
    {
        ClkFreBakup=ClockFreqValue;

        USART3_CR1_bit.USARTD = 1;  //Disable USART3
        BaudRate_Mantissa  = ClockFreqValue/9600;
        /* Set the fraction of USARTDIV */
        USART3_BRR2 = (sdt_int8u)((BaudRate_Mantissa >> (sdt_int8u)8) & (sdt_int8u)0xF0);
        /* Set the MSB mantissa of USARTDIV */
        USART3_BRR2 |= (sdt_int8u)(BaudRate_Mantissa & (sdt_int8u)0x0F);
        /* Set the LSB mantissa of USARTDIV */
        USART3_BRR1 = (sdt_int8u)(BaudRate_Mantissa >> (sdt_int8u)4);  
        USART3_CR1_bit.USARTD = 0; //Enable USART3
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART3口的配置
//PG0--U3RX  PG1--U3TX
//波特率:9600,无校验
//-------------------------------------------------------------------------------------------------
void Uart3_Configure(void)
{
    CLK_PCKENR3_bit.PCKEN34 = 1;
    PG_DDR &= (~0x01); PG_CR1 |= (0x01); PG_CR2 &= (~0x01); PG_ODR &= (~0x01);  //RXD
    PG_DDR |= (0x02);  PG_CR1 |= (0x02); PG_CR2 &= (~0x02); PG_ODR |= (0x02);   //TXD
    macro_trsCfg;
    
    
    USART3_CR1 = 0x00;   //0000 0000 8Data_Bits Parity_None
    USART3_CR2 = 0x0C;   //0000 1100 TEN REN
    USART3_CR3 = 0x00;   //0000 0000 1STOP_Bit
    USART3_CR4 = 0x00;
    USART3_CR5 = 0x00;
    USART3_GTR = 0x00;
    USART3_PSCR = 0x00;
    Recfg_Buadrate_USART3(16000000);
    USART3_CR2_bit.RIEN = 1;  //Receiver interrupt Enable
//-------------------------------------------------------------------------------------------------
    _Init_my_fifo(Uart_Rxd);
    _Init_my_fifo(Uart_Txd);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#pragma vector = USART3_R_RXNE_vector
__interrupt void ISR_Uart3_Rxd(void)
{
    sdt_int8u read_reg;

    if(USART3_SR_bit.PE)  //过滤掉校验错误的数据
    {
        read_reg=USART3_DR;
    }
    else
    {
        read_reg=USART3_DR; 
        _In_my_fifo(Uart_Rxd,read_reg);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************************************
//发送中断
//---------------------------------------------------------
static sdt_bool Txd_Finish;
//---------------------------------------------------------
#pragma vector = USART3_T_TXE_vector//USART3_T_TC_vector
__interrupt void ISR_Uart3_Txd(void)
{
    sdt_int8u read_reg,nbytes;    
    
    if(USART3_CR2_bit.TIEN)
    {
        if(USART3_SR_bit.TXE) 
        {
            _Get_my_fifo_byte(Uart_Txd,nbytes);
            if(nbytes)
            {
                _Out_my_fifo(Uart_Txd,read_reg);
                USART3_DR=read_reg;
            }
            else
            {
                USART3_CR2_bit.TIEN=0;   //禁用发生中断
            }
        }        
    }
    else if(USART3_CR2_bit.TCIEN)
    {
        if(USART3_SR_bit.TC)
        {
            USART3_CR2_bit.TCIEN = 0;  //发送完毕
            Txd_Finish = sdt_true;
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//链路进入接收模式
//-------------------------------------------------------------------------------------------------
void Enter_ReceiveMode_PHY(void)
{
    USART3_CR2_bit.REN = 1;
    USART3_CR2_bit.RIEN = 1;
    macro_trs_receive;
}
//-------------------------------------------------------------------------------------------------
//链路进入发送模式
//-------------------------------------------------------------------------------------------------
void Enter_TransmitMode_PHY(void)
{
    USART3_CR2_bit.REN = 0;
    USART3_CR2_bit.RIEN = 0;
    macro_trs_transmit;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//发送完毕状态获取,sdt_true -- 发送完毕
//-------------------------------------------------------------------------------------------------
sdt_bool Pull_PHYTxd_Finish(void)
{
    sdt_bool Read_Finish;
    
    __disable_interrupt();
    Read_Finish = Txd_Finish;
    Txd_Finish = sdt_false;
    __enable_interrupt();
    return(Read_Finish);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//启动发送硬件
//-------------------------------------------------------------------------------------------------
void Activate_PHYTxd(void)
{
    if(0 == USART3_CR2_bit.TIEN)
    {
        USART3_CR2_bit.TIEN = 1;
        USART3_CR2_bit.TCIEN = 1;        
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool Pull_OneByteFromPHY(sdt_int8u* _Out_Byte)
{
    sdt_int8u Read_Byte,NBytes;
    
    __disable_interrupt();
    _Get_my_fifo_byte(Uart_Rxd,NBytes);
    __enable_interrupt();
    if(NBytes)
    {
        __disable_interrupt();
        _Out_my_fifo(Uart_Rxd,Read_Byte);
        __enable_interrupt();
        
        *_Out_Byte = Read_Byte;
        return(sdt_true);
    }
    return(sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool Pull_TransmitPHY_IsReady(void)
{
    sdt_int8u Fifo_Status;
    
    __disable_interrupt();
    _Get_my_fifo_state(Uart_Txd,Fifo_Status);
    __enable_interrupt();
    if(FIFO_FULL == Fifo_Status)
    {
        return(sdt_false);
    }
    return(sdt_true);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Push_OneByteToPHY(sdt_int8u _In_Byte)
{
    __disable_interrupt();
    _In_my_fifo(Uart_Txd,_In_Byte);
    __enable_interrupt();
    Activate_PHYTxd();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++