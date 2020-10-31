#include "TimerUtils.h"
#include<avr/io.h>
#include<avr/interrupt.h>


#define FREQ 1000/(TIME_MS)
#define CPU_F 16000000
#define INTERRUPT_VALUE (CPU_F / (1 * FREQ) - 1)

volatile unsigned int counter = 0;

ISR(TIMER1_COMPA_vect)    // Timer1 ISR
{
    //TCNT1 = INTERRUPT_VALUE;   // for 1 sec at 16 MHz
    counter++;
    if (counter >= (TIME_MS * 1000))
    {
        callback();
        counter = 0;
    }
}

void TimerUtils_initTimer(void)
{
    // TIMER 1 for interrupt frequency 1000 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0; // initialize counter value to 0
    // set compare match register for 1000 Hz increments
    OCR1A = INTERRUPT_VALUE; // = 16000000 / (1 * 1000) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1(No prescaler) prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts
}