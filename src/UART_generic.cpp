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

//***************************************************************************//
//   UART functions
//
//***************************************************************************//
#include "msp430f47177.h"
#include "UART_generic.h"
//#include "char.h"
 #include "ascii_lcd.h"

extern serial_port uart1;
char rx_buffer1[8];
char rx_buffer1_ptr;

//***************************************************************************//
//   serial_port::writechar( char outchar )
//
//   Writes outchar.  When using with interrupts, be sure writechar is passed
//   the interrupt referenced value and not one in the cpu regs.
//
//***************************************************************************//
void serial_port::writechar( char outchar )
{
  while(UCA0STAT & UCBUSY);
  UCA0TXBUF = outchar;
//  char buf[2];
//  buf[1] = 0x00;
//  buf[0] = outchar;
//  lcd_writestring( buf );
  return;
}

//***************************************************************************//
//   serial_port::writestring( char *outstring )
//
//   Writes until it finds a null, 0x00, or until it has written 80 chars.
//   Each \n is interpreted as requiring a nl and cr to be written.
//
//   Returns number of characters printed
//
//***************************************************************************//
int serial_port::writestring( char *outstring )
{
  int in_pointer = 0;
  int num_printed = 0;
  while( (outstring[in_pointer] != 0x00) && (in_pointer < 80) )
  {
    if( outstring[in_pointer] == '\n' )
    {
      writechar(0x0A);
      writechar(0x0D);
    }
    else
    {
       	writechar(outstring[in_pointer]);
       	num_printed++;
    }
    in_pointer++;
  }
  return num_printed;
}

//***************************************************************************//
//   This function initializes the UART module
//
//   int init_serial_UART( int clksrc, int clkfreq, int baud, int port)
//   clksrc can be
//      clksrc_ACLK (1)
//      clksrc_SMCLK (2)
//   clkfreq is in Hz
//   baud is in Hz
//   port can be A0 or A1
//
//***************************************************************************//
int serial_port::init_serial_UART( int clksrc, unsigned long clkfreq, unsigned long baud, int port )
{  
  // init Uart A0 at 9600 baud for 16.384 MHz clock
  unsigned int errorstate;
  unsigned int UCBRF_temp;
  unsigned int UCBRS_temp;
  float n;
  errorstate = 0;
  n = clkfreq/baud;                         // from the datasheet...
  
  switch( port )
  {
  case A0:
    {
      P2SEL |= BIT4+BIT5;                       // P2.4,5 = USCI_A0 RXD/TXD
      //NO!  One stop bit.  UCA0CTL0 |= UCSPB;  //2 stop bits
      
      switch( clksrc )   					    //select clock source
      {
      case clksrc_ACLK:
        UCA0CTL1 |= UCSSEL_1;
        break;
      case clksrc_SMCLK:
        UCA0CTL1 |= UCSSEL_2;
        break;
      default :
        errorstate = 1;
      }
      
      if(n >= 15)
      {
        UCA0BR0 = 0x00FF & ( unsigned int )(n/16);             // UCBRx = INT(N)
        UCA0BR1 = 0x00FF & (( unsigned int )(n/16)) >> 8;      //
        UCBRF_temp = ( unsigned int )(((n/16) - ( unsigned int )(n/16)) * 16);
        UCBRS_temp = 0;
        UCA0MCTL = (UCBRF_temp << 4) + (UCBRS_temp << 1) + UCOS16;  // Modulation
        UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
        IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
      }
      else
      {
        errorstate = 1;
        
      }
      break;
    }
  case A1:
    {
      P1SEL |= BIT7+BIT6;                       // P1.6,7 = USCI_A1 RXD/TXD
//      UCA1CTL0 |= UCSPB;  //2 stop bits      
      switch( clksrc )   					    //select clock source
      {
      case clksrc_ACLK:
        UCA1CTL1 |= UCSSEL_1;
        break;
      case clksrc_SMCLK:
        UCA1CTL1 |= UCSSEL_2;
        break;
      default :
        errorstate = 1;
      }
      
      if(n >= 15)
      {
        UCA1BR0 = 0x00FF & ( unsigned int )(n/16);             // UCBRx = INT(N)
        UCA1BR1 = 0x00FF & (( unsigned int )(n/16)) >> 8;      //
        UCBRF_temp = ( unsigned int )(((n/16) - ( unsigned int )(n/16)) * 16);
        UCBRS_temp = 0;
        UCA1MCTL = (UCBRF_temp << 4) + (UCBRS_temp << 1) + UCOS16;  // Modulation
        UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
        UC1IE |= UCA1RXIE;                          // Enable USCI_A0 RX interrupt
      }
      else
      {
        errorstate = 1;
        
      }
      break;
    }  
  default:
    errorstate = 1;
  }
  return errorstate;
  // _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
  char selector = IFG2 & (UCA0RXIFG + UCA0TXIFG);
  if( selector & UCA0RXIFG ) //receive flag
  {
  //  if( !(UCA0STAT & (UCFE + UCOE + UCPE + UCRXERR)) && !(UCA0STAT & UCBUSY)) //process only with no error flags
  //  {
    	rx_buffer1[rx_buffer1_ptr] = UCA0RXBUF;
    	uart1.lastchar = rx_buffer1[rx_buffer1_ptr];
    	//rx_buffer1_ptr++;

      //IFG2 &= ~UCA0RXIFG;
	  //Debug by opening this.  Not necessary for the hatchet shell.
      //uart1.writechar(uart1.lastchar);
  //  }
  }
  //if( selector & UCA0TXIFG ) //transmit flag
  //{
  //  IFG2 &= ~UCA0TXIFG;
  //}
  //UCA0STAT &= ~(UCFE + UCOE + UCPE + UCRXERR);
  //IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

