
#include "uPSD3300.h"
#include "TurboLite_hardware.h"
#include "Turbo_timer.h"
extern xdata PSD_REGS PSD8xx_reg; 


unsigned char Key_check()
{
    //PSD8xx_reg.DRIVE_D|=0x06;     // OpenDrain
    PSD8xx_reg.DIRECTION_D|=0x06;   // Out direction
    PSD8xx_reg.DATAOUT_D|=0x06;     // Output "1"
    PSD8xx_reg.DIRECTION_B&=0xF9;   // In direction
    if((PSD8xx_reg.DATAIN_D&0x06)==06)return(0);
    timer0_delay(2);                //delay 20ms
    if((PSD8xx_reg.DATAIN_D&0x06)==06)return(0);
    else
    {
        if((PSD8xx_reg.DATAIN_D&0x06)==02)return(1);
        if((PSD8xx_reg.DATAIN_D&0x06)==04)return(2);
        if((PSD8xx_reg.DATAIN_D&0x06)==06)return(3);
    }
}
