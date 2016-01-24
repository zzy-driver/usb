/*--------------------------------------------------------------------------
TLregs.H

Header file for STM 3200 MicroPSD (uPSD) microcontroller.
06/2002 Ver 0.1 - Initial Version
08/2002 Ver 0.2 - Added Interrupt Vectors & Misc values

Copyright (c) 2002 ST Microelectronics
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
--------------------------------------------------------------------------*/

#ifndef _TLREGS_H_
#define _TLREGS_H_

#include "PSDregs.h"

// Common Misc. Defines...
#ifndef TRUE
  #define TRUE 0x01
#endif 
#ifndef FALSE
  #define FALSE 0x00
#endif 
#ifndef ON
  #define ON 0x01
#endif 
#ifndef OFF
  #define OFF 0x00
#endif 
#ifndef NULL
  #define NULL 0x00
#endif 

/* ------------------------------ */
/*      Processor Registers		  */
/* ------------------------------ */

sfr PSW   = 0xD0;		// Program Status Word
			sbit CY    = PSW^7;	// Carry
			sbit AC    = PSW^6;	// 
			sbit F0    = PSW^5;
			sbit RS1   = PSW^4;
			sbit RS0   = PSW^3;
			sbit OV    = PSW^2;	// Overflow
			sbit P     = PSW^0; 	// 
sfr ACC   = 0xE0;		// Accumulator
sfr B     = 0xF0;		// Register B
sfr SP    = 0x81;		// Stack Pointer
sfr DPL   = 0x82;		// Data Pointer low byte
sfr DPH   = 0x83;		// Data Pointer high byt

/*	DPTR Control	*/
sfr DPTC	= 0x85;	// XData Ptr Control
			//sbit AT		= DPTC^6;
			//sbit DPSEL2	= DPTC^2;
			//sbit DPSEL1	= DPTC^1;
			//sbit DPSEL0	= DPTC^0;
sfr	DPTM	= 0x86;	// XData Ptr Mode
			//sbit MD11	= DPTM^3;
			//sbit MD10	= DPTM^2;
			//sbit MD01	= DPTM^1;
			//sbit MD00	= DPTM^0;

/* ------------------------------ */
/*      Debug Unit				  */
/* ------------------------------ */
sfr	DIR		= 0x9E;
sfr	DVR		= 0x9F;
sfr DSTAT	= 0xCF;

/* ------------------------------ */
/*      	Power Management      */
/* ------------------------------ */
sfr	PCON	= 0x87;
			//sbit SMOD	= PCON^7;		// Baud Rate Double for USART when using TIMER1 as baud rate generator
			//sbit SMOD2= PCON^6;		// Baud Rate Double for USART2 when using TIMER1 as baud rate generator
			//sbit LVD	= PCON^5;		// Low voltage Reset enable
			//sbit POR	= PCON^4;		// 
			//sbit PD   = PCON^1;		// Power Down Mode
			//sbit IDLE = PCON^0;		// Idle Mode

/* ------------------------------ */
/*      	IO Ports			  */
/* ------------------------------ */
/*	port 1	*/
sfr	P1		= 0x90;
			sbit P1_7   = P1^7;	// bit 7 of P1
			sbit P1_6   = P1^6;	// bit 6 of P1
			sbit P1_5   = P1^5;	// bit 5 of P1
			sbit P1_4   = P1^4;	// bit 4 of P1
			sbit P1_3   = P1^3;	// bit 3 of P1
			sbit P1_2   = P1^2;	// bit 2 of P1
			sbit P1_1   = P1^1;	// bit 1 of P1
			sbit P1_0   = P1^0;	// bit 0 of P1

			sbit ADC7  = P1^7;	// ADC Input 3
			sbit ADC6  = P1^6;	// ADC Input 2
			sbit ADC5  = P1^5;	// ADC Input 1
			sbit ADC4  = P1^4;	// ADC Input 0
			sbit ADC3  = P1^3;	// ADC Input 3
			sbit ADC2  = P1^2;	// ADC Input 2
			sbit ADC1  = P1^1;	// ADC Input 1
			sbit ADC0  = P1^0;	// ADC Input 0

			sbit SPISSEL	= P1^7;	// SPI Slave Select
			sbit SPITXD		= P1^6;	// SPI TxD
			sbit SPIRXD 	= P1^5;	// SPI RxD
			sbit SPISCLK	= P1^4;	// SPI SCLK
			sbit TXD2 	 	= P1^3;	// USART2
			sbit RXD2  		= P1^2;	// USART2
			sbit T2EX  		= P1^1; // Timer2 Triger
			sbit T2    		= P1^0; // Timer2 Input

