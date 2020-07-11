//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//-----------------------------------------------------------------------------
#include "stm32f10x.h"
#include "..\mde_storage32bits.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//最后两个page 用于各种运行参数的存储
//0x0803 F000 --0x0803 F7FF     2K      1  page
//0x0803 F800 --0x0803 FFFF     2K      1  page
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FIRST_ADDR    0x0803F000
#define SECOND_ADDR   0x0803F800
//-----------------------------------------------------------------------------
sdt_int32u bsp_passage_flash_memory_read(block_def in_block,sdt_int32u in_offset)
{
    sdt_int32u* read_pFm;
    
    if(block_first == in_block)
    {
        read_pFm =(sdt_int32u*)(FIRST_ADDR+(in_offset*4));
    }
    else if(block_second == in_block)
    {
        read_pFm =(sdt_int32u*)(SECOND_ADDR+(in_offset*4));
    }
    else
    {
        read_pFm =(sdt_int32u*)FIRST_ADDR;
    }
    return(*read_pFm);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_passage_flash_memory_write(block_def in_block,sdt_int32u in_offset,sdt_int32u in_data)
{
    sdt_int32u write_f_addr;
    if(block_first == in_block)
    {
        write_f_addr =(FIRST_ADDR+(in_offset*4));
    }
    else if(block_second == in_block)
    {
        write_f_addr =(SECOND_ADDR+(in_offset*4));
    }
    else
    {
        write_f_addr =FIRST_ADDR;
    }
    
    if(0 == in_offset)
    {
        FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        
        volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
        FLASHStatus = FLASH_ErasePage(write_f_addr);
        if(FLASHStatus == FLASH_COMPLETE)
        {
        }
        else
        {
            return;
        }
    }
    
    volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
    FLASHStatus = FLASH_ProgramWord(write_f_addr,in_data);
    if(FLASHStatus == FLASH_COMPLETE)
    {
    }
    else
    {
        return;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_passage_flash_write_complete(void)
{
    FLASH_Lock();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++