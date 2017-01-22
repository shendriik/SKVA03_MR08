 /*************************************************
 *    Firmware for SKVA-03 MR08
 *    Shendrik Andrey
 *    andrey@findthis.ru 
 *    2016 (c)
 * 
 *************************************************/    
                              

                  
/* -------------------------- Own includes ------------------------------------*/
#include "defines_my.h" 


/* Getting address from the board jumpers */
UCHAR Get_Address()
{
    UCHAR adr=GET_ADDRESS();
    UCHAR ret=0; 
    UCHAR i=0;
    for(i=0;i<4;i++)
    {   
        if(!adr) break;        
        if(adr&0x01) 
        {
            ret=i+1;
            break;
        } 
        adr=adr>>1;
    }
    
    if (!ret) ret=1;
    return ret;
}