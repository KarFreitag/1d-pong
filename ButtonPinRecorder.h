// ButtonPinRecorder.h
#ifndef BUTTONPINRECORDER_H
#define BUTTONPINRECORDER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class ButtonPinRecorder {
  public:
    ButtonPinRecorder();
    ButtonPinRecorder( uint16_t recordingDuration);
    ButtonPinRecorder( uint16_t recordingDuration, uint8_t numRecordedButtonPinsMin, uint8_t numRecordedButtonPinsMax);
    bool loop();
    uint8_t getNumRecordedButtonPins();
    void getRecordedButtonPins( uint8_t * recordedButtonPins);

  private:
    void addPin( uint8_t pin);

    unsigned long recordingStartTime = 0;
    uint16_t recordingDuration;

    uint8_t numRecordedButtonPins = 0;
    uint8_t numRecordedButtonPinsMin;
    uint8_t numRecordedButtonPinsMax;
    
    uint8_t recordedButtonPins[6];
    uint8_t recordableButtonPins[6] = { 2, 3, 4, 5, 8, 9};
};

#endif
