#pragma once
#ifndef GestureInterface_h
#define GestureInterface_h

#include "configs.h"

#ifdef HAS_PAJ7620_GESTURE
#include <RevEng_PAJ7620.h>

class GestureInterface {
public:
  GestureInterface();
  void begin();
  void main();
  Gesture getGesture();
  String gestureToString(Gesture gesture);

private:
  RevEng_PAJ7620 paj7620;
  Gesture currentGesture;
};

#endif
#endif
