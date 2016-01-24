/*------------------------------------------------
Configure PCA in PWM Mode.
Mode0 - Stop
Mode1 - 8-bit fixed frequency PWM
Mode2 - 8-bit variant frequency PWM
Mode3 - 16-bit fixed frequency PWM
------------------------------------------------*/

#include "upsd3300.h"


#define TCM_MODE_STOP_ALL       0x00
#define TCM_MODE_CAPTURE_PE     0x20
#define TCM_MODE_CAPTURE_NE     0x10
#define TCM_MODE_MATCH          0x08
#define TCM_MODE_TOGGLE         0x04
#define TCM_MODE_EINTF          0x80

// Select PCA Counter 0
#define CCONx                   CCON3
#define PCACONx                 PCACON1
#define PCACLx                  PCACL1
#define PCACHx                  PCACH1
#define PWMFx                   PWMF1

// Select TCM0
#define TCMMODEx                TCMMODE5
#define CAPCOMHx                CAPCOMH5
#define CAPCOMLx                CAPCOML5


#define PWM_MODE1_DUTY_CYCLE    0x01        // 0x80 out of 0x100, negative width
#define PWM_MODE2_DUTY_CYCLE    0x07        // 0x40 of 0x100
#define PWM_MODE2_FREQ_RATIO    0x06        // 0x80 of 0x100
#define PWM_MODE3_DUTY_CYCLE    0x0000      // 0x8000 out of 0x10000

/*
void Timer0_Mode2_Init()
// Mode2 - 8-bit autoload
// freq = Fosc/12/(256-TH0)
{
    //1. Set timer operating mode: Timer, mode2
    TMOD=0x02;
    //2. Set TH0, value for auto-reloading.
    TH0=0xff;
    //3. Start Timer0
    TCON|=0x10;
}
*/
void PWM_Mode1_Init(unsigned char channel, unsigned char duty_cycle)
{
    switch(channel)
    {
    case 0:
        P4SFS0|=0x01;
        P4SFS1&=0xFE;
        PCACL0=PCACH0=0x00;
        CCON2=0x10;
        PCACON0=0x00;
        TCMMODE0=0x41;      //CAPCOML0=CAPCOMH0=duty_cycle;
        CAPCOMH0=duty_cycle;
        PCACON0|=0x40;
    break;
    case 1:

    break;
    }
}
/*
void PWM_Mode2_Init()
{
    // ------------- Mode 2 ---------------
    {
    //0.1 Configure pins as PCA function
    P4SFS0=0xff;
    P4SFS1=0;
    //0.2 initialize PCA0 counter
    PCACLx=PCACHx=0;
    //1.1 set PCA0CLK frequency - {prescalar, Enable}
    CCONx=0x10;
    //1.2 select PCA0CLK as PCA0 clock source
    //2. Configure PCA0 Counter - {Idle mode}
    PCACONx=0x00;
    //3. Set duty for TCM0
    PWMFx=PWM_MODE2_FREQ_RATIO;
    CAPCOMLx=CAPCOMHx=PWM_MODE2_DUTY_CYCLE;
    //4. Set TCM0 operating mode
    TCMMODEx=0x42;
    //5. Start PCA0 counter
    PCACONx|=0x40;
    }
}

void PWM_Mode3_Init(unsigned char channel, unsigned int duty_cycle)
{
    switch(channel)
    {
    case 0:
        P4SFS0|=0x01;
        P4SFS1&=0xFE;
        PCACL0=PCACH0=0x00;
        CCON2=0x10;
        PCACON0=0x00;
        CAPCOML0=duty_cycle&0x00ff; // write to CAPCOMLx and pause counter.
        CAPCOMH0=duty_cycle>>8;     // write to CAPCOMLx and resume counter.
        TCMMODE0=0x43;
        PCACON0|=0x40;
    break;
    case 1:

    break;
    }
}

void PWM_Synchronize()
{
    // ------------- Mode 1 ---------------

    //0.1 Configure pins as PCA function
    P4SFS0=0xff;
    P4SFS1=0;

    {//configure PCA0
    //0.2 initialize PCA0 counter
    PCACL0=PCACH0=0x00;
    //1.1 set PCA0CLK frequency
    CCON2=0x10;
    //1.2 select PCA0CLK as PCA0 clock source
    //2. Configure PCA0 Counter operating Mode
    PCACON0=0x00;
    //3. Set TCM0 operationg mode
    TCMMODE0=0x41;
    //4. Set duty for TCM0
    CAPCOML0=CAPCOMH0=PWM_MODE1_DUTY_CYCLE;
    }

    {//configure PCA1
    //0.2 initialize PCA1 counter
    PCACL1=PCACH1=PWM_MODE1_DUTY_CYCLE;
    //1.1 set PCA0CLK frequency
    CCON3=0x10;
    //1.2 select PCA0CLK as PCA0 clock source
    //2. Configure PCA0 Counter operating mode
    PCACON1=0x00;
    //3. Set TCM0 operationg mode
    TCMMODE3=0x41;
    //4. Set duty for TCM0
    CAPCOML3=CAPCOMH3=PWM_MODE1_DUTY_CYCLE;
    }
    //5. Start both PCA simutaniously.
    PCACON0|=0x80;

}
*/
void PwmInit_Mode1(unsigned char PwmDuty_Mode1)
{
    // ----------- Mode 1 --------------
    {
    //0.1 Configure pins as PCA function
    P4SFS0=0xff;
    P4SFS1=0;
    //0.2 initialize PCA0 counter
    PCACL0=PCACH0=0;

    //1.1 set PCA0CLK frequency
    CCON0=0x10;
    //1.2 select PCA0CLK as PCA0 clock source
    //2. Configure PCA0 Counter operating mode
    PCACON0=0x00;
    //3. Set TCM0 operationg mode
    TCMMODE0=0x41;
    //4. Set duty for TCM0
    CAPCOML0=CAPCOMH0=PwmDuty_Mode1;
    //5. Start PCA0 counter
    PCACON0|=0x40;
    }
}




void PwmSetDuty_Mode1(unsigned char PwmDuty_Mode1)
{
    CAPCOMH0=PwmDuty_Mode1;
}

