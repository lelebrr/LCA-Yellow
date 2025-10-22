#pragma once
#ifndef FeedbackInterface_h
#define FeedbackInterface_h

#include "configs.h"

class FeedbackInterface {
public:
  FeedbackInterface();
  void begin();

  #ifdef HAS_BUZZER_LED
  void buzz(int frequency, int duration);
  void ledOn();
  void ledOff();
  #endif

  #ifdef HAS_SPEAKER
  void playTone(int frequency, int duration);
  #endif
};

#endif