sfr	P1SFS0	= 0x8E;						// Port1 Selection Register 0
			// P1SFS0[7:0];
sfr	P1SFS1	= 0x8F;						// Port1 Selection Register 1
			// P1SFS1[7:0];

/*	port 3	*/
sfr	P3		= 0xB0;
			sbit P3_7   = P3^7;	// bit 7 of P3
			sbit P3_6   = P3^6;	// bit 6 of P3
			sbit P3_5   = P3^5;	// bit 5 of P3
			sbit P3_4   = P3^4;	// bit 4 of P3
			sbit P3_3   = P3^3;	// bit 3 of P3
			sbit P3_2   = P3^2;	// bit 2 of P3
			sbit P3_1   = P3^1;	// bit 1 of P3
			sbit P3_0   = P3^0;	// bit 0 of P3

			sbit I2CSCL = P3^7;	// I2C Serial Clock
			sbit I2CSDA = P3^6;	// I2C Serial Data
			sbit T1    = P3^5;	// Timer 1 Input
			sbit T0    = P3^4;	// Timer 0 Input
			sbit INT1  = P3^3;	// Ext Int 1 / Timer 1 Gate	
			sbit INT0  = P3^2;	// Ext Int 0 / Timer 0 Gate
			sbit TXD   = P3^1;	// USART0
			sbit RXD   = P3^0;	// USART0

sfr	P3SFS	= 0x91;						// Port3 Selection Register
			//sbit P3S7   = P3SFS^7;	// I2C Clock
			//sbit P3S6   = P3SFS^6;	// I2C Data

/*	port 4	*/
sfr	P4		= 0xC0;
			sbit P4_7   = P4^7;	// bit 7 of P4
			sbit P4_6   = P4^6;	// bit 6 of P4
			sbit P4_5   = P4^5;	// bit 5 of P4
			sbit P4_4   = P4^4;	// bit 4 of P4
			sbit P4_3   = P4^3;	// bit 3 of P4
			sbit P4_2   = P4^2;	// bit 2 of P4
			sbit P4_1   = P4^1;	// bit 1 of P4
			sbit P4_0   = P4^0;	// bit 0 of P4

			sbit PCA1CLK= P4^7;	// PCA1 External Clock
			sbit TCM5   = P4^6;	// PWM3
			sbit TCM4   = P4^5;	// PMW2
			sbit TCM3   = P4^4;	// PMW1
			sbit PCA0CLK= P4^3;	// PCA0 External Clock
			sbit TCM2   = P4^2;	// DDC Vsync input
			sbit TCM1   = P4^1;	// DDC SCL
			sbit TCM0   = P4^0;	// DDC SDA

			//sbit SPISSEL	= P4^7;	// SPI Slave Select
			//sbit SPITXD	= P4^6;	// SPI TxD
			//sbit SPIRXD 	= P4^5;	// SPI RxD
			//sbit SPISCLK	= P4^4;	// SPI SCLK
			//sbit TXD2 	= P4^3;	// USART2
			//sbit RXD2  	= P4^2;	// USART2
			//sbit T2EX  	= P4^1; // Timer2 Triger
			//sbit T2    	= P4^0; // Timer2 Input

sfr	P4SFS0	= 0x92;						// Port4 Select Register 0
			//sbit P4S7   = P4SFS0^7;	// PWM4 (variable PWM) 
			//sbit P4S6   = P4SFS0^6;	// PWM3
			//sbit P4S5   = P4SFS0^5;	// PMW2
			//sbit P4S4   = P4SFS0^4;	// PMW1
			//sbit P4S3   = P4SFS0^3;	// PMW0 (8-bit)
			//sbit P4S2   = P4SFS0^2;	// DDC Vsync input
			//sbit P4S1   = P4SFS0^1;	// DDC SCL
			//sbit P4S0   = P4SFS0^0;	// DDC SDA

sfr	P4SFS1	= 0x93;						// Port4 Select Register 1
			// P4SFS[7:0];
			
/* ------------------------------ */
/*      		ADC			      */
/* ------------------------------ */
sfr ADCPS	= 0x94;
			//sbit ADCCE	=CCON4^3;
			//sbit ADCPS2	=CCON4^2;
			//sbit ADCPS1	=CCON4^1;
			//sbit ADCPS0	=CCON4^0;
