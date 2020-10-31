#ifndef _TIMER_UTILS_H_
#define _TIMER_UTILS_H_

#define TIME_MS 0.500

void (*callback)();

void TimerUtils_initTimer(void);
ISR(TIMER1_COMPA_vect);    // Timer1 ISR

#endif