 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/     
 
/* ----------------------- Platform includes ----------------------------------*/ 
#include "mega8.h"
#include "delay.h"
#include "string.h"

/* ------------------------- Modbus includes ----------------------------------*/
#include "port.h"

/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h"

/* using extern variables */
extern UCHAR TIMER0_OVER;  
extern BOOL bSecondExpired;
extern USHORT adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
extern BOOL bAdcFinish;


/* using extern functions */
extern void ADC_Convertation_complete(USHORT *data);

/* Timer0 overflow interrupt for generating seconds intervals */
interrupt [TIM0_OVF] void timer0_ovr_isr(void)
{         
    //second has expired
    if(++TIMER0_OVER>=TIM0_OVERCOUNT)
    {      
        /* setting secondExpired flag*/
        bSecondExpired=TRUE;
        
        /* reset the timer0 */ 
        TIMER0_OVER=0; 
        TCNT0=0x00; 
    }               
 } 
 
 
 


/* ADC interrupt service routine with auto input scanning */
interrupt [ADC_INT] void adc_isr(void)
{
    static unsigned char input_index=0;
    /* Read the AD conversion result */
    adc_data[input_index]=ADCW;
    /* Select next ADC input */
    if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))
        {
            input_index=0;   
            /* setting ADC ñonvertation complete flag */
            bAdcFinish=TRUE;
        }
    ADMUX=(FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff))+input_index;
    /* Delay needed for the stabilization of the ADC input voltage */
    delay_us(10);
    /* Start the AD conversion */
    ADCSRA|=0x40;
}