sfr	ADAT0	= 0x95;						// ADC Data Register 0
			//sbit ADAT7	= ADTA^7;
			//sbit ADAT6	= ADTA^6;
			//sbit ADAT5	= ADTA^5;
			//sbit ADAT4 	= ADTA^4;
			//sbit ADAT3	= ADTA^3;
			//sbit ADAT2	= ADTA^2;
			//sbit ADAT1	= ADTA^1;
			//sbit ADAT0	= ADTA^0;
sfr	ADAT1	= 0x96;						// ADC Data Register 1
			//sbit ADAT9	= ADTA2^1;
			//sbit ADAT8	= ADTA2^0;
sfr	ACON=0x97;
			//sbit AINTF	= ACON^7;
			//sbit AINTEN	= ACON^6;
			//sbit ADEN		= ACON^5;
			//sbit ADS2		= ACON^4;
			//sbit ADS1		= ACON^3;
			//sbit ADS0		= ACON^2;
			//sbit ADST		= ACON^1;
			//sbit ADSF		= ACON^0;

/* ------------------------------ */
/*      	Bus Interface	      */
/* ------------------------------ */
sfr	BUSCON=0x9D;
			//sbit EPFQ	= BUSCON^7;
			//sbit EBC	= BUSCON^6;
			//sbit WRW1	= BUSCON^5;
			//sbit WRW0	= BUSCON^4;
			//sbit RDW1	= BUSCON^3;
			//sbit RDW0	= BUSCON^2;
			//sbit CW1	= BUSCON^1;
			//sbit CW0	= BUSCON^0;

/* ------------------------------ */
/*      	PCA				      */
/* ------------------------------ */
sfr	PCACL0	= 0XA2;
sfr	PCACH0	= 0xA3;
sfr	PCACON0	= 0xA4;
			//sbit EN_ALL	= PCACON0^7;
			//sbit EN_PCA	= PCACON0^6;
			//sbit EOVF1	= PCACON0^5;
			//sbit PCA_IDLE	= PCACON0^4;
			//sbit CLKSEL1	= PCACON0^1;
			//sbit CLKSEL0	= PCACON0^0;

sfr	PCACL1	= 0xBA;
sfr	PCACH1	= 0xBB;
sfr	PCACON1	= 0xBC;
			//sbit EN_PCA1	= PCACON1^6;
			//sbit EOVF11	= PCACON1^5;
			//sbit PCA_IDLE1= PCACON1^4;
			//sbit CLKSEL11	= PCACON1^1;
			//sbit CLKSEL01	= PCACON1^0;

sfr	PCASTA	= 0xA5;
			//sbit OVF1		= PCASTA^7;
			//sbit INTF5	= PCASTA^6;
			//sbit INTF4	= PCASTA^5;
			//sbit INTF3	= PCASTA^4;
			//sbit OVF0		= PCASTA^3;
			//sbit INTF2	= PCASTA^2;
			//sbit INTF1	= PCASTA^1;
			//sbit INTF0	= PCASTA^0;
sfr	PWMF0	= 0xB4;
sfr PWMF1	= 0xC7;

sfr	TCMMODE0	= 0xa9;
			//sbit EINTF0	= TCMMODE0^7;
			//sbit E_COMP0	= TCMMODE0^6;
			//sbit CAP_PE0	= TCMMODE0^5;
			//sbit CAP_NE0	= TCMMODE0^4;
			//sbit MATCH0	= TCMMODE0^3;
			//sbit TOGGLE0	= TCMMODE0^2;
			//sbit PWM10	= TCMMODE0^1;
			//sbit PWM00	= TCMMODE0^0;

sfr	TCMMODE1	= 0xAA;
			//sbit EINTF1	= TCMMODE1^7;
			//sbit E_COMP1	= TCMMODE1^6;
			//sbit CAP_PE1	= TCMMODE1^5;
			//sbit CAP_NE1	= TCMMODE1^4;
			//sbit MATCH1	= TCMMODE1^3;
			//sbit TOGGLE1	= TCMMODE1^2;
			//sbit PWM11	= TCMMODE1^1;
			//sbit PWM01	= TCMMODE1^0;

