/*
Dmitry Lebedev (Dimovjonok) dmitrylebedev@mail.ru
Create: 28.08.2021
Release: 14.03.2022
*/

/*
Доработать класс Pin для работы с аналоговыми выводами
 */


#ifndef _PIN_H
#define _PIN_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_PIN
#endif

#include "HAL_Board.h"


class Pin {
  public:
    Pin();
    Pin(NumberOfPin id);
    Pin(NumberOfPin id, DirectOfPin direct);
    Pin(NumberOfPin id, TypeOfPin type);
    Pin(NumberOfPin id, TypeOfPin type, DirectOfPin direct);
    void levelToHigh();
    void levelToLow();
    void toggleLevel();
    bool getLevel();  // used class HAL
    void putLevel(bool level);  // used class HAL
  private:
    NumberOfPin id;
    TypeOfPin type;
    DirectOfPin direct;
    bool level;
    uint8_t mcuPort;
    uint8_t mcuLine;
    NumberOfPin getID();
    void setID(NumberOfPin id);
    TypeOfPin getType();
    void setType(TypeOfPin type);
    DirectOfPin getDirect();
    void setDirect(DirectOfPin direct);
    void init();
    void configDigital(NumberOfPin id, DirectOfPin direct);  // used class HAL
  protected:
};


Pin::Pin(){
  setType(TypeOfPin::Undefined);
  setDirect(DirectOfPin::Undefined);
}

Pin::Pin(NumberOfPin id){
  setID(id);
  setType(TypeOfPin::Digital);
  setDirect(DirectOfPin::Input);
  init();
}

Pin::Pin(NumberOfPin id, DirectOfPin direct){
  setID(id);
  setType(TypeOfPin::Digital);
  setDirect(direct);
  init();
}

Pin::Pin(NumberOfPin id, TypeOfPin type){
  setID(id);
  setType(type);
  setDirect(DirectOfPin::Input);
  init();
}

Pin::Pin(NumberOfPin id, TypeOfPin type, DirectOfPin direct){
  setID(id);
  setType(type);
  setDirect(direct);
  init();
}

void Pin::levelToHigh(){
  if (type == TypeOfPin::Digital && direct == DirectOfPin::Output) putLevel(true);
}

void Pin::levelToLow(){
  if (type == TypeOfPin::Digital && direct == DirectOfPin::Output) putLevel(false);
}

void Pin::toggleLevel(){
  if (type == TypeOfPin::Digital && direct == DirectOfPin::Output)
    (level) ? levelToLow() : levelToHigh();
}

bool Pin::getLevel(){
  if (type == TypeOfPin::Digital && direct == DirectOfPin::Input)
    return HAL_Board::getPinLevel(id);
}

void Pin::putLevel(bool level){
  if (type == TypeOfPin::Digital && direct == DirectOfPin::Output){
    this->level = level;
    HAL_Board::setPinLevel(id,level);
  }
}

NumberOfPin Pin::getID(){
  return id;
}

void Pin::setID(NumberOfPin id){
  this->id = id;
}

TypeOfPin Pin::getType(){
  return type;
}

void Pin::setType(TypeOfPin type){
  this->type = type;
}

DirectOfPin Pin::getDirect(){
  return direct;
}

void Pin::setDirect(DirectOfPin direct){
  this->direct = direct;
}

void Pin::init(){
  switch (type){
    case TypeOfPin::Undefined:{
      break;
    }

    case TypeOfPin::Digital:{
      configDigital(id, direct);
      break;
    }

    case TypeOfPin::Analog:{
      break;
    }
  }
}

void Pin::configDigital(NumberOfPin id, DirectOfPin direct){
  switch (direct){
    case DirectOfPin::Undefined:{
      break;
    }

    case DirectOfPin::Input:{
      HAL_Board::configPinDI(id);
      break;
    }

    case DirectOfPin::Output:{
      HAL_Board::configPinDO(id);
      break;
    }
  }
}

#endif
