//************************************************************************80*//
//   relay_btn_9049 include                          hint: type, THEN block
//			
//  Controls the output relay and button
//
//***************************************************************************//
#ifndef RELAY_BTN_9049_H
	#define RELAY_BTN_9049_H
	
	#define OPEN  		0
	#define CLOSED		1

	#define FALSE  		0
	#define TRUE		1
	
	char get_btn_state( void );
	void set_relay_state( char );
	void demo_relay( void );
	void execute_test( void );
	
#endif // RELAY_BTN_9049_H
