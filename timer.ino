#include "TimerUtils.h"
#include "Scheduler.h"

volatile int invt = 0;
void ISR_CALLBACK()
{
    invt = !invt;
    digitalWrite(13, invt);
}

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{  
    callback = Scheduler_TicksCounter;
    TimerUtils_initTimer();
    Scheduler_Dispacther();
}