sfr	TCMMODE2	= 0xAB;
			//sbit EINTF2	= TCMMODE2^7;
			//sbit E_COMP2	= TCMMODE2^6;
			//sbit CAP_PE2	= TCMMODE2^5;
			//sbit CAP_NE2	= TCMMODE2^4;
			//sbit MATCH2	= TCMMODE2^3;
			//sbit TOGGLE2	= TCMMODE2^2;
			//sbit PWM12	= TCMMODE2^1;
			//sbit PWM02	= TCMMODE2^0;

sfr	TCMMODE3	= 0xBD;
sfr	TCMMODE4	= 0xBE;
sfr	TCMMODE5	= 0xBF;

sfr	CAPCOML0	= 0xAC;
sfr	CAPCOMH0	= 0xAD;
sfr CMPCOML1	= 0xAF;
sfr	CMPCOMH1	= 0xB1;
sfr	CMPCOML2	= 0xB2;
sfr	CMPCOMH2	= 0xB3;
sfr	CAPCOML3	= 0xC1;
sfr	CAPCOMH3	= 0xC2;
sfr	CAPCOML4	= 0xC3;
sfr	CAPCOMH4	= 0xC4;
sfr	CAPCOML5	= 0xC5;
sfr	CAPCOMH5	= 0xC6;


/* ------------------------------ */
/*      	WatchDog		      */
/* ------------------------------ */
sfr WDTRST   = 0xA6;		// Watch Dog Reset
sfr WDTKEY   = 0xAE;		// Watch Dog Key Enable

/* ------------------------------ */
/*      	Interrupt		      */
/* ------------------------------ */

sfr IE	= 0xA8;		// Interrupt Enable (main)
			sbit EA    = IE^7;	// Enable All interrupts
			sbit ET2   = IE^5; 	// Timer 2
			sbit ES    = IE^4;	// Usart 0	
			sbit ET1   = IE^3;	// Timer 1
			sbit EX1   = IE^2;	// External Int1
			sbit ET0   = IE^1;	// Timer 0
			sbit EX0   = IE^0;	// External Int0

sfr IP = 0xB8;			// Interrupt Priority (main)
			sbit PDB   = IP^6;	// 
			sbit PT2   = IP^5;	// Timer 2
			sbit PS    = IP^4;	// Usart 0
			sbit PT1   = IP^3;	// Timer 1
			sbit PX1   = IP^2;	// Ext Int1
			sbit PT0   = IP^1;	// Timer 0
			sbit PX0   = IP^0;	// Ext Int 0

sfr IEA	= 0xA7;			// Interrupt Enable (2nd)
			//sbit ADC	= IEA^7;
			//sbit SPI	= IEA^6;
			//sbit PCA	= IEA^5;
			//sbit ES2	= IEA^4;
			//sbit EI2C	= IEA^1;

sfr IPA	= 0xB7;			// Interrupt Priority (2nd)
			//sbit PADC	= IPA^7;
			//sbit PSPI = IPA^6;
			//sbit PPCA	= IPA^5;
			//sbit PS2	= IPA^4;
			//sbit PI2C	= IPA^1;

/* ------------------------------ */
/*      	SPI SFRs		      */
/* ------------------------------ */

sfr SPITDR=0xD4;
sfr SPIRDR=0xD5;
sfr	SPICON0=0xD6;
			/*  SPICON0  */
			//sbit TE		=SPICON0^6;
			//sbit RE		=SPICON0^5;
			//sbit SPIEN	=SPICON0^4;
			//sbit SSEL		=SPICON0^3;
			//sbit FLSB		=SPICON0^2;
			//sbit SPO		=SPICON0^1;
sfr SPICON1=0xD7;
			/*  SPICON1  */
			//sbit TEIE		=SPICON1^3;
			//sbit RORIE	=SPICON1^2;
			//sbit TIE		=SPICON1^1;
			//sbit RIE		=SPICON1^0;
sfr SPICLKD=0xD2;
			/*  SPICLKD  */
			//sbit SPICLKD5	=SPICLKD^5;
			//sbit SPICLKD4	=SPICLKD^4;
			//sbit SPICLKD3	=SPICLKD^3;
			//sbit SPICLKD2	=SPICLKD^2;
			//sbit SPICLKD1	=SPICLKD^1;
			//sbit SPICLKD0 =SPICLKD^0;
sfr SPISTAT=0xD3;
			/*  SPISTAT  */
			//sbit BUSY		=SPISTAT^4;
			//sbit TEISF	=SPISTAT^3;
			//sbit RORISF	=SPISTAT^2;
			//sbit TISF		=SPISTAT^1;
			//sbit RISF		=SPISTAT^0;
		
		
