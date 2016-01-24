/*--------------------------------------------------------------------------
uPSD3300.H

Header file for STM 3300 Turbo MicroPSD (uPSD) microcontroller.
03/2003 Ver 0.1 - Initial Version

Copyright (c) 2003 ST Microelectronics
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

/*--------------------------------------------------------------------------
Revise:
1. SCON1 is bit addressable.
2. delete suffix '1' in SCON0 bit signals.
2. Interrupt number is not interrupt priority.
--------------------------------------------------------------------------*/


#ifndef _UPSD_H_
#define _UPSD_H_


typedef struct	// general structure of 8 bit register allowing bit access 
	{
	unsigned char bit0 : 1;
	unsigned char bit1 : 1;
	unsigned char bit2 : 1;
	unsigned char bit3 : 1;
	unsigned char bit4 : 1;
 	unsigned char bit5 : 1;
	unsigned char bit6 : 1;
	unsigned char bit7 : 1;
	} Register;    

typedef union	// allow bit or byte access to registers 
	{
	char byte;
	Register bits;
	} xdata Mix_Reg;

typedef union	// allow bit or byte access to registers 
	{
	char byte;
	Register bits;
	} SFR_Reg;


/* ------------------------------ */
/*      Standard PSD Registers    */
/* ------------------------------ */

typedef xdata struct REG_PSD_struct {
        unsigned char DATAIN_A;         // PSD_REG_BASE +0x00
        unsigned char DATAIN_B;         //              +0x01
        unsigned char CONTROL_A;        //              +0x02
        unsigned char CONTROL_B;        //              +0x03
        unsigned char DATAOUT_A;        //              +0x04
        unsigned char DATAOUT_B;        //              +0x05
        unsigned char DIRECTION_A;      //              +0x06
        unsigned char DIRECTION_B;      //              +0x07
        unsigned char DRIVE_A;          //              +0x08
        unsigned char DRIVE_B;          //              +0x09
        unsigned char IMC_A;            //              +0x0A
        unsigned char IMC_B;            //              +0x0B
        unsigned char OUTENABLE_A;      //              +0x0C
        unsigned char OUTENABLE_B;      //              +0x0D
        unsigned char res2[2];          //      spacer
        unsigned char DATAIN_C;         //              +0x10
        unsigned char DATAIN_D;         //              +0x11
        unsigned char DATAOUT_C;        //              +0x12 
        unsigned char DATAOUT_D;        //              +0x13
        unsigned char DIRECTION_C;      //              +0x14
        unsigned char DIRECTION_D;      //              +0x15
        unsigned char DRIVE_C;          //              +0x16
        unsigned char DRIVE_D;          //              +0x17
        unsigned char IMC_C;            //              +0x18
        unsigned char res1a;            //      spacer
        unsigned char OUTENABLE_C;      //              +0x1A
        unsigned char OUTENABLE_D;      //              +0x1B
        unsigned char res4[4];          //      spacer
        unsigned char OMC_AB;           //              +0x20
        unsigned char OMC_BC;           //              +0x21
        unsigned char OMCMASK_AB;       //              +0x22
        unsigned char OMCMASK_BC;       //              +0x23
        unsigned char res8c[0x8C];      //      spacer
        unsigned char PMMR0;            //              +0xB0
        unsigned char res1b;            //      spacer
        unsigned char PMMR1;            //              +0xB2
        unsigned char res1c;            //      spacer
        unsigned char PMMR2;            //              +0xB4
        unsigned char res0B[0x0B];      //      spacer
        unsigned char MAINPROTECT;      //              +0xC0
        unsigned char res1d;            //      spacer
        unsigned char ALTPROTECT;       //              +0xC2
        unsigned char res4a[4];         //      spacer
        unsigned char JTAG;             //              +0xC7
        unsigned char res18[0x18];      //      spacer
        unsigned char PAGE;             //              +0xE0
        unsigned char res1e;            //      spacer
        unsigned char VM;               //              +0xE2
	  unsigned char res29[0x1d];	    //    	spacer
} PSD_REGS;




