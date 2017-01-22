 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 * 
 *    Chip type               : ATmega8
 *    Program type            : Application
 *    AVR Core Clock frequency: 11,059200 MHz
 *    Memory model            : Small
 *    External RAM size       : 0
 *    Data Stack size         : 256
 *************************************************/
                
/* ------------------------- System includes ----------------------------------*/
#include "string.h"

/* ----------------------- Platform includes ----------------------------------*/ 
#include "mega8.h"

/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h"
#include "global_var.h"

/* ------------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbcrc.h"
#include "port.h"


/*using extern functions */
extern void SecondExpired();
extern void ADC_Convertation_complete();
extern UCHAR Get_Address();

/**/
extern void init_IO();
extern void init_Timer0();
extern void init_ADC();
extern void init_Watchdog();
extern UCHAR init_ModbusSlave(UCHAR modbus_id);




void main(void)
{

    
    /* Initialization MCU perefiry */  
    init_IO();
    init_Timer0();
    init_ADC();     
    init_Watchdog();                            
    #asm("sei")
    
    /* Modbuds Regs initialization */    
    //memcpy(usRegHoldingBuf,&Modbus_Map,sizeof(Modbus_Map));                                   
    
    
    /* Initialize the ModbusSlave protocol stack, if error wait for WD to reset MCU */
    modbusParams.ID=Get_Address();
    if(!init_ModbusSlave(modbusParams.ID)) { while(1);}
    

    while(1)
    {                 
    
        /* Running Modbus Protocol Stack,  reset WD if no error */
        if(eMBPoll()==MB_ENOERR){ #asm("WDR")} 
          
        
        /* calling SecondExpired handler */
        if(bSecondExpired)
        {              
            SecondExpired(); 
            bSecondExpired=FALSE;      
        }
        
        /* calling adc conv complete handler */                              
        if(bAdcFinish)
        {              
            ADC_Convertation_complete(); 
            bAdcFinish=FALSE;      
        }  
        
        /* Updating modbus registers by values in modbus map */
        memcpy(usRegHoldingBuf,&mModbusMap,sizeof(ModbusMap));      
    }    
        
}




eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    return MB_ENOREG;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
    
    if( ( usAddress >= REG_HOLD_START ) &&
        ( usAddress + usNRegs <= REG_HOLD_START + REG_HOLD_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldingStart );

        switch ( eMode )
        {
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
                *pucRegBuffer++ = ( UCHAR ) ( usRegHoldingBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( UCHAR ) ( usRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;
        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
                usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
    








