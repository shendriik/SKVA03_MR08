 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/   
 
/* ------------------------- System includes ----------------------------------*/
#include "string.h"
                                                                    
/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h" 

/* ------------------------- Modbus includes ----------------------------------*/
#include "port.h"

/* using extern variables */
extern modbusSlaveParams modbusParams;
extern ModbusMap mModbusMap;
extern USHORT adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
extern UCHAR Get_Address();


/*using extern functions */
extern UCHAR init_ModbusSlave(UCHAR modbus_id);


/* Second expired callback function */
void SecondExpired()
{  
    UCHAR new_adr;  

    /* Checking address jumpers and initializing the ModbusSlave protocol stack */  
    new_adr=Get_Address();
    if(modbusParams.ID!=new_adr)
    {      
        /* Initialize the ModbusSlave protocol stack, if error wait for WD to reset MCU */
        modbusParams.ID=new_adr;         
        if(!init_ModbusSlave(modbusParams.ID))
        {
            /* Error initialization Modbus: waiting for the WD to reset MCU */ 
            while(1); 
        }
    } 
      
}

/* ADC convertation complete handler */
void ADC_Convertation_complete()
{  
    USHORT mAx100[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
    UCHAR i;                 
    
    /* convert adc to mA x100 and copy it to modbus map */
    for(i=0;i<LAST_ADC_INPUT-FIRST_ADC_INPUT+1;i++)
    {
        *(((USHORT*)(&mModbusMap))+LAST_ADC_INPUT-i)=(USHORT)(ADC_TO_mA((*(adc_data+i)))*100);   
    }

}