//****************** PSD control register bit definitions *********

//PSD PORTA
#define PA0		bit0
#define PA1		bit1	
#define PA2		bit2	
#define PA3		bit3	
#define PA4		bit4	
#define PA5		bit5	
#define PA6		bit6	
#define PA7		bit7	

//PSD PORTB
#define PB0		bit0
#define PB1		bit1	
#define PB2		bit2	
#define PB3		bit3	
#define PB4		bit4	
#define PB5		bit5	
#define PB6		bit6	
#define PB7		bit7	

//PSD PORTC
#define PC0		bit0
#define PC1		bit1	
#define PC2		bit2	
#define PC3		bit3	
#define PC4		bit4	
#define PC5		bit5	
#define PC6		bit6	
#define PC7		bit7	

//PSD PORTD
#define PD0		bit0
#define PD1		bit1	
#define PD2		bit2	

//PSD JTAG
#define JEN		bit0   // JTAG enable

//PSD PMMR0
#define APD_ENABLE	    bit1
#define PLD_TURBO		bit3
#define PLD_ARRAY_CLK	bit4
#define PLD_MCELL_CLK	bit5

//PSD PMMR2
#define PLD_CNTL0		bit2
#define PLD_CNTL1		bit3
#define PLD_CNTL2		bit4
#define PLD_ALE		    bit5
#define PLD_DBE		    bit6

//PSD VM
#define SRAM_CODE		bit0
#define EE_CODE		    bit1
#define FL_CODE		    bit2
#define EE_DATA		    bit3
#define FL_DATA		    bit4
#define PIO_EN		    bit7


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
/* Standard 8051 MCU Registers    */
/* ------------------------------ */
// sfr P0       = 0x80;	// Port 0 - Always used for External Memory Access (no access)
sfr P1        = 0x90;	// Port 1
// sfr P2       = 0xA0;	// Port 2 - Always used for External Memory Access (no access)
sfr P3        = 0xB0;  	// Port 3
sfr PSW       = 0xD0;  	// Program Status Word
sfr ACC       = 0xE0;  	// Accumulator
sfr B         = 0xF0;  	// Register B
sfr SP        = 0x81;  	// Stack Pointer
sfr DPL       = 0x82;  	// Data Pointer low byte
sfr DPH       = 0x83;  	// Data Pointer high byt
sfr PCON      = 0x87;  	// MCU Power Control Register
sfr TCON      = 0x88;  	// Timer / Counter Control
sfr TMOD      = 0x89;  	// Timer / Counter Mode
sfr TL0       = 0x8A;  	// Timer 0 low byte
sfr TL1       = 0x8B;  	// Timer 1 low byte
sfr TH0       = 0x8C;  	// Timer 0 high byte
sfr TH1       = 0x8D;  	// Timer 1 high byte
sfr IE        = 0xA8;  	// Interrupt Enable (main)
sfr IP        = 0xB8;  	// Interrupt Priority (main) 
sfr SCON     = 0x98;  	// UART0 Serial Control
sfr SBUF     = 0x99;  	// UART0 Serial Buffer
sfr BUSCON   = 0x9D;    // Bus Control Register

/* ------------------------ */
/*  Common 8052 Extensions  */
/* ------------------------ */
sfr T2CON     = 0xC8;	// Timer 2 Control
sfr RCAP2L    = 0xCA;	// Timer 2 Reload low byte
sfr RCAP2H    = 0xCB;	// Timer 2 Reload high byte
sfr TL2       = 0xCC;	// Timer 2 low byte
sfr TH2       = 0xCD;	// Timer 2 high byte

/* ------------------------ */
/*  UPSD 3300 Extensions    */
/* ------------------------ */
sfr P4        = 0xC0;	// New port 4
sfr P1SFS0    = 0x8E;	// Port 1 I/O select Register 0
sfr P1SFS1    = 0x8F;	// Port 1 I/O select Register 1
sfr P3SFS     = 0x91;	// Port 3 I/O select
sfr P4SFS0    = 0x92;	// Port 4 I/O select Register 0
sfr P4SFS1    = 0x93;	// Port 4 I/O select Register 1

