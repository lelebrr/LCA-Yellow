#pragma once
#ifndef TempInterface_h
#define TempInterface_h

#include <OneWire.h>
#include <DallasTemperature.h>
#include "configs.h"

class TempInterface {
public:
  TempInterface();
  void begin();
  void main();
  float getTempC();

private:
  OneWire* oneWire;
  DallasTemperature* sensors;
  float currentTempC;
};

#endif
