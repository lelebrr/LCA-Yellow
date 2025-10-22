#ifndef WIFISCAN_H
#define WIFISCAN_H

#include <Arduino.h>
#include <WiFi.h>
#include <vector>
#include <NimBLEDevice.h>
#include <NimBLEAdvertisedDevice.h>
#include "configs.h"

// ===== FORWARD DECLARATIONS =====
// Declarar structs ANTES da classe WiFiScan

// STRUCT SSID
struct ssid {
  String essid;
  uint8_t bssid[6];
  int channel;
  bool selected;
};

// STRUCT ACCESS POINT
struct AccessPoint {
  String essid;
  uint8_t bssid[6];
  int rssi;
  int channel;
  bool selected;
  std::vector<int>* stations;
  uint8_t sec;
  uint16_t wps;
  uint32_t packets;
  String man;
};

// STRUCT STATION
struct Station {
  uint8_t mac[6];
  bool selected;
};

// STRUCT AIRTAG
struct AirTag {
  String mac;
  std::vector<uint8_t> payload;
  uint16_t payloadSize;
  bool selected;
};

// STRUCT FLIPPER
struct Flipper {
  String mac;
  String name;
};

// ===== CLASSE WIFISCAN =====
class WiFiScan {
public:
  // Alias para compatibilidade
  typedef ssid SSID;

  // Construtor
  WiFiScan();

  // Membros públicos
  int currentScanMode;
  int set_channel;

  // Métodos principais
  void RunSetup();
  void main(uint32_t currentTime);
  void StartScan(uint8_t scan_mode, uint16_t color = 0);
  void StopScan(uint8_t scan_mode);
  void RunClearAPs();
  void RunClearSSIDs();
  void RunClearStations();
  void RunAPInfo(uint16_t index, bool do_display = true);
  void getMAC(char* addr, uint8_t* data, uint16_t offset);
  bool scanning();
  void changeChannel();
  void changeChannel(int chan);
  void channelHop();
  // Outros métodos (adicione conforme necessário)
  // ...
private:
  // Membros privados
  // ...
};

#endif // WIFISCAN_H