// --- ADC SFRs ---
sfr ADCPS    = 0x94;	// ADC Clock Control Register
sfr ADAT0    = 0x95;	// ADC Data Register1 ADAT[9:8]
sfr ADAT1    = 0x96;	// ADC Data Register0 ADAT[7:0]
sfr ACON     = 0x97;	// ADC Control Register

// --- UART1 SFRS ----
sfr SCLK1    = 0xD1;	// UART1 Serial Clock
sfr SCON1    = 0xD8;	// UART1 Serial Control
sfr SBUF1    = 0xD9;	// UART1 Serial Buffer

// --- PCA SFRs ------
sfr PCACL0   = 0xA2;	// PCA0 Counter Low
sfr PCACH0   = 0xA3;	// PCA0 Counter High
sfr PCACON0  = 0xA4;	// PCA0 Configuration Register
sfr PCASTA   = 0xA5;	// PCA0, PCA1 Status Register
sfr PCACL1   = 0xBA;	// PCA1 Counter Low
sfr PCACH1   = 0xBB;	// PCA1 Counter High
sfr PCACON1  = 0xBC;	// PCA1 Configuration Register 
sfr PWMF0    = 0xB4;    // PCA0 PWM Frequency
sfr PWMF1    = 0xC7;    // PCA1 PWM Frequency


// ---TCM SFRs -------
sfr TCMMODE0  = 0xA9;   // TCM0 Mode Register   
sfr TCMMODE1  = 0xAA;   // TCM1 Mode Register   
sfr TCMMODE2  = 0xAB;   // TCM2 Mode Register
sfr TCMMODE3  = 0xBD;   // TCM3 Mode Register
sfr TCMMODE4  = 0xBE;   // TCM4 Mode Register
sfr TCMMODE5  = 0xBF;   // TCM5 Mode Register
sfr CAPCOML0  = 0xAC;   // TCM0 Capture/Compare Register Low  
sfr CAPCOMH0  = 0xAD;   // TCM0 Capture/Compare Register High  
sfr CAPCOML1  = 0xAF;   // TCM1 Capture/Compare Register Low  
sfr CAPCOMH1  = 0xB1;   // TCM1 Capture/Compare Register High  
sfr CAPCOML2  = 0xB2;   // TCM2 Capture/Compare Register Low  
sfr CAPCOMH2  = 0xB3;   // TCM2 Capture/Compare Register High 
sfr CAPCOML3  = 0xC1;   // TCM3 Capture/Compare Register Low  
sfr CAPCOMH3  = 0xC2;   // TCM3 Capture/Compare Register High 
sfr CAPCOML4  = 0xC3;   // TCM4 Capture/Compare Register Low  
sfr CAPCOMH4  = 0xC4;   // TCM4 Capture/Compare Register High 
sfr CAPCOML5  = 0xC5;   // TCM5 Capture/Compare Register Low  
sfr CAPCOMH5  = 0xC6;   // TCM5 Capture/Compare Register High 
 

// --- WDT SFRs ---
sfr WDRST    = 0xA6;    // Watch Dog Reset
sfr WDKEY    = 0xAE;    // Watch Dog Key Enable

// --- INTERRUPT 2 SFRs ---
sfr IEA      = 0xA7;   	// Interrupt Enable (2nd)
sfr IPA      = 0xB7;    // Interrupt Priority (2nd)

// --- I2C SFRs ---
sfr S1SETUP  = 0XDB;    // I2C S1 Setup
sfr S1CON    = 0xDC;	// I2C Bus Control Register
sfr S1STA    = 0xDD;	// I2C Bus Status
sfr S1DAT    = 0xDE;	// I2C Data Hold Register
sfr S1ADR    = 0xDF;    // I2C Bus Address

// --- SPI SFRs ----
sfr SPICLKD  = 0XD2;    // SPI Clock Divisor
sfr SPISTAT  = 0XD3;    // SPI Status Reg.
sfr SPITDR   = 0xD4;    // SPI Transmit Reg.
sfr SPIRDR   = 0xD5;    // SPI Receive Reg.
sfr SPICON0  = 0xD6;    // SPI Control0 Reg.
sfr SPICON1  = 0xD7;    // SPI Control1 Reg.

