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

#include "msp430f47177.h"
#include "timers.h"

unsigned int count_A0;
unsigned int count_B0;

// Timer init
//
// The math on this goes:  If 12.288MHz / 1 / 2048 = 1.5KHz
// The interrupt fires 3 times per millisecond

void init_timers()
{
	// Timer A config
    TA0CCR0 = 2048;							// set up 100 samples per 60hz cycle (166us per interrupt -- be careful!)
    TA0CTL = TASSEL_2 + ID_0 + MC_1;		//TAS_sel = SCLK, ID_0 = /1, Mode = up count.  Also starts the timer

	// Timer B config
    TB0CCR0 = 24000;						// set up (1/256)s timer
    TB0CTL = TBSSEL_2 + ID_1 + MC_1;		//TAS_sel = SCLK, ID_1 = 0x01 = /2, Mode = up count;  Also starts the timer

	// Enable interrupts
    TACTL |= TAIE;
    //TBCTL |= TBIE;
	//TB0CCTL0 |= CCIE;
    //TA0CCTL0 |= CCIE;
}

//This approximates microseconds from 1/100 power cycle ticks.
void us_delay( unsigned long microseconds )
{
	unsigned int num_ticks;
	//1 tick == 166.6 uS
	num_ticks = ( microseconds * 6 ) / 1000;
	count_A0 = 0;
	while( count_A0 < num_ticks );
}

//ms_delay waits a stricter 1ms per input count.
//It is a SW delay so it is still not perfect.
void ms_delay(unsigned int howlong)
{
  unsigned int ms_count;
  ms_count = 0;
  while( ms_count < howlong )
  {
	  //clear counter, wait 6 counts
	  count_A0 = 0;
	  while( count_A0 < 6 );  // wait 1 ms
	  ms_count++;
  }
  
  return;
}

#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA1_isr(void)
{
	TAIV = 0x00;
	count_A0++;

}

#pragma vector = TIMERB1_VECTOR
__interrupt void timerB1_isr(void)
{
	TBIV = 0x00;
	count_B0++;

}
