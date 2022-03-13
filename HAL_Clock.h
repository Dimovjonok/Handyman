/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 08.01.2020
Release: 13.03.2022
class HAL_Clock
*/

#ifndef _HAL_CLOCK_H
#define _HAL_CLOCK_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_HAL_CLOCK
#endif

#include <Arduino.h>
#include <avr/pgmspace.h>


class HAL_Clock {
  friend class Time;
  private:
    HAL_Clock();
    static unsigned long GetMilli();
    static unsigned long GetMicro();
    static void DelayMicro(unsigned int delay);
    HAL_Clock(const HAL_Clock& clock);
    const HAL_Clock& operator=(const HAL_Clock& clock);
};

unsigned long HAL_Clock::GetMilli(){
  return millis();
}

unsigned long HAL_Clock::GetMicro(){
  return micros();
}

void HAL_Clock::DelayMicro(unsigned int delay){
  delayMicroseconds(delay);
}

HAL_Clock::HAL_Clock(){}
HAL_Clock::HAL_Clock(const HAL_Clock& clock){}
const HAL_Clock& HAL_Clock::operator=(const HAL_Clock& clock){}

#endif