/* ------------------------------ */
/*      	Clock SFRs		      */
/* ------------------------------ */
sfr CCON0=0xF9;		//Debugger, CPU Clock Control
	/*  CCON0  */
	//sbit DBGCE	=CCON0^4;
	//sbit CPU_AR	=CCON0^3;
	//sbit CPUPS2	=CCON0^2;
	//sbit CPUPS1	=CCON0^1;
	//sbit CPUPS0	=CCON0^0;
sfr CCON2=0xFB;		//PCA0 Clock Control
	//sbit PCA0CE	=CCON2^4;
	//sbit PCA0PS3	=CCON2^3;
	//sbit PCA0PS2	=CCON2^2;
	//sbit PCA0PS1	=CCON2^1;
	//sbit PCA0PS0	=CCON2^0;
sfr CCON3=0xFC;		//PCA1 Clock Control
	/*  CCON6  */
	//sbit PCA1CE	=CCON3^4;
	//sbit PCA1PS3	=CCON3^3;
	//sbit PCA1PS2	=CCON3^2;
	//sbit PCA1PS1	=CCON3^1;
	//sbit PCA1PS0	=CCON3^0;

/* ------------------------------ */
/*      Turbo Lite Timer SFRs    */
/* ------------------------------ */
/*	Timer0,1 SFRs    */
sfr TCON  = 0x88;		// Timer / Counter Control
			sbit TF1   = TCON^7;	// Standard 8051 timer control
			sbit TR1   = TCON^6;
			sbit TF0   = TCON^5;
			sbit TR0   = TCON^4;
			sbit IE1   = TCON^3;
			sbit IT1   = TCON^2;
			sbit IE0   = TCON^1;
			sbit IT0   = TCON^0;

sfr TMOD  = 0x89;		// Timer / Counter Mode
			//sbit GATE1   = TMOD^7;
			//sbit C_T1   = TMOD^6;
			//sbit M11   = TMOD^5;
			//sbit M10   = TMOD^4;
			//sbit GATE0   = TMOD^3;
			//sbit C_T0   = TMOD^2;
			//sbit M01   = TMOD^1;
			//sbit M00   = TMOD^0;

sfr TL0   = 0x8A;		// Timer 0 low byte
sfr TL1   = 0x8B;		// Timer 1 low byte
sfr TH0   = 0x8C;		// Timer 0 high byte
sfr TH1   = 0x8D;		// Timer 1 high byte

/*	Timer2 SFRs    */
sfr T2CON=0xC8;		// Timer2 Control Register
			sbit TF2    = T2CON^7;	// Timer2 overflow flag.
			sbit EXF2   = T2CON^6;	// External signal flag. Set when negative transition occur on T2EX and EXEN2=1.
			sbit RCLK   = T2CON^5;	// UART receive clock select. 0-Timer1, 1-Timer2
			sbit TCLK   = T2CON^4;	// UART transimit clock select. 0-Timer1, 1-Timer2
			sbit EXEN2  = T2CON^3;	// Timer2 external signal (T2EX) enable.
			sbit TR2    = T2CON^2;	// Start/Stop control
			sbit C_T2   = T2CON^1;	// Timer/Counter select
			sbit CP_RL2 = T2CON^0;	// Capture/Reload select

sfr SCLK1=0xD1;	// Timer2 Control Register 2
			//sbit RCLK2=SCLK1^5;
			//sbit TCLK2=SCLK1^4;

sfr RCAP2L	= 0xCA;	// Timer 2 Reload low byte
sfr RCAP2H	= 0xCB;	// Timer 2 Reload high byte
sfr TL2		= 0xCC;	// Timer 2 low byte
sfr TH2		= 0xCD;	// Timer 2 high byte

/* ------------------------------ */
/*      Turbo Lite IrAD SFRs      */
/* ------------------------------ */
sfr IRDACON=0xCE;
			/*  TRDACON  */
			//sbit IRDAEN	=IRDACON^6;
			//sbit PULSE	=IRDACON^5;
			//sbit CDIV4	=IRDACON^4;
			//sbit CDIV3	=IRDACON^3;
			//sbit CDIV2	=IRDACON^2;
			//sbit CDIV1	=IRDACON^1;
			//sbit CDIV0	=IRDACON^0;


/* ------------------------------ */
/*      Turbo Lite I2C SFRs       */
/* ------------------------------ */

sfr S1SETUP=0xDB;	// I2C Setup Control
			//sbit ENABLE	= S1SETUP^7;
			// S1SETUP[6:0]	= S1SETUP^[6:0];
