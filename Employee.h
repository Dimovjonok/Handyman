/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 08.01.2020
Release:
class Employee
*/

/*
Базовый класс для Staffer - реализация общего для всех приложений функционала
Данный класс не может использоваться как главные класс приложения (нельзя создать экземпляр этого класса).
Поэтому он реализован как абстрактный класс (некоторые методы оставлены без реализаций и помечены модификатором virtual).

 */

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_EMPLOYEE
#endif

#include "Action.h"


class Employee {
  public:
    void Prepare();
    void Sheduler();
    virtual void Dispatcher() = 0;
    // void Scavenger();
    // void Background();
    NumberOfAction ActionRepeatEveryTime(TimeInMilli period, void (*actor)(), CountOfRepeatAction countMax);
    NumberOfAction ActionRepeatAlways(TimeInMilli period, void (*actor)());
    NumberOfAction ActionRepeatOnce(TimeInMilli period, void (*actor)());
  protected:
    Employee();
  private:
    void Sheduler(TimeInMilli currentTime);
    NumberOfAction ActionAdd(TypeOfAction type, TimeInMilli period, void (*actor)(), CountOfRepeatAction countMax);
    NumberOfAction ActionAllocateSpace();
    Action action[ACTION_MaxNumber];
    TimeInMilli CurrentTime();
	Employee(const Employee& employee);
	const Employee& operator=(const Employee& employee);
};

void Employee::Prepare(){}

void Employee::Sheduler(){
  for (NumberOfAction i = 0; i < ACTION_MaxNumber; i++){
    if (action[i].type != TypeOfAction::Empty){
      action[i].Update();
    }
  }
}

void Employee::Sheduler(TimeInMilli currentTime) {
  for (NumberOfAction i = 0; i < ACTION_MaxNumber; i++){
    if (action[i].type != TypeOfAction::Empty){
      action[i].Update(currentTime);
    }
  }
}

// void Employee::Scavenger(){}

// void Employee::Background(){}

NumberOfAction Employee::ActionRepeatEveryTime(TimeInMilli period, void (*actor)(), CountOfRepeatAction countMax){
  return ActionAdd(TypeOfAction::EveryTime, period, actor, countMax);
}

NumberOfAction Employee::ActionRepeatAlways(TimeInMilli period, void (*actor)()){
  return ActionAdd(TypeOfAction::EveryTime, period, actor, -1);
}

NumberOfAction Employee::ActionRepeatOnce(TimeInMilli period, void (*actor)()){
  return ActionAdd(TypeOfAction::EveryTime, period, actor, 1);
}

NumberOfAction Employee::ActionAdd(TypeOfAction type, TimeInMilli period, void (*actor)(), CountOfRepeatAction countMax){
  NumberOfAction i = ActionAllocateSpace();
  if (i != -1){
    action[i].type = type;
    action[i].period = period;
    action[i].count = 0;
    action[i].countMax = countMax;
    action[i].previousTime = CurrentTime();
    action[i].actor = actor;
    return i;
  } else return -1;
}

NumberOfAction Employee::ActionAllocateSpace(){
  for (NumberOfAction i = 0; i < ACTION_MaxNumber; i++){
    if (action[i].type == TypeOfAction::Empty){
      return i;
    }
  }
  return ACTION_NotAvailable;
}

TimeInMilli Employee::CurrentTime(){
  return Time::CurrentMilli();
}

Employee::Employee(){};
Employee::Employee(const Employee& employee){};
const Employee& Employee::operator=(const Employee& employee){};

#endif
