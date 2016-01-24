#include "uPSD3300.h"
#include "TurboLite_hardware.h"
#include "Turbo_timer.h"
#define PollingTime 10000
extern xdata PSD_REGS PSD8xx_reg; 


unsigned char Polling_Encoder()
{
    unsigned char temp;

    temp=PSD8xx_reg.OMC_AB;
    if((temp&0x01)!=0)
    {
        PSD8xx_reg.OMC_AB&=0xFE;
        timer0_delay(1);
        if((PSD8xx_reg.OMC_BC&0x02)!=0)return(1);
        else return(2);
    }
    return(0);
}
