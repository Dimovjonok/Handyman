/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 08.01.2020
Release:
class Action
*/

#ifndef _ACTION_H
#define _ACTION_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_ACTION
#endif


#include "Time.h"


/*
!!! Включить описание всех возможных действий, которые способна выполнить конкретная система
(статические типизированные константы)

Ввести свойство bool completed  для определения статуса действия (выполняется/завершено)
(может не bool, а более развернуто - status ожидание/выполняется/завершено и т.п.)
Потребуется для сборщика мусора, который будет очищать очередь заданий
 */


const uint8_t ACTION_MaxNumber PROGMEM = 10;
const uint8_t ACTION_NotAssigned PROGMEM = -1;
const uint8_t ACTION_NotAvailable PROGMEM = -2;

enum class TypeOfAction: uint8_t {
  Empty = 0,
  EveryTime
};

typedef int CountOfRepeatAction;
typedef uint8_t NumberOfAction;
typedef void (*Actor)();


class Action {
  public:
    Action();
    void Update();
    void Update(TimeInMilli currentTime);
    Actor actor; //void (*callback)();
    TypeOfAction type;
    CountOfRepeatAction count;
    CountOfRepeatAction countMax;
    TimeInMilli period;
    TimeInMilli previousTime;
    // bool completed
  // private:
    TimeInMilli CurrentTime();
  protected:
    TimeInMicro CurrentMoment();
};


Action::Action(){
  type = TypeOfAction::Empty;
}

void Action::Update(){
  Update(CurrentTime());
}

void Action::Update(TimeInMilli currentTime){
  if (currentTime - previousTime >= period){
    switch (type){
      case TypeOfAction::EveryTime:{
        (*actor)();
        break;
      }
    }
    previousTime = currentTime;
    count++;
  }
  if (countMax > -1 && count >= countMax){
    type = TypeOfAction::Empty;
  }
}

TimeInMilli Action::CurrentTime(){
  return Time::CurrentMilli();
}

TimeInMicro Action::CurrentMoment(){
  return Time::CurrentMicro();
}

#endif