sfr S1CON= 0xDC;	// I2C Control
			/*  S1CON  */
			//sbit CR2    	= S1CON^7;
			//sbit EN1   	= S1CON^6; 
			//sbit STA   	= S1CON^5; 
			//sbit STO    	= S1CON^4;
			//sbit ADDR   	= S1CON^3;
			//sbit AA   	= S1CON^2;
			//sbit CR1   	= S1CON^1;
			//sbit CR0   	= S1CON^0;	
sfr S1STA= 0xDD;	// I2C S2 Status
			/*  S1STA  */	
			//sbit GC    	= S1STA^7;
			//sbit STOP   	= S1STA^6; 
			//sbit INTR   	= S1STA^5; 
			//sbit TX_MD    = S1STA^4;
			//sbit BBUSY   	= S1STA^3;
			//sbit BLOST   	= S1STA^2;
			//sbit ACK_R   	= S1STA^1;
			//sbit SLV   	= S1STA^0;
sfr S1DAT= 0xDE;	// I2C Data Hold Register
sfr S1ADR= 0xDF;	// I2C Bus Address



/* ------------------------------ */
/*      Turbo Lite UART SFRs     */
/* ------------------------------ */

// UART
sfr SCON  = 0x98;		// UART0 Serial Control
			sbit SM0   = SCON^7;	// Mode define bit0.
			sbit SM1   = SCON^6;	// Mode define bit1.
			sbit SM2   = SCON^5;	// Multiprocessor Enable.
			sbit REN   = SCON^4;	// Receive Enable.
			sbit TB8   = SCON^3;	// Data bit8 that will be transmitted in mode 2 and 3.
			sbit RB8   = SCON^2;	// Data bit8 that was received in mode 2 and 3.
			sbit TI    = SCON^1;	// Transmit interrupt flag.
			sbit RI    = SCON^0;	// Receive interrupt flag.

sfr SBUF  = 0x99;		// UART0 Serial Buffer

// Second UART
sfr SCON1= 0xD8;
			sbit SM01   = SCON1^7;	// Mode define bit0.
			sbit SM11   = SCON1^6;	// Mode define bit1.
			sbit SM21   = SCON1^5;	// Multiprocessor Enable.
			sbit REN1   = SCON1^4;	// Receive Enable.
			sbit TB81   = SCON1^3;	// Data bit8 that will be transmitted in mode 2 and 3.
			sbit RB81   = SCON1^2;	// Data bit8 that was received in mode 2 and 3.
			sbit TI1    = SCON1^1;	// Transmit interrupt flag.
			sbit RI1    = SCON1^0;	// Receive interrupt flag.
sfr SBUF1= 0xD9;

/* -----------------------------------
Interrupt Vectors:
Interrupt Address = (Number * 8) + 3
------------------------------------ */ 
#define RESET_VECTOR_ADDR		0		// Reset Address = 0
#define IE0_VECTOR			0     	//0x03 External Interrupt 0
#define IEO_VECTOR_ADDR         0x03
#define TF0_VECTOR			1		//0x0B Timer 0
#define TF0_VECTOR_ADDR			0x0B
#define IE1_VECTOR			2		//0x13 External Interrupt 1
#define IE1_VECTOR_ADDR			0x13
#define TF1_VECTOR			3		//0x1B Timer 1
#define TF1_VECTOR_ADDR			0x1B
#define SIO_VECTOR			4		//0x23 Serial Port 0
#define SIO_VECTOR_ADDR			0x23
#define TF2_VECTOR			5		//0x2B Timer 2
#define TF2_VECTOR_ADDR			0x2B	
#define ADC_VECTOR			7		//0x3B ADC
#define ADC_VECTOR_ADDR			0x3B
#define I2C_VECTOR			8		//0x43 I2C
#define I2C_VECTOR_ADDR			0x43	
#define SIO1_VECTOR   		9		//0x4B Serial Port 1
#define SIO1_VECTOR_ADDR   		0x4B	
#define SPI_VECTOR			10		//0x53 SPI
#define SPI_VECTOR_ADDR			0x53
#define PCA_VECTOR			11		//0x5B PCA
#define PCA_VECTOR_ADDR			0x5B
#define DBG_VECTOR			12		//0x63 DEBUG (Highest Priority)
#define DBG_VECTOR_ADDR			0x63

/* ---------------------------------- */


#endif
