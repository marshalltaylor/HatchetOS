//************************************************************************80*//
//   IO functions                                    hint: type, THEN block
//
//  This safely configures the IO on the 9049 to match a base configuration.
//
//  Once executed once, it isn't necessary to revisit the code, but the include
//  names all the board level IO of the 9049.  #include "IO_9049.h"
//
//***************************************************************************//
#include "msp430f47177.h"  //This may be necessary
#include "IO_9049.h"

void init_IO_9049( void )
{
	//Port 1
	//Port 2 -- UART
	P2SEL &= ~(UART_RTS_PIN + UART_CTS_PIN);
	P2SEL |= UART_RXD_PIN + UART_TXD_PIN;
	P2DIR &= ~(UART_CTS_PIN);
	P2DIR |= UART_RTS_PIN;
	
	//Port 3 -- J4 SPI / industrial interface
	P3SEL |= J4_SCLK_PIN + J4_MISO_PIN + J4_MOSI_PIN;
	P2DIR &= ~(J4_MOSI_PIN);
	P2DIR |= J4_SCLK_PIN + J4_MISO_PIN;
	
	//Port 4 -- Industrial interface
	P4SEL &= ~(DSCSW_STS_PIN + OUT_EN_PIN + CS0_PIN + CS1_PIN + QRESET_PIN);
	P4DIR &= ~(DSCSW_STS_PIN);
	P4DIR |= DSCSW_STS_PIN + OUT_EN_PIN + CS0_PIN + CS1_PIN + QRESET_PIN;
	
	//Port 5
	
	//Port 6
	
	//Port 7 -- LEDs / LCD control
	P7OUT |= LED4_PIN + LED3_PIN + LED2_PIN + LED1_PIN;
	P7OUT &= ~(LCD_BKLT_PIN);
	P7SEL = 0x00;
	P7DIR &= ~(N_CI_PIN);
	P7DIR |= LED4_PIN + LED3_PIN + LED2_PIN + LED1_PIN + BUFFER_DIR_PIN + LCD_BKLT_PIN + OUT01_PIN;
	
	//*** Safe init order of LCD ***///
	//Set MSP430 IO as input
	//Set drive as input
	//Set set LCD as READ and INST (both low)
	//Later, enable power to LCD
	
	//Port 8 -- LCD data pins
	P8OUT = 0x00;
	P8SEL = 0x00;
	P8DIR = 0x00; // init as inputs

	//Port 7 -- LEDs / LCD control
	P7OUT &= ~BUFFER_DIR_PIN;

	//Port 10 -- LCD control
	P10OUT &= ~(E_PIN + RS_PIN + RW_PIN);
	P10OUT |= N_LCD_ON_PIN;
	P10SEL &= ~(RS_PIN + RW_PIN + E_PIN + N_LCD_ON_PIN);
	P10DIR |= RS_PIN + RW_PIN + E_PIN + N_LCD_ON_PIN;
	
	//Port 9 -- All LEDs
	P9OUT = 0xFF; //off
	P9SEL = 0x00;
	P9DIR = 0xFF; // All outputs
	
}
