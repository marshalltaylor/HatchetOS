/* ============================================================================ */
/* This is a copy of msp430f47177.cmd with alternate names for the LCD          */
/* interface.                                                                   */
/*                                                                              */
/* There must exist an include file that operates like msp430f47177.h           */
/* Probably, this is located in hitachi_9049.h and p8_bus_9049.h                */
/*                                                                              */
/* ============================================================================ */

/************************************************************
* DIGITAL I/O Port7/8 Pull up / Pull down Resistors
************************************************************/
/*originally port 7, dual mapping*/
HITACHI_CTL_IN               = 0x0038;
HITACHI_CTL_OUT              = 0x003A;
HITACHI_CTL_DIR              = 0x003C;
HITACHI_CTL_SEL              = 0x003E;
HITACHI_CTL_REN              = 0x0014;
P8_CTL_IN               = 0x0038;
P8_CTL_OUT              = 0x003A;
P8_CTL_DIR              = 0x003C;
P8_CTL_SEL              = 0x003E;
P8_CTL_REN              = 0x0014;
/*originally port 8*/
P8_BUS_IN               = 0x0039;
P8_BUS_OUT              = 0x003B;
P8_BUS_DIR              = 0x003D;
P8_BUS_SEL              = 0x003F;
P8_BUS_REN              = 0x0015;

/************************************************************
* DIGITAL I/O Port9/10 Pull up / Pull down Resistors
************************************************************/
/*originally port 10*/
HITACHI_LCD_IN              = 0x0009;
HITACHI_LCD_OUT             = 0x000B;
HITACHI_LCD_DIR             = 0x000D;
HITACHI_LCD_SEL             = 0x000F;
HITACHI_LCD_REN             = 0x0017;

/************************************************************
* End of Modules
************************************************************/
