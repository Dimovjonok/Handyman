/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 12.03.2022
Release:
*/

/*
Основной цикл приложения - не меняется.
 */

#define _MODE_DEBUG
#define _MODE_DEBUG_TOSERIAL

#include "Staffer.h"


Staffer& staffer = Staffer::getInstance();


void setup() {
  	staffer.Prepare();
}

void loop() {
  	// staffer.Sheduler();
  	staffer.Dispatcher();
  	// staffer.Background();
  	// staffer.Scavenger();
}
