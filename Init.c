 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/ 
 
/* ----------------------- Platform includes --------------------------------*/
#include <mega8.h>

/* ------------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbcrc.h"
#include "port.h" 

/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h"


/* using extern variables */
extern modbusSlaveParams modbusParams;


/* Initialization timer0 for generation seconds intervals */
void init_Timer0()
{

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 31,250 kHz
    TCCR0=0x04;
    TCNT0=0x00;
    TIMSK|=(1<<TOIE0);  
    
}

/* Initialization IO */
void init_IO()
{
    DERE_INIT;                              /* Enable RTS pin out */     
    ADRESS_IO_INIT                          /* Enable jumpers io */
}

/* Initialization ADC */
void init_ADC()
{
    // ADC initialization
    // ADC Clock frequency: 125,000 kHz
    // ADC Voltage Reference: AVCC pin
    ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
    ADCSRA=0xCE;
}

/* Initialization Watchdog timer */
void init_Watchdog()
{

#pragma optsize-
    WDTCR=(1<<WDCE)|(1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0); 
    WDTCR=(1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0); 
#asm("WDR")
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

}

/* Initialization the modbus slave protocol stack */
UCHAR init_ModbusSlave(UCHAR modbus_id)
{    

    /* Modbus Initialization. Enable the Modbus Protocol Stack */
    return   (eMBInit(MB_RTU, modbus_id, 0,BAUDRATE, MB_PAR_EVEN)==MB_ENOERR) && 
             (eMBSetSlaveID( 0x34, TRUE,modbusParams.ucSlaveID, 3 )==MB_ENOERR) && 
             (eMBEnable()==MB_ENOERR);                
}



