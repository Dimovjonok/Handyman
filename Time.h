/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 08.01.2020
Release: 13.03.2022
class Time
*/

#ifndef _TIME_H
#define _TIME_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_TIME
#endif

#include "HAL_Clock.h"

typedef unsigned long TimeInMilli;
typedef unsigned long TimeInMicro;

class Time {
  public:
    static TimeInMilli CurrentMilli();
    static TimeInMicro CurrentMicro();
    static void DelayMicro(TimeInMicro delay);
  private:
    Time();
    Time(const Time& time);
    const Time& operator=(const Time& time);
};

TimeInMilli Time::CurrentMilli(){
  return HAL_Clock::GetMilli();
}

TimeInMicro Time::CurrentMicro(){
  return HAL_Clock::GetMicro();
}

static void Time::DelayMicro(TimeInMicro delay){
  HAL_Clock::DelayMicro(delay);
}

Time::Time(){}
Time::Time(const Time& time){}
const Time& Time::operator=(const Time& time){}

#endif
