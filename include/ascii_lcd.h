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
//   Top level ascii LCD interface include
//
//  Files that use these functions need:  #include "IO_9049.h"
//***************************************************************************//
#ifndef ASCII_LCD_H
  #define ASCII_LCD_H
  
  #define CLEAR_DISPLAY           0x01
  #define CURSOR_HOME             0x02
  #define ENTRY_MODE_SET          0x04
  #define DISPLAY_ON_OFF_CONTROL  0x08
  #define CURSOR_DISPLAY_SHIFT    0x10
  #define FUNCTION_SET            0x20
  #define SET_CGRAM_ADDRESS       0x40
  #define SET_DDRAM_ADDRESS       0x80
  
  //void lcd_writechar( char reg_select, char outchar )
  //rename to pin position
  #define RS_DATA RS_PIN
  #define RS_INST 0
  #define RW_READ RW_PIN
  #define RW_WRITE 0
  
  void lcd_init( void );

  char lcd_bus_op( char, char, char );

  void lcd_writechar( char );

  void lcd_set_cur( char, char );

  int lcd_writestring( char * );

  char char_flip( char );

  #endif /* ASCII_LCD_H */
