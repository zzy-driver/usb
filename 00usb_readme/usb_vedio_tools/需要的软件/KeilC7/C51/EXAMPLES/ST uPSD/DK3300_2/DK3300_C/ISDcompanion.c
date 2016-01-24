#include "upsd3300.h"
#include "TurboLite_hardware.h"

extern xdata PSD_REGS PSD8xx_reg;
/*
void InitUart0()	//Init UART0 for ISD51
{
	unsigned int timer2_baud;

	// ISD51 makes use of Uart1 or Uart2 based on header file & object file used

	//1.2 #define Timer2_Set_BaudRate(BaudRate)
    timer2_baud = (65536L - ( (FREQ_OSC * 125L) / (4L * 19200L)));
    RCAP2L = (timer2_baud & 0x00FF);
	RCAP2H = (timer2_baud >> 8);

	//1.3 Configure Timer2: Mode-Timer, Interrupt-No, Start
	//1.1 Select UART0 Baud Generator: TCLK-Timer2, RCLK-Timer2
	T2CON   = 0x34;		//Set and start Timer2.
						//sbit TF2    = T2CON^7;	// Timer2 overflow flag.
						//sbit EXF2   = T2CON^6;	// External signal flag. Set when negative transition occur on T2EX and EXEN2=1.
						//sbit RCLK   = T2CON^5;	// UART0 receive clock select. 0-Timer1, 1-Timer2
						//sbit TCLK   = T2CON^4;	// UART0 transimit clock select. 0-Timer1, 1-Timer2
						//sbit EXEN2  = T2CON^3;	// Timer2 external signal (T2EX) enable.
						//sbit TR2    = T2CON^2;	// Start/Stop control
						//sbit C_T2   = T2CON^1;	// Timer/Counter select
						//sbit CP_RL2 = T2CON^0;	// Capture/Reload select

	//2. Configure P3.0,P3.1 as UART0 pins
	P3SFS|=0x03;

	//3. Set UART0 operating mode
    SCON = 0x50;      // enable first serial UART & receiver 

	//4. Configure MCU Interrupt support
	EA = 1;             // Enable global interrupt flag       
}*/
