#include "GpsInterface.h"

#ifdef HAS_GPS

GpsInterface::GpsInterface(HardwareSerial* serial) {
  _gps_serial = serial;
}

void GpsInterface::begin() {
  _gps_serial->begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Módulo GPS inicializado.");
}

void GpsInterface::main() {
  while (_gps_serial->available() > 0) {
    gps.encode(_gps_serial->read());
  }
}

int GpsInterface::getNumSats() {
  if (gps.satellites.isValid()) {
    return gps.satellites.value();
  }
  return 0;
}

bool GpsInterface::getFixStatus() {
  return gps.location.isValid() && gps.satellites.value() > 0;
}

String GpsInterface::getLat() {
  if (gps.location.isValid()) {
    return String(gps.location.lat(), 6);
  }
  return "N/A";
}

String GpsInterface::getLon() {
  if (gps.location.isValid()) {
    return String(gps.location.lng(), 6);
  }
  return "N/A";
}

String GpsInterface::getAlt() {
  if (gps.altitude.isValid()) {
    return String(gps.altitude.meters()) + " m";
  }
  return "N/A";
}

String GpsInterface::getSpeed() {
  if (gps.speed.isValid()) {
    return String(gps.speed.kmph()) + " km/h";
  }
  return "N/A";
}

String GpsInterface::getCourse() {
  if (gps.course.isValid()) {
    return String(gps.course.deg());
  }
  return "N/A";
}

String GpsInterface::getDatetime() {
  if (gps.date.isValid() && gps.time.isValid()) {
    String dateStr = "";
    dateStr += String(gps.date.year());
    dateStr += "-";
    if (gps.date.month() < 10) dateStr += "0";
    dateStr += String(gps.date.month());
    dateStr += "-";
    if (gps.date.day() < 10) dateStr += "0";
    dateStr += String(gps.date.day());

    String timeStr = "";
    if (gps.time.hour() < 10) timeStr += "0";
    timeStr += String(gps.time.hour());
    timeStr += ":";
    if (gps.time.minute() < 10) timeStr += "0";
    timeStr += String(gps.time.minute());
    timeStr += ":";
    if (gps.time.second() < 10) timeStr += "0";
    timeStr += String(gps.time.second());

    return dateStr + " " + timeStr;
  }
  return "No GPS Time";
}

#endif