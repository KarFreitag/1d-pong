
#include "ButtonPinRecorder.h"
#include "Constants.h"

ButtonPinRecorder::ButtonPinRecorder(uint16_t recordingDuration)
    : recordingDuration(recordingDuration),
      numRecordedButtonPinsMin(Const::numPlayersMin),
      numRecordedButtonPinsMax(Const::numPlayersMax) {}

ButtonPinRecorder::ButtonPinRecorder(uint16_t recordingDuration, uint8_t numRecordedButtonPinsMin, uint8_t numRecordedButtonPinsMax)
    : recordingDuration(recordingDuration),
      numRecordedButtonPinsMin(numRecordedButtonPinsMin),
      numRecordedButtonPinsMax(numRecordedButtonPinsMax)
{
}

void ButtonPinRecorder::update(unsigned long runtime)
{
  uint8_t numRecordablePins = sizeof(recordableButtonPins);
  for (uint8_t i = 0; i < numRecordablePins; ++i)
  {
    if (digitalRead(recordableButtonPins[i]) == HIGH)
    {
      addPin(recordableButtonPins[i]);

      // reset recording time
      recordingStartTime = runtime;
    }
  }

  bool timesUp = (runtime - recordingStartTime) > recordingDuration;
  bool minPinsReached = recordedButtonPins.size() >= numRecordedButtonPinsMin;
  bool maxPinsReached = recordedButtonPins.size() >= numRecordedButtonPinsMax;

  finished = maxPinsReached || (minPinsReached && timesUp);
}

bool ButtonPinRecorder::hasFinished() 
{
  return finished;
}

std::vector<uint8_t> ButtonPinRecorder::getRecordedButtonPins()
{
  return recordedButtonPins;
}

void ButtonPinRecorder::addPin(uint8_t pin)
{
  auto foundPinPos = std::find(recordedButtonPins.begin(), recordedButtonPins.end(), pin);

  if (foundPinPos == recordedButtonPins.end())
  {
    recordedButtonPins.push_back(pin);
  }
}
