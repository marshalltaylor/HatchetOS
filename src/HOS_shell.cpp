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

#include "UART_generic.h"
#include "msp430f47177.h"
#include "HOS_char.h"
#include "HOS_shell.h"
#include "IO_9049.h"
#include "LEDs.h"
#include "timers.h"
#include "ascii_lcd.h"
#include "relay_btn_9049.h"

extern serial_port uart1;
extern unsigned int count_A0;

//char cmdhistory[8][40];
char cmdline[8][40];
//char hline_ptr = 0;

//debug variables
int non_alpha_caught = 0;
extern int trap_isr_count;
void hos_shell( void )
{
//  line_parse cmdline;
  long temp1;
  long temp2;
  int exitshell;
  int cmdline_ptr;
  int cmdline_lptr;
  char hex_buf[4];
  ms_delay(1000);

  exitshell = 0;    //set 1 to leave shell
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n--------------------------------------------------------------------------------\n");
  uart1.writestring("\nHatchet OS Shell\n");
  uart1.writestring("Carefully bludgeoned together by Marshall Taylor\n");
  uart1.writestring("\n");
  uart1.writestring("alpha  2012\n");
  uart1.writestring("beta   July, 2014\n");
  uart1.writestring("1.0    August, 2014\n");
  uart1.writestring("\n--------------------------------------------------------------------------------\n");
  uart1.writestring("\n");
  uart1.writestring("\n");
  uart1.writestring("\n");

  //Call HOS boot routines here
  uart1.writestring("Initializing LCD...");
  lcd_init();
  uart1.writestring("Done!\n");
  uart1.writestring("Writing test data to screen...");
  lcd_writestring("9049 Demo");
  lcd_set_cur( 0, 1 );
  lcd_writestring("Nice work Josh!");
  uart1.writestring("Done!\n");
  uart1.writestring("Relay test...");
  demo_relay();
  uart1.writestring("Done!\n");


  uart1.writestring("\n");
  uart1.writestring("Boot successful!\n\n");
  uart1.writestring("Use 'help' for more information\n");
  uart1.writestring("\n");

	//Clears the command line 2D array
  for(cmdline_ptr=0;cmdline_ptr<20;cmdline_ptr++)
  {
  	for(cmdline_lptr=0;cmdline_lptr<8;cmdline_lptr++)
  	{
	    	cmdline[cmdline_lptr][cmdline_ptr] = 0x00;
  	}
  }
  cmdline_ptr = 0;
  cmdline_lptr = 0;


  while(exitshell == 0)
  {

	    cmdline_ptr = 0; // reset to left (enter has been pressed)

		//Give a prompt
	    uart1.writechar('>');
	    uart1.lastchar = 0x00;

    char parse_now = 0;  //reset.  Set 1 to leave the loop

    while( !parse_now ) // This loop is a bit redundant...
    {
    	//loop until internally decided to leave
    	switch( uart1.lastchar ) {
    	case 0x1B://escape
    		uart1.lastchar = 0x00;
    		while( !uart1.lastchar );  //wait for next key
    		if( uart1.lastchar == '[' )  //OK!  We got a cursor control indicator
    		{
        		uart1.lastchar = 0x00;
        		while( !uart1.lastchar );  //wait for next key
            	switch( uart1.lastchar ) {
            	case 'A': //Up
            		uart1.writestring("\x1B[2K"); // clear line
            		uart1.writestring("\r"); // cr
            		uart1.writestring(">"); // Give a prompt
            		//decrement cmdline_lptr
            		cmdline_lptr--;
            		cmdline_lptr &= 0x07;
            		//print out that line
            		cmdline_ptr = uart1.writestring((char *)((int)&cmdline + (40 * cmdline_lptr)));  //writes line, also reports char position
            		break;
            	case 'B': //Down
            		uart1.writestring("\x1B[2K"); // clear line
            		uart1.writestring("\r"); // cr
            		uart1.writestring(">"); // Give a prompt
            		//increment the cmdline_lptr
            		cmdline_lptr++;
            		cmdline_lptr &= 0x07;
            		//print out that line
            		cmdline_ptr = uart1.writestring((char *)((int)&cmdline + (40 * cmdline_lptr)));  //writes line, also reports char position
            		break;
            	case 'C': //Right
                    if( cmdline_ptr < CMD_LINE_LENGTH ) //Move pointer in command line
                    {
                    	cmdline_ptr++;
                        uart1.writestring("\x1B[C"); // go right
                    }
                    break;
            	case 'D': //Left
                    if( cmdline_ptr > 0 ) //Move pointer in command line
                    {
                    	cmdline_ptr--;
                        uart1.writestring("\x1B[D"); // go left
                    }
            		break;
            	default:
            		break;
            	}
    		}
    		uart1.lastchar = 0x00;
    		break;
    	case 0x08: //backspacearoo
    		uart1.lastchar = 0x00; //Clear the char
            if( cmdline_ptr > 0 ) //Move pointer in command line
            {
            	cmdline_ptr--;
                uart1.writestring("\x1B[D"); // Go left
                cmdline[cmdline_lptr][cmdline_ptr] = 0x00; //clear current char in the buffer
                uart1.writestring(" "); //clear current char on the screen
                uart1.writestring("\x1B[D"); // Go left
            }
    		break;
    	case 0x00:
    		break;
    	case 0x0D:
    		parse_now = 1;
    		break;
    	case 0x0A:
    		parse_now = 1;
    		break;
    	default:
    		if(( uart1.lastchar > 0x1F ) && ( uart1.lastchar < 0x7F ))// only process valid characters into the command line
    		{
                uart1.writechar(uart1.lastchar);
                cmdline[cmdline_lptr][cmdline_ptr] = uart1.lastchar;
                if( cmdline_ptr < CMD_LINE_LENGTH )
                {
                	cmdline_ptr++;
                }
                cmdline[cmdline_lptr][cmdline_ptr] = 0x00;
    		}
    		else
    		{
    			non_alpha_caught++;
    		}
    		uart1.lastchar = 0x00;
    		break;
    	}

    }

    //

    //Give a return
    uart1.writechar(0x0A);
    uart1.writechar(0x0D);
	
    //Reference the crazy 2D array into a single char *
    char * cmd_entered_ptr;
	cmd_entered_ptr = (char *)((int)&cmdline + (40 * cmdline_lptr));

	cmdline_lptr++; //Now that the line to operate on is buffered int cmd_char_ptr we can increment the 2D line pointer
	cmdline_lptr &= 0x07;
	

	//***Line to operate on now called cmd_entered_ptr, use it as an array***//



	//Start parcin'
    cmdline_ptr = 0;  //Is this really necessary?
    char dec_string[11];  //used to convert ints to ascii

    //Example parcer usage is the "help" command.
    if(stringcompare(cmd_entered_ptr, "help", 0, 0))
    {
      uart1.writestring("\n");
      uart1.writestring("\n Commands:");
      uart1.writestring("\n    help             Shows this menu");
      uart1.writestring("\n    info             Displays debug info");
      uart1.writestring("\n    larson           Exercise LEDs");
      uart1.writestring("\n    button           Demos input");
	  uart1.writestring("\n    lcd home         ");
	  uart1.writestring("\n    lcd init         ");
	  uart1.writestring("\n    lcd write nn     Give 2 byte hex (0A not 0x0A)");
	  uart1.writestring("\n                     Writes 12 bits as command");
	  uart1.writestring("\n    lcd read         Some LCDs don't report status");
	  uart1.writestring("\n    hello world      Test LCD display");
	  uart1.writestring("\n");
      uart1.writestring("\n ESC can get you out most commands.  It checks during the command ");
      uart1.writestring("\n loop start so you may have to hold it through the cycle.");
      uart1.writestring("\n\n");
    }

	if(stringcompare(cmd_entered_ptr, "info", 0, 0))
    {
		//Report debug info
		uart1.writestring("trap_isr_count: ");
		long2ascii( trap_isr_count, dec_string );
		uart1.writestring( dec_string );
		uart1.writestring("\n");
		uart1.writestring("non_alpha_caught: ");
		long2ascii( non_alpha_caught, dec_string );
		uart1.writestring( dec_string );
		uart1.writestring("\n\n");


	}

	if(stringcompare(cmd_entered_ptr, "larson", 0, 0))
    {
		larson();
	}
	if(stringcompare(cmd_entered_ptr, "toggle", 0, 0))
    {
		while( uart1.lastchar != 0x1B ) //checks for 'esc'
		{
			//clear lastchar
			uart1.lastchar = 0x00;
			set_relay_state( CLOSED );
			uart1.writestring("Closed\n");
			//wait 1000ms
			ms_delay(1000);
			set_relay_state( OPEN );
			uart1.writestring("Open\n");
			//wait 1000ms
			ms_delay(1000);

		}
	}
	if(stringcompare(cmd_entered_ptr, "demo", 0, 0))
    {
		demo_relay();
	}	if(stringcompare(cmd_entered_ptr, "execute", 0, 0))
    {
		execute_test();
	}
	if(stringcompare(cmd_entered_ptr, "button", 0, 0))
    {
		while( uart1.lastchar != 0x1B ) //checks for 'esc'
		{
			//clear lastchar
			uart1.lastchar = 0x00;
			//check button
			if( get_btn_state() )
			{
				uart1.writestring("Button!\n");
				while( get_btn_state() == 1 );
				//wait 100ms
				ms_delay(100);
			}

		}

	}
	if(stringcompare(cmd_entered_ptr, "lcd home", 0, 0))
    {
		lcd_set_cur( 0, 0 );
	}
	if(stringcompare(cmd_entered_ptr, "lcd init", 0, 0))
    {
		lcd_init();
	}
	if(stringcompare(cmd_entered_ptr, "lcd write", 0, 0))
    {
		char lcd_temp;
		lcd_temp = char2hex(cmd_entered_ptr[10]) << 4;
		lcd_temp |= char2hex(cmd_entered_ptr[11]);
		lcd_bus_op( RS_INST, RW_WRITE, lcd_temp );
		//   Use RS_DATA RS_INST, RW_READ, RW_WRITE
	}
	if(stringcompare(cmd_entered_ptr, "lcd read", 0, 0))
    {
		//Report debug info
		uart1.writestring("returned value: ");
		long2ascii( lcd_bus_op( RS_INST, RW_READ, 0xAA ), dec_string );
		uart1.writestring( dec_string );
		uart1.writestring("\n");
	}
	if(stringcompare(cmd_entered_ptr, "hello world", 0, 0))
    {
		lcd_writestring("Hello World!");
	}

  }
}
