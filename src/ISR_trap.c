// This file is used to provide an out for spurious interrupts.  Without, calling
// an unspecified interrupt may lead to the next successive interrupt vector sending
// the pc to the associated ISR.
//
// Use the global trap_isr_count to quantify how shitty your interrupts are configured.
//
// use "extern int trap_isr_count;" in tender functions if required -- use clear rather
#include "msp430f47177.h"
#include "ISR_trap.h"

int trap_isr_count;

// trap clear function.
//
// Call to clear.  Probably should during interrupt init.
// Returns number of trapped interrupt calls from last clear
int trap_isr_count_clear( void )
{
  int return_value;
  return_value = trap_isr_count;
  trap_isr_count = 0;
  
  return return_value;
  
}

// Trap isr assignation - put all unused ISR vector here
// Vectors are from MSP430F47177.h
//
// The commented section includes ALL vectors for reference.

//#pragma vector = \
DMA_VECTOR\
, BASICTIMER_VECTOR\
, PORT2_VECTOR\
, USCIAB1TX_VECTOR\
, USCIAB1RX_VECTOR\
, PORT1_VECTOR\
, TIMERA1_VECTOR\
, TIMERA0_VECTOR\
, SD16A_VECTOR\
, USCIAB0TX_VECTOR\
, USCIAB0RX_VECTOR\
, WDT_VECTOR\
, COMPARATORA_VECTOR\
, TIMERB1_VECTOR\
, TIMERB0_VECTOR\
, NMI_VECTOR\
, RESET_VECTOR

#pragma vector = \
DMA_VECTOR\
, BASICTIMER_VECTOR\
, PORT2_VECTOR\
, USCIAB1TX_VECTOR\
, USCIAB1RX_VECTOR\
, PORT1_VECTOR\
, TIMERA0_VECTOR\
, SD16A_VECTOR\
, WDT_VECTOR\
, COMPARATORA_VECTOR\
, TIMERB0_VECTOR\
, RESET_VECTOR
__interrupt void TrapIsr( void )
{
  //Deal with it.
  trap_isr_count++;
  
}