// --- IrDA SFRs ----
sfr IRDACON  = 0xCE;    // IrDA Configuration Register

// --- MCU Debug ---
sfr DSTAT    = 0xCF;    // Debug MCU Status
sfr DIR      = 0x9E;    // Debug Index Register
sfr DVR      = 0x9F;    // Debug Value Register


// --- Clock Control SFRs ----
sfr CCON0    = 0xF9;    // PLL, Debugber, CPU Clock Control
sfr CCON1    = 0xFA;    // PLL Divider Input
sfr CCON2    = 0xFB;    // PCA0 Clock Control
sfr CCON3    = 0xFC;    // PCA1 Clock Control


// --- XDATA Pointer SFRs ----
sfr DPTC     = 0x85;    // XData Pointer Control
sfr DPTM     = 0x86;    // XData Pointer Mode

// --- Program Counter -----
sfr PCL      = 0x9A;    // Program Counter Low 
sfr PCH      = 0x9B;    // Program Counter High 

// --- Temporary SFRs -----
sfr TSFR0    = 0XB5;    // Temporary SFR0
sfr TSFR1    = 0XB6;    // Temporary SFR1

/* --------------------------- */
/*  Common 8051 BIT Registers  */
/* --------------------------- */
/*  PSW  */
sbit CY    = PSW^7;	    // Carry
sbit AC    = PSW^6;	    // 
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;	    // Overflow
sbit P     = PSW^0; 	// 

/*  SCON  */
sbit SM0   = SCON^7;	// Standard 8051 Uart Control
sbit SM1   = SCON^6;
sbit SM2   = SCON^5;
sbit REN   = SCON^4;
sbit TB8   = SCON^3;
sbit RB8   = SCON^2;
sbit TI    = SCON^1;
sbit RI    = SCON^0;

/*  TCON  */
sbit TF1   = TCON^7;	// Standard 8051 timer control
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

/*  IE  */
sbit EA    = IE^7;  	// Enable All interrupts
sbit EDB   = IE^6;  	// Enable Debug
sbit ET2   = IE^5; 	    // Timer 2
sbit ES    = IE^4;	    // Usart 0	
sbit ET1   = IE^3;	    // Timer 1
sbit EX1   = IE^2;	    // External Int1
sbit ET0   = IE^1;	    // Timer 0
sbit EX0   = IE^0;	    // External Int0

/*  IP  */
sbit PDB   = IP^6;	    // Debug
sbit PT2   = IP^5;	    // Timer 2
sbit PS    = IP^4;	    // Usart 0
sbit PT1   = IP^3;	    // Timer 1
sbit PX1   = IP^2;	    // Ext Int1
sbit PT0   = IP^1;      // Timer 0
sbit PX0   = IP^0;	    // Ext Int 0

/*    P4 Alternate 1  */
sbit PCA1_XCLK  = P4^7;	 // PCA1
sbit TCM5       = P4^6;  // TCM5
sbit TCM4       = P4^5;  //	TCM4
sbit TCM3       = P4^4;  //	TCM3
sbit PCA0_XCLK  = P4^3;	 // PCA0
sbit TCM2       = P4^2;  // TCM2
sbit TCM1       = P4^1;  //	TCM1
sbit TCM0       = P4^0;  //	TCM0

  
/*    P4 Alternate 2  */
sbit SPI_SSEL_P4   = P4^7;  // SPI SSEL
sbit SPI_TxD_P4    = P4^6;  // SPI TxD
sbit SPI_RxD_P4    = P4^5;  // SPI RxD
sbit SPI_SCLK_P4   = P4^4;  // SPI SCLK
sbit UART1_TxD_P4  = P4^3;  // UART1 TxD
sbit UART1_RxD_P4  = P4^2;  // UART1 RxD
sbit TMR2_TRG_P4   = P4^1;  // Timer 2 Trigger Input
sbit TMR2_CNT_P4   = P4^0;  // Timer 2 Count Input


