// ButtonPinRecorder.h
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ArduinoSTL.h>

#include "Updateable.h"

class ButtonPinRecorder: public Updateable {
  public:
    ButtonPinRecorder();
    ButtonPinRecorder( uint16_t recordingDuration);
    ButtonPinRecorder( uint16_t recordingDuration, uint8_t numRecordedButtonPinsMin, uint8_t numRecordedButtonPinsMax);

    void update(unsigned long runtime);
    
    bool hasFinished();
    std::vector<uint8_t> getRecordedButtonPins();

  private:
    void addPin( uint8_t pin);

    unsigned long recordingStartTime = 0;
    uint16_t recordingDuration;
    uint8_t numRecordedButtonPinsMin;
    uint8_t numRecordedButtonPinsMax;
    
    std::vector<uint8_t> recordedButtonPins;
    bool finished = false;
    uint8_t recordableButtonPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9};
};