// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

//************************************************************************80*//
//   Hitachi LCD type include
//
//  Files that use these functions need:  #include "IO_9049.h"
//***************************************************************************//

/*----------------------------------------------------------------------------*/
/* PERIPHERAL FILE MAP                                                        */
/*----------------------------------------------------------------------------*/

#ifndef SFR_8BIT
/* External references resolved by a device-specific linker command file */
#define SFR_8BIT(address)   extern volatile unsigned char address
#define SFR_16BIT(address)  extern volatile unsigned int address
//#define SFR_20BIT(address)  extern volatile unsigned int address
typedef void (* __SFR_FARPTR)();
#define SFR_20BIT(address) extern __SFR_FARPTR address
#define SFR_32BIT(address)  extern volatile unsigned long address

#endif

#ifndef HITACHI_H
  #define HITACHI_H
  //Names the control ports 
  SFR_8BIT(HITACHI_CTL_IN);                               /* Port 7 Input */
  SFR_8BIT(HITACHI_CTL_OUT);                              /* Port 7 Output */
  SFR_8BIT(HITACHI_CTL_DIR);                              /* Port 7 Direction */
  SFR_8BIT(HITACHI_CTL_SEL);                              /* Port 7 Selection */
  SFR_8BIT(HITACHI_LCD_REN);                              /* Port 7 Resistor Enable */
  
  SFR_8BIT(HITACHI_LCD_IN);                               /* Port 10 Input */
  SFR_8BIT(HITACHI_LCD_OUT);                              /* Port 10 Output */
  SFR_8BIT(HITACHI_LCD_DIR);                              /* Port 10 Direction */
  SFR_8BIT(HITACHI_LCD_SEL);                              /* Port 10 Selection */
  SFR_8BIT(HITACHI_LCD_REN);                              /* Port 10 Resistor Enable */

  //Core functions.  These control the buffers
  void set_hitachi( char );
  // use:  RS_PIN + RW_PIN + E_PIN
  
  void set_n_enb_hitachi( char );
  // use:  N_LCD_ON_PIN
  
  void set_ctrl_hitachi( char );
  // use:  LCD_BKLT_PIN
  
  //Functions specific to driving an LCD
  //set the state of the LCD control pins.  Pass anded bits from .h
  
  #endif /* HITACHI_H */
