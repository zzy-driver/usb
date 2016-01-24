/*------------------------------------------------------------------------------
Turbo_TIMER.C

uPSD Timer0 Device Driver Functions
06/2002 Ver 0.1 - Initial Version
08/2002 Ver 0.2 - Timer 0 reload calcualted from FREQ_OSC define

Note: Some functions have been commented out so as to remove linker warnings
      for code segments that are not used.


Copyright 2002 STMicroelectrons Inc.

This example demo code is provided as is and has no warranty,
implied or otherwise.  You are free to use/modify any of the provided
code at your own risk in your applications with the expressed limitation
of liability (see below) so long as your product using the code contains
at least one uPSD products (device).

LIMITATION OF LIABILITY:   NEITHER STMicroelectronics NOR ITS VENDORS OR 
AGENTS SHALL BE LIABLE FOR ANY LOSS OF PROFITS, LOSS OF USE, LOSS OF DATA,
INTERRUPTION OF BUSINESS, NOR FOR INDIRECT, SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES OF ANY KIND WHETHER UNDER THIS AGREEMENT OR
OTHERWISE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
------------------------------------------------------------------------------*/

#include "uPSD3300.h"
#include "Turbo_timer.h"
#include "TurboLite_hardware.h"

/*------------------------------------------------------------------------------
              Local Variable Declarations
------------------------------------------------------------------------------*/
static unsigned int idata timer0_tick;
unsigned int timer0_value;

/*------------------------------------------------------------------------------
static void timer0_isr (void);

This function is an interrupt service routine for TIMER 0.  It should never
be called by a C or assembly function.  It will be executed automatically
when TIMER 0 overflows.
------------------------------------------------------------------------------*/
static void timer0_isr (void) interrupt TF0_VECTOR using 1
{
/*------------------------------------------------
Stop timer, adjust the timer 0 counter so that we get another
interrupt in 10ms, and restart the timer.
------------------------------------------------*/
    TR0 = 0;                      // stop timer 0
    TL0 = (timer0_value & 0x00FF);
    TH0 = (timer0_value >> 8);
    TR0 = 1;                      // start timer 0
    timer0_tick++;                // Increment global var timer_tick (number of 10ms ticks)
}

/*------------------------------------------------------------------------------
void timer0_init(void);

This function enables TIMER 0.  TIMER 0 will generate a synchronous interrupt
once every 100Hz.
------------------------------------------------------------------------------*/
void timer0_init (void)
{
    EA = 0;                 /* disable interrupts */
    timer0_tick = 0;
    TR0 = 0;                /* stop timer 0 */
    TMOD &= 0xF0;           /* clear timer 0 mode bits - bottom 4 bits */
    TMOD |= 0x01;           /* put timer 0 into 16-bit no prescale */

    // Calculate timer tollover based on FREQ_OSC to be 10ms periods (100hz)
    timer0_value = 0x10000 - ( ((FREQ_OSC * 5L) / 6L) - 17L);
    TL0 = (timer0_value & 0x00FF);
    TH0 = (timer0_value >> 8);

    PT0 = 1;                /* set high priority for timer 0 */
    ET0 = 1;                /* enable timer 0 interrupt */
    TR0 = 1;                /* start timer 0 */
    EA = 1;                 /* enable interrupts */
}


/*------------------------------------------------------------------------------
unsigned int timer0_count (void);

This function returns the current timer0 tick count.
------------------------------------------------------------------------------*/
unsigned int timer0_count (void)
{
    unsigned int t;

    EA = 0;               // disable ints so we cna read steady value
    t = timer0_tick;
    EA = 1;               // enable
    return(t);
}


/*------------------------------------------------------------------------------
void timer0_delay (
  unsigned count);

This function waits for 'count' timer ticks to pass.
------------------------------------------------------------------------------*/
void timer0_delay (unsigned int count)
{
    unsigned int start_count;

    start_count = timer0_count(); /* get the start count */

    while ((timer0_count() - start_count) <= count)   /* wait for count "ticks" */
    {
    }
}


void delay_10ms()
{
    timer0_delay(1);
}

void delay_1sec(void)
{
    timer0_delay(100);
}
/*
void delay_2sec(void)
{
    delay_1sec();
    delay_1sec();
}

void delay_10sec(void)
{
    delay_2sec();
    delay_2sec();
    delay_2sec();
    delay_2sec();
    delay_2sec();
}

void delay_0_5sec(void)
{
    timer0_delay(50);
}

void delay_0_1sec(void)
{
    timer0_delay(10);
}
*/

