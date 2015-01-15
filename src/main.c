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

#include "msp430.h"
#include "msp430f47177.h"
#include "ISR_trap.h"
#include "IO_9049.h"
#include "timers.h"
#include "LEDs.h"
#include "UART_generic.h"
#include "HOS_shell.h"

//Globals
extern unsigned int count_A0;
serial_port uart1;

//Compiler should run _system_pre_init() before main
//Main program
int main()
{
	init_IO_9049();
	init_timers();
	trap_isr_count_clear();
	
	uart1.init_serial_UART( clksrc_SMCLK, 12288000, 38400, A0);

    __bis_SR_register(GIE);            // Enable interrupts

    hos_shell();

    while(1);

}



