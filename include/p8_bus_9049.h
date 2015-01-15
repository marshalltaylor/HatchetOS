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
//   8 bit bus driver include
//
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

#ifndef P8_BUS_H
  #define P8_BUS_H
  //Kind of silly here because port 8 is an 8 bit port, but we want
  //to be consistant.

  SFR_8BIT(P8_CTL_IN);                               /* Port 7 Input */
  SFR_8BIT(P8_CTL_OUT);                              /* Port 7 Output */
  SFR_8BIT(P8_CTL_DIR);                              /* Port 7 Direction */
  SFR_8BIT(P8_CTL_SEL);                              /* Port 7 Selection */
  SFR_8BIT(P8_CTL_REN);                              /* Port 7 Resistor Enable */

  SFR_8BIT(P8_BUS_IN);                               /* Port 8 Input */
  SFR_8BIT(P8_BUS_OUT);                              /* Port 8 Output */
  SFR_8BIT(P8_BUS_DIR);                              /* Port 8 Direction */
  SFR_8BIT(P8_BUS_SEL);                              /* Port 8 Selection */
  SFR_8BIT(P8_BUS_REN);                              /* Port 8 Resistor Enable */

  //Core functions.  These control the buffers
  //read port, return char
  char read_p8_bus( void );
  
  //write port, return diag
  void write_p8_bus( char );
  
  //Set the 9049 side bus Z, forcing drive of the output
  void cook_p8_bus( void );
  
  //Functions specific to driving an LCD
  //set the state of the LCD control pins.  Pass anded bits from .h
  
  
#endif /* P8_BUS_H */
  
  
