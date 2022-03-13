/*
Dmitry Lebedev (DumDumbIch) dumdumbich@gmail.com
Create: 26.02.2022
Release: 13.03.2022
class HAL_Board
*/

#ifndef _HAL_Board_H
#define _HAL_Board_H

#ifdef _MODE_DEBUG
#define _MODE_DEBUG_HAL_Board
#endif

#include <Arduino.h>
#include <avr/pgmspace.h>

// Процессорный модуль
#define _ARDUINO_PRO_MINI
// #define _ARDUINO_MEGA2560
//#define _ARDUINO_DUE

#define ANALOG 0
#define DIGITAL 1


const uint16_t BOARD_ID PROGMEM = 0x0001;

typedef uint8_t PinMode;
typedef uint8_t PinType;
typedef uint8_t BoardPins;
typedef uint8_t NumberOfPin;


#ifdef _ARDUINO_PRO_MINI
	const NumberOfPin HAL_LedBuiltin = {LED_BUILTIN};
	const NumberOfPin HAL_PinSwitchNo = {2};
	const NumberOfPin HAL_PinSwitchNc = {3};
#endif


#ifdef _ARDUINO_MEGA2560

#endif


#ifdef _ARDUINO_DUE

#endif


class HAL_Board {
	friend class Pin;
  private:
    static void configPinDI(BoardPins pin); // Used Arduino library
    static void configPinDO(BoardPins pin); // Used Arduino library
    static bool getPinLevel(BoardPins pin); // Used Arduino library
    static void setPinLevel(BoardPins pin, bool level); // Used Arduino library
    static void pinToHigh(BoardPins pin);
    static void pinToLow(BoardPins pin);
    static bool checkPinConfig(BoardPins pin, PinType type, PinMode mode); // !!! Method not released !!!
    HAL_Board();
    HAL_Board(const HAL_Board& board);
    const HAL_Board& operator=(const HAL_Board& board);
};


void HAL_Board::configPinDI(BoardPins pin){
  if (checkPinConfig(pin,DIGITAL,INPUT)) pinMode(pin, INPUT); // Used Arduino library
}

void HAL_Board::configPinDO(BoardPins pin){
  if (checkPinConfig(pin,DIGITAL,OUTPUT)) pinMode(pin, OUTPUT); // Used Arduino library
}

bool HAL_Board::getPinLevel(BoardPins pin){
  return digitalRead(pin); // Used Arduino library
}

void HAL_Board::setPinLevel(BoardPins pin, bool level){
  digitalWrite(pin, level); // Used Arduino library
}

void HAL_Board::pinToHigh(BoardPins pin){
  setPinLevel(pin, HIGH);
}

void HAL_Board::pinToLow(BoardPins pin){
  setPinLevel(pin, LOW);
}

bool HAL_Board::checkPinConfig(BoardPins pin, PinType type, PinMode mode){
  return true; // It's gag - Replace with the real code
}

HAL_Board::HAL_Board() {}
HAL_Board::HAL_Board(const HAL_Board& board) {}
const HAL_Board& HAL_Board::operator=(const HAL_Board& board){}

#endif
