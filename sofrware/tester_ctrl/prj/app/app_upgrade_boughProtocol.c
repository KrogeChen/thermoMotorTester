//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//负责Bough Easy Upgrade Protocol的报文处理,任务。
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\APP_Cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BGPTCL_EasyUpagrde         0xD002  //简易固件升级协议
#define BGPTCL_debug               0xDFFF  //
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BGEUCMD_QuerySalveStatus   0x01
#define BGEUCMD_EnterBoot          0x02
#define BGEUCMD_StrUpgrade_map     0x03
#define BGEUCMD_ResumeUpgrade_map  0x04
#define BGEUCMD_TransferFile       0x05

#define BGEUCMD_ErrorReport        0xFE
//-------------------------------------------------------------------------------------------------
#define BGEUERR_NoneError          0x00
#define BGEUERR_Length             0x01
#define BGEUERR_Version            0x02
#define BGEUERR_Command            0x03
#define BGEUERR_FileMapCheckSum    0x04
#define BGEUERR_FileCheckSum       0x05
#define BGEUERR_BlockNumber        0x06
#define BGEUERR_Fireware           0x07
#define BGEUERR_Other              0xFE
//--------------------------------------------------------------------------------------------------
#define BGEUSTS_None               0x00
#define BGEUSTS_NotInBoot          0x01
#define BGEUSTS_Boot               0x10
//#define BGEUSTS_QueryFileMap       0x11
#define BGEUSTS_QueryFile          0x12
#define BGEUSTS_UpgradeFinish      0x1F
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define THE_VER      0x01
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int8u Pull_TheDeviceUpgradeStatus(void);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: Bough 错误应答
//功能: 
//入口: 
//      _Out_pPayload       应答内容,          ---->>
//      _In_ErrCode          错误号            <<----
//出口: 应答的数据长度,
//-------------------------------------------------------------------------------------------------
sdt_int8u Bough_AnswerErrorReport(sdt_int8u* _Out_pPayload,sdt_int8u _In_ErrCode)
{
    _Out_pPayload[0] = THE_VER;              //Version
    _Out_pPayload[1] = BGEUCMD_ErrorReport;  //Command
    _Out_pPayload[2] = BGEUSTS_None;         //Status
    _Out_pPayload[3] = _In_ErrCode;      //Error Code
    return(4);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: Bough 简易升级报文协议处理函数
//功能: 
//入口: 
//      _In_pReceiveData     接收到的数据指针,         <<----
//     _In_TheAddr           本机链路地址              <<----
//      _Out_pTransmitData   应答数据指针,             ---->>
//      _Out_DevEnterBoot    进入Boot,sdt_true --需要进入   ---->>
//出口: 是否有应答数据,sdt_true--有应答数据
//-------------------------------------------------------------------------------------------------
sdt_bool Bough_EasyUpgrade_Protocol(BoughLinkCommData_Def* _In_pReceiveData,sdt_int8u* _In_TheAddr,BoughLinkCommData_Def* _Out_pTransmitData,sdt_bool* _Out_DevEnterBoot)
{         
    *_Out_DevEnterBoot = sdt_false;
    if(((0xFF == _In_pReceiveData->LinkDstAddr[0])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[1])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[2])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[3])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[4])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[5]))||\
       ((_In_TheAddr[0] == _In_pReceiveData->LinkDstAddr[0])&&\
        (_In_TheAddr[1] == _In_pReceiveData->LinkDstAddr[1])&&\
        (_In_TheAddr[2] == _In_pReceiveData->LinkDstAddr[2])&&\
        (_In_TheAddr[3] == _In_pReceiveData->LinkDstAddr[3])&&\
        (_In_TheAddr[4] == _In_pReceiveData->LinkDstAddr[4])&&\
        (_In_TheAddr[5] == _In_pReceiveData->LinkDstAddr[5])))
    {
        _Out_pTransmitData->ProcotolType = BGPTCL_EasyUpagrde;
        _Out_pTransmitData->LinkDstAddr[0] = _In_pReceiveData->LinkSrcAddr[0];
        _Out_pTransmitData->LinkDstAddr[1] = _In_pReceiveData->LinkSrcAddr[1];
        _Out_pTransmitData->LinkDstAddr[2] = _In_pReceiveData->LinkSrcAddr[2];
        _Out_pTransmitData->LinkDstAddr[3] = _In_pReceiveData->LinkSrcAddr[3];
        _Out_pTransmitData->LinkDstAddr[4] = _In_pReceiveData->LinkSrcAddr[4];
        _Out_pTransmitData->LinkDstAddr[5] = _In_pReceiveData->LinkSrcAddr[5];
        
        _Out_pTransmitData->LinkSrcAddr[0] = _In_TheAddr[0];
        _Out_pTransmitData->LinkSrcAddr[1] = _In_TheAddr[1];
        _Out_pTransmitData->LinkSrcAddr[2] = _In_TheAddr[2];
        _Out_pTransmitData->LinkSrcAddr[3] = _In_TheAddr[3];
        _Out_pTransmitData->LinkSrcAddr[4] = _In_TheAddr[4];
        _Out_pTransmitData->LinkSrcAddr[5] = _In_TheAddr[5];
        
        if(0 == _In_pReceiveData->PayloadLength)
        {
            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
        }
        else
        {
            if(THE_VER == _In_pReceiveData->Payload[0])  //Command
            {
                switch(_In_pReceiveData->Payload[1])
                {
                    case BGEUCMD_QuerySalveStatus://Query Boot Status
                    {
                        if(4 == _In_pReceiveData->PayloadLength)
                        {
                            _Out_pTransmitData->Payload[0] = THE_VER;                           //Version
                            _Out_pTransmitData->Payload[1] = (BGEUCMD_QuerySalveStatus | 0x80); //Command
                            _Out_pTransmitData->Payload[2] = Pull_TheDeviceUpgradeStatus();     //Status
                            _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                 //Error Code
                            _Out_pTransmitData->PayloadLength = 4;                               
                        }
                        else
                        {
                            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_EnterBoot:
                    {
                        if(4 == _In_pReceiveData->PayloadLength)
                        {
                            _Out_pTransmitData->Payload[0] = THE_VER;                           //Version
                            _Out_pTransmitData->Payload[1] = (BGEUCMD_EnterBoot | 0x80);        //Command
                            _Out_pTransmitData->Payload[2] = Pull_TheDeviceUpgradeStatus();     //Status
                            _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                 //Error Code
                            _Out_pTransmitData->PayloadLength = 4;                          
                        }
                        else
                        {
                            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
                        }
                        
                        *_Out_DevEnterBoot = sdt_true;                                         //Device Enter Boot Status 
                        break;
                    }
                    case BGEUCMD_StrUpgrade_map://重传命令
                    {
                        
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u err;
                            err = mde_push_fileMap(&_In_pReceiveData->Payload[6],sdt_false);
                            if(err)
                            {
                                Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],err);
                            }
                            else
                            {
                                _Out_pTransmitData->Payload[0] = THE_VER;                                //Version
                                _Out_pTransmitData->Payload[1] = (BGEUCMD_StrUpgrade_map | 0x80);  //Command
                                _Out_pTransmitData->Payload[2] = BGEUSTS_QueryFile;                   //Status,请求FileMap
                                _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                                     //Error Code
                                
                                sdt_int16u next_block_number;
                                mde_pull_upgrade_next_block(&next_block_number);
                                pbc_int16uToArray_bigEndian(next_block_number,&_Out_pTransmitData->Payload[4]);
                                _Out_pTransmitData->PayloadLength = 6;                                   
                            }
                        }
                        else
                        {
                            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_ResumeUpgrade_map://续传命令
                    {
                      
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u err;
                            err = mde_push_fileMap(&_In_pReceiveData->Payload[6],sdt_true);
                            if(err)
                            {
                                Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],err);
                            }
                            else
                            {
                                _Out_pTransmitData->Payload[0] = THE_VER;                              //Version
                                _Out_pTransmitData->Payload[1] = (BGEUCMD_ResumeUpgrade_map | 0x80);        //Command
                                _Out_pTransmitData->Payload[2] = BGEUSTS_QueryFile;                  //Status,请求FileMap
                                _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                    //Error Code
                                
                                sdt_int16u next_block_number;
                                mde_pull_upgrade_next_block(&next_block_number);
                                pbc_int16uToArray_bigEndian(next_block_number,&_Out_pTransmitData->Payload[4]);
                                _Out_pTransmitData->PayloadLength = 6;                                     
                            }
                        }
                        else
                        {
                            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_TransferFile://接收到File内容
                    {
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u ErrorCode = BGEUERR_NoneError;

                            ErrorCode = mde_push_files_one_block(pbc_arrayToInt16u_bigEndian(&_In_pReceiveData->Payload[4]),&_In_pReceiveData->Payload[6]);  //处理接收报文
                            
                            sdt_bool completed;
                            sdt_int16u next_block_number;
                            
                            completed = mde_pull_upgrade_next_block(&next_block_number);
                            if(ErrorCode)
                            {
                                _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],ErrorCode);
                            }
                            else if(completed)
                            {
                                _Out_pTransmitData->Payload[0] = THE_VER;                              //Version
                                _Out_pTransmitData->Payload[1] = (BGEUCMD_TransferFile | 0x80);         //Command
                                _Out_pTransmitData->Payload[2] = BGEUSTS_UpgradeFinish;                 //Status,UpgradeFinish
                                _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                     //Error Code
                                _Out_pTransmitData->Payload[4] = 0;
                                _Out_pTransmitData->Payload[5] = 0;
                                _Out_pTransmitData->PayloadLength = 6;   
                            }
                            else
                            {
                                _Out_pTransmitData->Payload[0] = THE_VER;                           //Version
                                _Out_pTransmitData->Payload[1] = (BGEUCMD_TransferFile | 0x80);     //Command
                                _Out_pTransmitData->Payload[2] = BGEUSTS_QueryFile;                 //Status,请求File
                                _Out_pTransmitData->Payload[3] = BGEUERR_NoneError;                 //Error Is not
                                pbc_int16uToArray_bigEndian(next_block_number,&_Out_pTransmitData->Payload[4]);
                                _Out_pTransmitData->PayloadLength = 6;    
                            }
                        }
                        else
                        {
                            _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Length);
                        }
                        break;
                    }
                    default:
                    {
                        _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUCMD_ErrorReport);
                        break;
                    }
                }
            }
            else
            {
                _Out_pTransmitData->PayloadLength = Bough_AnswerErrorReport(&_Out_pTransmitData->Payload[0],BGEUERR_Version);
            }          
        }
        return(sdt_true);
    }
    return(sdt_false);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//升级接收文件状态

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: 获取设备是否运行在Boot状态
//功能: 
//入口: 
//      
//出口: sdt_true--Boot状态
//-------------------------------------------------------------------------------------------------
sdt_int8u Pull_TheDeviceUpgradeStatus(void)
{
    sdt_int8u TheUdeStatus = BGEUSTS_Boot;
    /*
    switch(UPL_RevFileStatus)
    {
        case UPL_Idle:
        {
            break;
        }
        case UPL_RevFileMap:
        {
            TheUdeStatus = BGEUSTS_QueryFileMap;
            break;
        }
        case UPL_RevFileData:
        {
            TheUdeStatus = BGEUSTS_QueryFile;
            break;
        }
        case UPL_RevFinish:
        {
            TheUdeStatus = BGEUSTS_UpgradeFinish;
            break;
        }
        default:
        {
            break;
        }
    }*/
    return(TheUdeStatus);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//重传处理
//-------------------------------------------------------------------------------------------------
void RestartUpgrade_Process(void)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//续传处理
//-------------------------------------------------------------------------------------------------
void ResumeUpgrade_Process(void)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void APP_BoughUpgradeProtocol_Task(void)
{
//-------------------------------------------------------------------------------------------------
    BoughLinkCommData_Def*  pReceiveData;
    sdt_bool ReceiveOneMessage;
    sdt_int8u local_addr[6]={0x00,0x04,0xA3,0x00,0x00,0x02};

    Mde_Local_BoughLink_Task();
    mde_upgrade_files_task();
    pReceiveData = Pull_Local_MessageFromBoughLink(&ReceiveOneMessage);
    if(ReceiveOneMessage)
    { 
        switch(pReceiveData->ProcotolType)
        {
            case BGPTCL_EasyUpagrde:
            {     
                BoughLinkCommData_Def   TransmitData;
                sdt_bool Enter_Boot;
                
                if(Bough_EasyUpgrade_Protocol(pReceiveData,&local_addr[0],&TransmitData,&Enter_Boot))
                {
                    if(Pull_Local_TransmitIsReady())
                    {
                        Push_Local_TransmitMessageToBoughLink(&TransmitData);
                    }
                }
                break;
            }
            case BGPTCL_debug:
            {
                BoughLinkCommData_Def   TransmitData;
                
                TransmitData.ProcotolType = BGPTCL_debug;
                TransmitData.LinkDstAddr[0] = pReceiveData->LinkSrcAddr[0];
                TransmitData.LinkDstAddr[1] = pReceiveData->LinkSrcAddr[1];
                TransmitData.LinkDstAddr[2] = pReceiveData->LinkSrcAddr[2];
                TransmitData.LinkDstAddr[3] = pReceiveData->LinkSrcAddr[3];
                TransmitData.LinkDstAddr[4] = pReceiveData->LinkSrcAddr[4];
                TransmitData.LinkDstAddr[5] = pReceiveData->LinkSrcAddr[5];
        
                TransmitData.LinkSrcAddr[0] = local_addr[0];
                TransmitData.LinkSrcAddr[1] = local_addr[1];
                TransmitData.LinkSrcAddr[2] = local_addr[2];
                TransmitData.LinkSrcAddr[3] = local_addr[3];
                TransmitData.LinkSrcAddr[4] = local_addr[4];
                TransmitData.LinkSrcAddr[5] = local_addr[5];
        
                TransmitData.Payload[0] = 0x00;   
                TransmitData.Payload[1] = 0x03;    
                TransmitData.Payload[2] = 0x00;//app_pull_distance_mm() >> 8;
                TransmitData.Payload[3] = 0x00;//app_pull_distance_mm();
                TransmitData.PayloadLength = 4;   
                if(Pull_Local_TransmitIsReady())
                {
                    Push_Local_TransmitMessageToBoughLink(&TransmitData);
                }

            }
            default:
            {
                break;
            }
        }
    }
//-------------------------------------------------------------------------------------------------
  
//-------------------------------------------------------------------------------------------------

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++