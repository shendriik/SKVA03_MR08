 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/ 
      
#ifndef _DEFINES_MY_
#define _DEFINES_MY_

#include "port.h"


/* identification of the board */
#define DEV_PREAMBULE                   0x05060708

/* ADDRESSES */
#define REG_HOLD_START                  1000
#define REG_HOLD_NREGS                  10

/* RS485 LINK */
#define BAUDRATE                        4800

/* SECOND INTERVAL TIMER */
#define TIM0_CLK                        31250
#define TIM0_OVERCOUNT                  TIM0_CLK/256   


/* ADDRESS JUMPERS specific */
#define ADR0_PIN         5
#define ADR0_DDR         DDRD
#define ADR0_PORT        PORTD
#define ADR0_PINPORT     PIND
/**/
#define ADR1_PIN         6
#define ADR1_DDR         DDRD
#define ADR1_PORT        PORTD
#define ADR1_PINPORT     PIND
/**/
#define ADR2_PIN         7
#define ADR2_DDR         DDRD
#define ADR2_PORT        PORTD
#define ADR2_PINPORT     PIND
/**/
#define ADR3_PIN         0
#define ADR3_DDR         DDRB
#define ADR3_PORT        PORTB
#define ADR3_PINPORT     PINB
/**/
#define ADRESS_IO_INIT        \
    do { \   
        ADR0_DDR &= ~_BV( ADR0_PIN ); \ 
        ADR1_DDR &= ~_BV( ADR1_PIN ); \
        ADR2_DDR &= ~_BV( ADR2_PIN ); \
        ADR3_DDR &= ~_BV( ADR3_PIN ); \
        ADR0_PORT |= _BV( ADR0_PIN ); \ 
        ADR1_PORT |= _BV( ADR1_PIN ); \
        ADR2_PORT |= _BV( ADR2_PIN ); \
        ADR3_PORT |= _BV( ADR3_PIN ); \    
    } while( 0 );

#define GET_BIT(PORT,BIT) \
    ( (PORT &_BV( BIT ))>> BIT ) 
    
#define GET_ADDRESS() \
    ( ~((GET_BIT(ADR3_PINPORT,ADR3_PIN)<<3)|(GET_BIT(ADR2_PINPORT,ADR2_PIN)<<2)|(GET_BIT(ADR1_PINPORT,ADR1_PIN)<<1)|(GET_BIT(ADR0_PINPORT,ADR0_PIN)<<0))&0x0F ) 
                
    
    
/* Modbus stuff */
typedef struct
{
    UCHAR ucSlaveID[3];
    UCHAR isInit;
    UCHAR ID;
} modbusSlaveParams;


/* Modbus map struct */
typedef struct
{
   USHORT           CHAN1mAx100;
   USHORT           CHAN2mAx100;
   USHORT           CHAN3mAx100;
   USHORT           CHAN4mAx100;
   USHORT           CHAN5mAx100;
   USHORT           CHAN6mAx100; 
   USHORT           CHAN7mAx100; 
   USHORT           CHAN8mAx100;  
   ULONG            Preambule; 
} ModbusMap;

/* ADC & convertation*/
#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7
#define ADC_VREF_TYPE 0x40

#define ADC16mA 719

#define ADC_TO_mA(adc) \
    ((float)(adc<<4)/ADC16mA) 
    


#endif