/*  P3  */
sbit I2CSC      = P3^7;	 // I2C Serial Clock
sbit I2CSD      = P3^6;	 // I2C Serial Data
sbit CNTR1      = P3^5;	 // Counter 1 Input
sbit CNTR0      = P3^4;	 // Counter 0 Input
sbit INT1       = P3^3;	 // Ext Int 1 / Timer 1 Gate	
sbit INT0       = P3^2;	 // Ext Int 0 / Timer 0 Gate
sbit UART0_TxD  = P3^1;	 // UART0 TxD
sbit UART0_RxD  = P3^0;	 // UART0 RxD


/*  P1 Alternate 1 */
sbit SPI_SSEL   = P1^7;	 // SPI SSEL
sbit SPI_TxD    = P1^6;  // SPI TxD
sbit SPI_RxD    = P1^5;  // SPI RxD
sbit SPI_SCLK   = P1^4;  // SPI SCLK
sbit UART1_TxD  = P1^3;  // UART1 TxD
sbit UART1_RxD  = P1^2;  // UART1 RxD
sbit TMR2_TRG   = P1^1;  // Timer 2 Trigger Input
sbit TMR2_CNT   = P1^0;  // Timer 2 Count Input


/*  P1 Alternate 2 */
sbit ADC7       = P1^7;	 // ADC Channel 7
sbit ADC6       = P1^6;	 // ADC Channel 6
sbit ADC5       = P1^5;	 // ADC Channel 5
sbit ADC4       = P1^4;	 // ADC Channel 4
sbit ADC3       = P1^3;	 // ADC Channel 3
sbit ADC2       = P1^2;	 // ADC Channel 2
sbit ADC1       = P1^1;	 // ADC Channel 1
sbit ADC0       = P1^0;	 // ADC Channel 0

             
/*  T2CON  */
sbit TF2        = T2CON^7;
sbit EXF2       = T2CON^6;
sbit RCLK       = T2CON^5;
sbit TCLK       = T2CON^4;
sbit EXEN2      = T2CON^3;
sbit TR2        = T2CON^2;
sbit C_T2       = T2CON^1;
sbit CP_RL2     = T2CON^0;


/*    PCON   */
/*
sbit SMOD0      = PCON^7;	// Baud Rate bit for UART0	
sbit SMOD1      = PCON^6;	// Baud Rate bit for UART1
sbit LVD        = PCON^5;	// Low voltage Reset enable
sbit POR        = PCON^4;  	// Power On Reset
sbit PD         = PCON^1;	// Power Down Mode
sbit IDLE       = PCON^0;  	// Idle Mode
*/

/*    TMOD   */
/*
sbit GATE1      = TMOD^7;
sbit C_T1       = TMOD^6;
sbit M11        = TMOD^5;
sbit M10        = TMOD^4;
sbit GATE0      = TMOD^3;
sbit C_T0       = TMOD^2;
sbit M01        = TMOD^1;
sbit M00        = TMOD^0;
*/


/*    P1 GPIO   */
sbit P1_7       = P1^7;	   // bit 7 of P1
sbit P1_6       = P1^6;    // bit 6 of P1
sbit P1_5       = P1^5;	   // bit 5 of P1
sbit P1_4       = P1^4;	   // bit 4 of P1
sbit P1_3       = P1^3;	   // bit 3 of P1
sbit P1_2       = P1^2;	   // bit 2 of P1
sbit P1_1       = P1^1;	   // bit 1 of P1
sbit P1_0       = P1^0;	   // bit 0 of P1

/*    P3 GPIO   */
sbit P3_7       = P3^7;	   // bit 7 of P3
sbit P3_6       = P3^6;	   // bit 6 of P3
sbit P3_5       = P3^5;	   // bit 5 of P3
sbit P3_4       = P3^4;	   // bit 4 of P3
sbit P3_3       = P3^3;	   // bit 3 of P3
sbit P3_2       = P3^2;	   // bit 2 of P3
sbit P3_1       = P3^1;	   // bit 1 of P3
sbit P3_0       = P3^0;	   // bit 0 of P3

