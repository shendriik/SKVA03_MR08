 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/ 
  
#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h"


/* Number of overflows by TIMER0  */
UCHAR TIMER0_OVER=0;    
 
                            
/* Modbus holding Regs array */
static USHORT usRegHoldingBuf[REG_HOLD_NREGS];    
/* Modbus holding Regs start reg */            
static USHORT   usRegHoldingStart = REG_HOLD_START;   
/* Modbus Params & Flags */
modbusSlaveParams modbusParams = {
                                    0xAA,0xBB,0xCC,       /* SlaveID params */
                                    FALSE,                /* Initialization flag */
                                    0xFF                  /* Slave ID */
                                 }; 
/* Modbus map */
ModbusMap mModbusMap =          {
                                    0x0000,               /* chan1 init value */
                                    0x0000,               /* chan2 init value */
                                    0x0000,               /* chan3 init value */
                                    0x0000,               /* chan4 init value */
                                    0x0000,               /* chan5 init value */
                                    0x0000,               /* chan6 init value */
                                    0x0000,               /* chan7 init value */
                                    0x0000,               /* chan8 init value */
                                    0x3830524d            /* Preambule "MR08" */
                                };

/* second expired flag */       
BOOL bSecondExpired = FALSE;

/* ADC data array */
USHORT adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];

/* second expired flag */       
BOOL bAdcFinish = FALSE;

#endif
