
#include "ButtonPinRecorder.h"

ButtonPinRecorder::ButtonPinRecorder( uint16_t recordingDuration)
  : recordingDuration( recordingDuration),
    numRecordedButtonPinsMin( 2),
    numRecordedButtonPinsMax( 6) {}


ButtonPinRecorder::ButtonPinRecorder( uint16_t recordingDuration, uint8_t numRecordedButtonPinsMin, uint8_t numRecordedButtonPinsMax)
  : recordingDuration( recordingDuration),
    numRecordedButtonPinsMin( numRecordedButtonPinsMin),
    numRecordedButtonPinsMax( numRecordedButtonPinsMax) {

}

bool ButtonPinRecorder::loop() {
  uint8_t numRecordablePins = sizeof( recordableButtonPins);
  for (uint8_t i = 0; i < numRecordablePins; ++i) {
    if (digitalRead( recordableButtonPins[ i]) == HIGH) {
      addPin( recordableButtonPins[ i]);

      // reset recording time
      recordingStartTime = millis();
    }
  }

  numRecordedButtonPins = min( numRecordedButtonPins, numRecordedButtonPinsMax);
  bool timesUp = (millis() - recordingStartTime) > recordingDuration;
  bool minPinsReached = numRecordedButtonPins >= numRecordedButtonPinsMin;
  bool maxPinsReached = numRecordedButtonPins >= numRecordedButtonPinsMax;

  bool isDone = maxPinsReached || (minPinsReached && timesUp);
  return isDone;
}

uint8_t ButtonPinRecorder::getNumRecordedButtonPins() {
  return numRecordedButtonPins;
}

void ButtonPinRecorder::getRecordedButtonPins( uint8_t * recordedButtonPins) {
  for (int i = 0; i < numRecordedButtonPins; ++i) {
    recordedButtonPins[i] = this->recordedButtonPins[i];
  }
}

void ButtonPinRecorder::addPin( uint8_t pin) {
  bool buttonPinAlreadyRecorded = false;
  for (uint8_t j = 0; j < numRecordedButtonPins; ++j) {
    if (recordedButtonPins[j] == pin) {
      buttonPinAlreadyRecorded = true;
      break;
    }
  }

  if (!buttonPinAlreadyRecorded) {
    recordedButtonPins[ numRecordedButtonPins] = pin;
    ++numRecordedButtonPins;
  }
}

