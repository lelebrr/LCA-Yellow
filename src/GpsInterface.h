#pragma once

#ifndef GpsInterface_h
#define GpsInterface_h

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "configs.h"

class GpsInterface {
  public:
    GpsInterface(HardwareSerial* serial);
    void begin();
    void main();

    int getNumSats();
    String getNumSatsString();
    bool getFixStatus();
    String getFixStatusAsString();
    int getGpsModuleStatus();
    String getLat();
    String getAccuracy();
    String getLon();
    String getAlt();
    String getSpeed();
    String getCourse();
    String getDatetime();
    String getText();
    String getNmea();
    String getNmeaNotimp();
    String getNmeaNotparsed();

    void sendSentence(String sentence);
    String generateGXgga();
    String generateGXrmc();
    void setType(int type);
  private:
    HardwareSerial* _gps_serial;
    TinyGPSPlus gps;
};

extern GpsInterface gps_obj;

#endif