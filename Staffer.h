/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 08.01.2020
Release:
class Staffer
*/

/*
Основной класс приложения - сотрудник, выполняющий конкретные обязанности
Реализован как Singleton - данная сущность реализуется в единственном экземпляре
 */

#ifndef _STAFFER_H
#define _STAFFER_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_STAFFER
#endif


#include "Employee.h"
#include "Pin.h"	// Только на время тестирования


class Staffer : public Employee {
	public:
		static Staffer& getInstance();
    	void Prepare();
		void Dispatcher();
	protected:
  	private:
		Staffer();
      	Pin* ledBuiltin;
      	Pin* pinSwitchNo;
      	Pin* pinSwitchNc;
		boolean switchStateNo = false;
		boolean switchStateNc = false;
		boolean changedSwitchState(boolean noState, boolean ncState);
		boolean setLedCurrentState();
};


Staffer::Staffer():Employee(){}

Staffer& Staffer::getInstance() {
	static Staffer instance;
	return instance;
}

void Staffer::Prepare(){
	Serial.begin(115200);
  	Serial.println("Main setup()");

  	ledBuiltin = new Pin(HAL_LedBuiltin,TypeOfPin::Digital, DirectOfPin::Output);
  	pinSwitchNo = new Pin(HAL_PinSwitchNo,TypeOfPin::Digital, DirectOfPin::Input);
  	pinSwitchNc = new Pin(HAL_PinSwitchNc,TypeOfPin::Digital, DirectOfPin::Input);

  	switchStateNo = pinSwitchNo->getLevel();
  	Serial.println(switchStateNo);

    switchStateNc = pinSwitchNc->getLevel();
    Serial.println(switchStateNc);

    ledBuiltin->putLevel(switchStateNo);
}

void Staffer::Dispatcher() {
	if(changedSwitchState(pinSwitchNo->getLevel(), pinSwitchNc->getLevel())) {
		Serial.println("Staffer::Dispatcher() - changedSwitchState");
		if(switchStateNo & !switchStateNc || !switchStateNo && switchStateNc) {
			ledBuiltin->putLevel(setLedCurrentState());
			Serial.println("Switch state changed");
		} else {
			Serial.println("Undefined switch state");
		}
	}
}

boolean Staffer::changedSwitchState(boolean noState, boolean ncState) {
    boolean result = false;
    if(switchStateNo != noState && switchStateNc != ncState) {
        switchStateNo = noState;
        switchStateNc = ncState;
        result = true;
    }
    return result;
}

boolean Staffer::setLedCurrentState() {
    return switchStateNo & !switchStateNc;
}

#endif