/*    P4 GPIO   */
sbit P4_7       = P4^7;	   // bit 7 of P4
sbit P4_6       = P4^6;	   // bit 6 of P4
sbit P4_5       = P4^5;	   // bit 5 of P4
sbit P4_4       = P4^4;	   // bit 4 of P4
sbit P4_3       = P4^3;	   // bit 3 of P4
sbit P4_2       = P4^2;	   // bit 2 of P4
sbit P4_1       = P4^1;	   // bit 1 of P4
sbit P4_0       = P4^0;	   // bit 0 of P4


/*    ACON   */
//sbit AINTF  = ACON^7;
//sbit AINTEN = ACON^6;
//sbit ADEN   = ACON^5;
//sbit ADS2   = ACON^4;
//sbit ADS1   = ACON^3;
//sbit ADS0   = ACON^2;
//sbit ADST   = ACON^1;
//sbit ADSF   = ACON^0;

/*  SCON1   */
sbit SM01   = SCON1^7;
sbit SM11   = SCON1^6;
sbit SM21   = SCON1^5;
sbit REN1   = SCON1^4;
sbit TB81   = SCON1^3;
sbit RB81   = SCON1^2;
sbit TI1    = SCON1^1;
sbit RI1    = SCON1^0;


 /*  IEA  */
//sbit ADC    = IEA^7;
//sbit SPI    = IEA^6; 
//sbit PCA    = IEA^5; 
//sbit ES2    = IEA^4;
//sbit EI2C   = IEA^1;
//sbit EUSB   = IEA^0;

/*  IPA  */
//sbit PADC   = IPA^7;
//sbit PSPI   = IPA^6;
//sbit PPCA   = IPA^5;
//sbit PS2    = IPA^4;
//sbit PI2C   = IPA^1;
//sbit PUSB   = IPA^0;


/*  S1CON  */
//sbit CR2        = S1CON^7;
//sbit ENI1       = S1CON^6; 
//sbit STA        = S1CON^5; 
//sbit STO        = S1CON^4;
//sbit ADDR       = S1CON^3;
//sbit AA         = S1CON^2;
//sbit CR1        = S1CON^1;
//sbit CR0        = S1CON^0;

/*  S1STA  */
//sbit GC         = S1STA^7;
//sbit STOP       = S1STA^6; 
//sbit INTR       = S1STA^5; 
//sbit TX_MD      = S1STA^4;
//sbit BBUSY      = S1STA^3;
//sbit BLOST      = S1STA^2;
//sbit ACK_R      = S1STA^1;
//sbit SLV        = S1STA^0;

/* IRDACON */
//sbit IRDAEN     = IRDACON^6;
//sbit BIT_PULSE  = IRDACON^5;
//sbit CDIV4      = IRDACON^4;
//sbit CDIV3      = IRDACON^3;
//sbit CDIV2      = IRDACON^2;
//sbit CDIV1      = IRDACON^1;
//sbit CDIV0      = IRDACON^0;


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
#define UART0_VECTOR		4		//0x23 Serial Port 0
#define UART0_VECTOR_ADDR		0x23
#define TF2_VECTOR			5		//0x2B Timer 2
#define TF2_VECTOR_ADDR			0x2B	
#define ADC_VECTOR			7		//0x3B ADC
#define ADC_VECTOR_ADDR			0x3B
#define I2C_VECTOR			8		//0x43 I2C
#define I2C_VECTOR_ADDR			0x43	
#define UART1_VECTOR   		9		//0x4B Serial Port 1
#define UART1_VECTOR_ADDR  		0x4B	
#define SPI_VECTOR			10		//0x53 SPI
#define SPI_VECTOR_ADDR			0x53
#define PCA_VECTOR			11		//0x5B PCA
#define PCA_VECTOR_ADDR			0x5B
#define DBG_VECTOR			12		//0x63 DEBUG (Highest Priority)
#define DBG_VECTOR_ADDR			0x63

/* ---------------------------------- */


#endif
