//************************************************************************80*//
//   relay_btn_9049                                  hint: type, THEN block
//			
//  Controls the output relay and button
//
//***************************************************************************//
#include "msp430f47177.h"
#include "IO_9049.h"
#include "relay_btn_9049.h"
#include "timers.h"
#include "ascii_lcd.h"
#include "UART_generic.h"
#include "HOS_char.h"

extern serial_port uart1;


//***************************************************************************//
//   char get_btn_state( void )
//			
//  Require 25 consecutive cycles to debounce
//
//***************************************************************************//
char get_btn_state( void )
{
	char output = 0;
	int i;
	
	for( i = 0; i < 25; i++ )
	{
		if( (P7IN & N_CI_PIN) == 0 ) //if the bit is low
		{
			//CI detected
			output++;
		}
	}
	
	if( output == 25 )
	{
		output = 1;
	}
	else
	{
		output = 0;
	}
	
	return output;
}

//***************************************************************************//
//   void set_relay_state( char input )      
//
//	pass: 	OPEN
//			CLOSED
//	
//	where OPEN = 0 and CLOSED = 1
//
//***************************************************************************//
void set_relay_state( char input )
{
	if( input == 0 )
	{
		P7OUT &= ~( OUT01_PIN );
	}
	else
	{
		P7OUT |= OUT01_PIN;
	}
	return;
}

//***************************************************************************//
//   void demo_relay( void )      
//
//
//***************************************************************************//
void demo_relay( void )
{
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(405);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(243);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(162);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(112);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(83);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(61);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(41);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(31);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	ms_delay(17);
	//
	set_relay_state( CLOSED );
	ms_delay(15);
	set_relay_state( OPEN );
	
	return;
}

//***************************************************************************//
//   void execute_test( void )      
//
//
//***************************************************************************//
void execute_test( void )
{
	int i = 0;
	int ms_counted;
	char dec_string[11];  //used to convert ints to ascii
	
	lcd_set_cur( 0, 0 );
	lcd_writestring("                                ");
	uart1.writestring("SYNC,CYLE TIME, TIME BEFORE FALL\n");
	for( i = 5000; (uart1.lastchar != 0x1B )&&(i<8000); i = i + 100 ) //checks for 'esc' during cycle
	{
		ms_counted = 0;
		//clear lastchar
		uart1.lastchar = 0x00;

		//wait for sync
		while( get_btn_state() == 0 );
		lcd_set_cur( 11, 0 );
		lcd_writestring("sync.");
		uart1.writestring("sync,");
		//wait a bit for sync;
		ms_delay(800);
		ms_counted = ms_counted + 800;
		lcd_set_cur( 11, 0 );
		lcd_writestring("     ");
		//report step
		long2ascii( i, dec_string );
		uart1.writestring( dec_string );
		uart1.writestring(",");
		//count the number of ms before closing the relay
		ms_delay( i - 800 );
		ms_counted = ms_counted + i;
		set_relay_state( CLOSED );
		//Wait for input to go low	
		while( (get_btn_state() == 1)&&(ms_counted < 20000 )) //bails afte 20s
		{
			us_delay(1000);
			ms_counted++;
		}
		//report time input went low
		long2ascii( ms_counted, dec_string );
		uart1.writestring( dec_string );
		uart1.writestring("\n");
		set_relay_state( OPEN );
		//wait before resetting
		ms_delay( 1500 );
	

	}
}
