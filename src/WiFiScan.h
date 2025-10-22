// ============================================
// WiFiScan.h CORRIGIDO COMPLETO
// ============================================

#ifndef WIFISCAN_H
#define WIFISCAN_H

// Includes necessários
#include <Arduino.h>
#include <esp_wifi.h> // Adicionado para definições da API WiFi
#include <WiFi.h>
#include <vector>
#include <NimBLEDevice.h>
#include <NimBLEAdvertisedDevice.h>
// #include <ArduinoJson.h> // Adicionado
#include "configs.h"
#include "utils.h"
#include "settings.h"
#include "Assets.h"

#ifdef HAS_BT
  #include "esp_bt.h"
#endif

#ifdef HAS_SCREEN
  #include "Display.h"
#endif

#ifdef HAS_SD
  #include "SDInterface.h"
#endif

#include "Buffer.h"

#ifdef HAS_BATTERY
  #include "BatteryInterface.h"
#endif

#ifdef HAS_GPS
  #include "GpsInterface.h"
#endif

#ifdef MARAUDER_FLIPPER
  #include "flipperLED.h"
#elif defined(MARAUDER_V4)
  #include "flipperLED.h"
#elif defined(XIAO_ESP32_S3)
  #include "xiaoLED.h"
#elif defined(MARAUDER_M5STICKC)
  #include "stickcLED.h"
#else
  #include "LedInterface.h"
#endif

// ===== CLASS WiFiScan =====
class WiFiScan {
public:
  // Definições de structs aninhadas para evitar redefinições
  struct SSID {
    String essid;
    uint8_t bssid[6];
    int channel;
    bool selected;
  };

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

  struct AirTag {
      String mac;                  // MAC address of the AirTag
      std::vector<uint8_t> payload; // Payload data
      uint16_t payloadSize;
      bool selected;
  };

  struct Flipper {
    String mac;
    String name;
  };

  // Membros públicos
  int currentScanMode;
  int set_channel; // Manter esta declaração

  // Métodos públicos
  WiFiScan();
  void RunSetup();
  void main(uint32_t currentTime);

  // Stuff for RAW stats
  uint32_t mgmt_frames = 0;
  uint32_t data_frames = 0;
  uint32_t beacon_frames = 0;
  uint32_t req_frames = 0;
  uint32_t resp_frames = 0;
  uint32_t deauth_frames = 0;
  uint32_t eapol_frames = 0;
  int8_t min_rssi = 0;
  int8_t max_rssi = -128;

  String analyzer_name_string = "";

  uint8_t analyzer_frames_recvd = 0;

  bool analyzer_name_update = false;

  uint8_t old_channel = 0;

  int16_t _analyzer_value = 0;

  bool orient_display = false;
  bool wifi_initialized = false;
  bool ble_initialized = false;

  String free_ram = "";
  String old_free_ram = "";
  String connected_network = "";

  String dst_mac = "ff:ff:ff:ff:ff:ff";
  byte src_mac[6] = {};

  #ifdef HAS_SCREEN
    int16_t _analyzer_values[TFT_WIDTH];
    int16_t _temp_analyzer_values[TFT_WIDTH];
  #endif

  String current_mini_kb_ssid = "";

  const String alfa = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789-=[];',./`\\_+{}:\"<>?~|!@#$%^&*()";

  wifi_config_t ap_config;

  #ifdef HAS_SCREEN
    int8_t checkAnalyzerButtons(uint32_t currentTime);
  #endif

  void StartScan(uint8_t scan_mode, uint16_t color = 0);
  void StopScan(uint8_t scan_mode);
  void setBaseMacAddress(uint8_t macAddr[6]);
  void RunClearAPs(); // Manter esta (linha ~162)
  void RunClearSSIDs(); // Manter esta (linha ~163)
  void RunClearStations(); // Manter esta (linha ~164)
  void RunAPInfo(uint16_t index, bool do_display = true);
  void getMAC(char* addr, uint8_t* data, uint16_t offset);
  bool scanning();
  String getStaMAC();
  String getApMAC();
  String freeRAM();
  void changeChannel();
  void changeChannel(int chan);
  void RunInfo();
  void RunSetMac(uint8_t * mac, bool ap = true);
  void RunGenerateRandomMac(bool ap = true);
  void RunGenerateSSIDs(int count = 20);
  void runSaveSSIDList(bool save_as = true);
  void RunLoadSSIDList();
  void RunSaveAPList(bool save_as = true);
  void RunLoadAPList();
  void RunSaveATList(bool save_as = true);
  void RunLoadATList();
  void channelHop();
  void runMain(uint32_t currentTime);

  bool save_serial = false;
  void startPcap(String file_name);
  void startLog(String file_name);

  static void pwnSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void beaconSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void rawSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void stationSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void apSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void apSnifferCallbackFull(void* buf, wifi_promiscuous_pkt_type_t type);
  static void deauthSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void probeSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void beaconListSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void activeEapolSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void eapolSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
  static void wifiSnifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);

private:
  // Wardriver thanks to https://github.com/JosephHewitt
  struct mac_addr mac_history[100];

  uint8_t ap_mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  uint8_t sta_mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

  // Settings
  uint mac_history_cursor = 0;
  uint8_t channel_hop_delay = 1;
  bool force_pmkid = false;
  bool force_probe = false;
  bool save_pcap = false;

  int x_pos; //position along the graph x axis
  float y_pos_x; //current graph y axis position of X value
  float y_pos_x_old = 120; //old y axis position of X value
  float y_pos_y; //current graph y axis position of Y value
  float y_pos_y_old = 120; //old y axis position of Y value
  float y_pos_z; //current graph y axis position of Z value
  float y_pos_z_old = 120; //old y axis position of Z value
  int midway = 0;
  byte x_scale = 1; //scale of graph x axis, controlled by touchscreen buttons
  byte y_scale = 1;

  bool do_break = false;

  bool wsl_bypass_enabled = false;

  uint32_t initTime = 0;
  bool run_setup = true;
  void initWiFi(uint8_t scan_mode);
  uint8_t bluetoothScanTime = 5;
  int packets_sent = 0;
  const wifi_promiscuous_filter_t filt = {.filter_mask=WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA}; // Corrigido PROMISC -> PROMIS
  #ifdef HAS_BT
    NimBLEScan* pBLEScan;
  #endif

  const char* rick_roll[8] = {
    "01 Never gonna give you up",
    "02 Never gonna let you down",
    "03 Never gonna run around",
    "04 and desert you",
    "05 Never gonna make you cry",
    "06 Never gonna say goodbye",
    "07 Never gonna tell a lie",
    "08 and hurt you"
  };

  const char* prefix = "G";

  // wifi_init_config_t cfg2 = {       .event_handler = &esp_event_send_internal,       .osi_funcs = &g_wifi_osi_funcs,       .wpa_crypto_funcs = g_wifi_default_wpa_crypto_funcs,       .static_rx_buf_num = 6,      .dynamic_rx_buf_num = 6,      .tx_buf_type = 0,      .static_tx_buf_num = 1,      .dynamic_tx_buf_num = WIFI_DYNAMIC_TX_BUFFER_NUM,      .cache_tx_buf_num = 0,      .csi_enable = false,      .ampdu_rx_enable = false,      .ampdu_tx_enable = false,      .amsdu_tx_enable = false,      .nvs_enable = false,      .nano_enable = WIFI_NANO_FORMAT_ENABLED,      .rx_ba_win = 6,      .wifi_task_core = 0 }; // COMENTAR ESTA LINHA (linha ~259)
};

#endif // WIFISCAN_H
