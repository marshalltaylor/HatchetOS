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
//   8 bit bus driver functions                      hint: type, THEN block
//
//  This function drives the 4 pins of the cpu, 8 pins of data, and the 
//  r/w pin of the bus driver.  It uses the cpu directly and must reference
//  the appropriate header files.
//
//  Use by setting the 4 pins to common names, and drive with a function that
//  knows the specifications of the protocol.  This driver protects the hardware
//  by not writing to a bus already being written to.
//
//  The intention is that this file remains useful for porting to other similar
//  hardwares.  This particular version has been hardcoded to map the LCD pin
//  functions though.  No upper functions should touch the hardware at this
//  point.
//
//    Happy coding!
//
//***************************************************************************//
#include "msp430.h"
#include "msp430f47177.h"
#include "IO_9049.h"
#include "p8_bus_9049.h"

//read port, return char
char read_p8_bus( void )
{
	//Check if 430 port is configured 'outward' before changing buffer
	if( P8_BUS_DIR ) //pin high for output
	{
		//Set the 430 to input
		P8_BUS_DIR = 0x00;
		//set a diag LED to OFF (P7.4)
		P7OUT |= BIT4;
	}
	
	//Set up buffer
	P8_CTL_OUT &= ~BUFFER_DIR_PIN; //set low for read
	
	//Wait for the bus to become ready
	//not needed for 16MHz cpu
	
	//Read port
	return P8_BUS_IN;

}

//Set output byte on bus
void write_p8_bus( char p8_data )
{
	//Check if the buffer is set is configured 'inward' before setting buffer  
	if( (P8_CTL_OUT & BUFFER_DIR_PIN) == 0 ) //check low for read
	{
		//Config the buffer
		P8_CTL_OUT |= BUFFER_DIR_PIN; //set high for write
	}
	
	//Load the data to the 430's output drivers
	P8_BUS_OUT = p8_data;
	
	//Set the bus direction to output
	P8_BUS_DIR = 0xFF;
	//set a diag LED to ON (P7.4)
	P7OUT &= ~BIT4;
	
	return;
}

// //Puts the bus into the intermediary state.  Named as such to invoke caution of use.
// void cook_p8_bus( void )
// {
    // //Set the 430 to input
	// P8_BUS_DIR = 0x00;
	// //set buffer to write.  This is the danger!  The connected device should already be in read.
	// P8_CTL_OUT |= BUFFER_DIR_PIN; //set high for write
	
	// return;
// }
