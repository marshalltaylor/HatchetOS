//Basic set and clear functions.  Give BITx or LEDx sums
//In the future, possible byte operations could be added.
#include "msp430f47177.h"
#include "IO_9049.h"
#include "LEDs.h"
//for larson
#include "timers.h"
#include "UART_generic.h"

//for larson with HOS, for escape key detection
extern serial_port uart1;

extern unsigned int count_A0;

void set_leds( unsigned int input_mask )
{
	char port9_byte;
	char port7_byte;
	//make leds 5-12 the whole port 7 byte
	port9_byte = (char)(input_mask >> 4);
	//make leds 1-4 the upper nyble of port 9
	port7_byte = 0xF0 & (char)(input_mask << 4);
	//set flagged bits
	P7OUT &= ~port7_byte;
	P9OUT &= ~port9_byte;
	
}

void clear_leds( unsigned int input_mask )
{
	char port9_byte;
	char port7_byte;
	//make leds 5-12 the whole port 7 byte
	port9_byte = (char)(input_mask >> 4);
	//make leds 1-4 the upper nyble of port 9
	port7_byte = 0xF0 & (char)(input_mask << 4);
	//set flagged bits
	P7OUT |= port7_byte;
	P9OUT |= port9_byte;

}

void larson( void )
{
	//Larson scanner, right?
	char larson_dir;
	char larson_shift;
	larson_shift = 1;  //shift pos 2
	larson_dir = 1;  //right (lower)
	while( uart1.lastchar != 0x1B ) //checks for 'esc'
	{
		if( larson_dir == 1 )
		{
			//clear lastchar
			uart1.lastchar = 0x00;
			//try and rotate right
			if( larson_shift > 0)
			{
				//set output
				set_leds(0x7 << larson_shift);
				clear_leds(0xFFF & ~(0x7 << larson_shift));
				//shift
				larson_shift--;

			}
			else
			{
				//set output
				set_leds(0x7 << larson_shift);
				clear_leds(0xFFF & ~(0x7 << larson_shift));
				//switch
				larson_dir = 0;
				larson_shift++;
			}
		}
		else
		{
			//try and rotate left
			if( larson_shift < 9)
			{
				//set output
				set_leds(0x7 << larson_shift);
				clear_leds(0xFFF & ~(7 << larson_shift));
				//shift
				larson_shift++;
			}
			else
			{
				//set output
				set_leds(0x7 << larson_shift);
				clear_leds(0xFFF & ~(0x7 << larson_shift));
				//switch
				larson_dir = 1;
				larson_shift--;
			}
		}
		//Wait now
    	us_delay( 100000 );
	}

}
