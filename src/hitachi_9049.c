//************************************************************************80*//
//   Hitachi LCD type pin functions of 9049          hint: type, THEN block
//
//  This function operates much like the 8 bit bus driver, except it only
//  points to the functions required for control of the LCD character.
//
//  Uses:
//  Port 7, set_ctrl_hitachi(():
//  #define LCD_BKLT_PIN BIT1
//
//  Port 10, set_hitachi(), set_n_enb_hitachi():
//  #define RS_PIN BIT3
//  #define RW_PIN BIT2
//  #define E_PIN BIT1
//  #define N_LCD_ON_PIN BIT0
//
//***************************************************************************//
#include "msp430.h"
#include "msp430f47177.h"
 #include "timers.h"
#include "IO_9049.h"
#include "p8_bus_9049.h"
#include "hitachi_9049.h"

//Functions specific to driving an LCD.  Read, modify, write but with more rules

//set the state of the LCD control pins.  Pass anded bits from .h
void set_hitachi( char lcd_word )
{
	//ms_delay( 200 );
  //write the temp char, then move to output
  char temp_char;

  //mask out only the useful pins from the input
  lcd_word &= RS_PIN + RW_PIN + E_PIN;
  //buffer while making a hole for the new pins
  temp_char = ( HITACHI_LCD_OUT & ~(RS_PIN + RW_PIN + E_PIN) ) | lcd_word;
  //output
  HITACHI_LCD_OUT = temp_char;
  
  return;
}

//powers hitachi. powers if == 0, off if != 0.
void set_n_enb_hitachi( char power_word )
{
	//ms_delay( 200 );
  //write the temp char, then move to output
  char temp_char;

  //mask out only the useful pins from the input
  power_word &= N_LCD_ON_PIN;
  //buffer while making a hole for the new pins
  temp_char = ( HITACHI_LCD_OUT & ~(N_LCD_ON_PIN) ) | power_word;
  //output
  HITACHI_LCD_OUT = temp_char;
  
  return;
}

//set the state of the buffer backlight control.  Masks out all others
//Pass anded bits from .h
void set_ctrl_hitachi( char ctl_word )
{
	//ms_delay( 200 );
  //write the temp char, then move to output
  char temp_char;

  //mask out only the useful pins from the input
  ctl_word &= LCD_BKLT_PIN;
  //buffer while making a hole for the new pins
  temp_char = ( HITACHI_CTL_OUT & ~(LCD_BKLT_PIN) ) | ctl_word;
  //output
  HITACHI_CTL_OUT = temp_char;
  
  return;
}
