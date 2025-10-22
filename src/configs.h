#pragma once
#ifndef configs_h
#define configs_h

#define LCA_VERSION "v2.0-Alpha-Recovery"

// =================================================================================================
// == Definições da Placa e Hardware Principal
// =================================================================================================
#define LCA_CYD_S3 // Identificador único para a placa ESP32-3248S035R (ESP32-S3)
#define HARDWARE_NAME "LCA Toolkit (ESP32-S3)"

// =================================================================================================
// == Ativação de Módulos e Funcionalidades
// =================================================================================================
#define HAS_SCREEN
#define HAS_SD          // Ativa o SD Card principal (on-board)
#define HAS_BT

// --- Módulos Externos Ativados ---
#define HAS_SD_2                // Segundo SD Card (externo)
#define HAS_CC1101              // Módulos de Rádio Sub-GHz
#define HAS_NRF24               // Módulo 2.4GHz
#define HAS_PN532               // Leitor/Escritor NFC
#define HAS_GPS                 // Módulo GPS
#define HAS_PAJ7620_GESTURE     // Sensor de Gestos
#define HAS_DS18B20_TEMP        // Sensor de Temperatura
#define HAS_IR_TRANSMITTER      // Transmissor Infravermelho
#define HAS_BUZZER_LED          // Buzzer e/ou LED para feedback
#define HAS_SPEAKER             // Alto-falante para áudio
#define HAS_BATTERY             // Monitoramento de Bateria

// =================================================================================================
// == Mapeamento de Pinos (Pinout) - FINAL E CORRIGIDO
// =================================================================================================
#ifdef LCA_CYD_S3
  // --- Barramento I2C (Compartilhado com Touch On-Board) ---
  #define I2C_SDA 9
  #define I2C_SCL 10

  // --- Barramento SPI (Compartilhado) ---
  #define SPI_MISO 18
  #define SPI_MOSI 13
  #define SPI_SCK 14

  // --- Pinos de Chip Select (CS) para dispositivos SPI ---
  #define SD_CS 41          // SD Card 1 (On-board)
  #define SD2_CS 21         // SD Card 2 (Externo)
  #define CC1101_CS1 19     // CC1101 Módulo 1
  #define CC1101_CS2 20     // CC1101 Módulo 2
  #define NRF24_CS 33       // NRF24L01

  // --- Pinos de Módulos Específicos ---
  #define NRF24_CE 15         // NRF24L01 Chip Enable
  #define NRF24_CE_PIN NRF24_CE
  #define NRF24_CSN_PIN NRF24_CS
  #define IR_TX_PIN 35        // Transmissor IR
  #define DS18B20_PIN 16      // Sensor de Temperatura DS18B20 (One-Wire)
  #define BUZZER_LED_PIN 3    // Buzzer/LED para feedback
  #define SPEAKER_PIN 17      // Speaker (usando DAC Canal 1)

  // --- Pinos do GPS (UART2) ---
  #define GPS_TX 36           // Conectar ao RX do GPS
  #define GPS_RX 37           // Conectar ao TX do GPS
  #define GPS_SERIAL_INDEX 2  // Usando a Serial2 do ESP32
#endif

// --- Definições de Pinos para Hardware Específico (Ex: Flipper) ---
#ifdef MARAUDER_FLIPPER
 #define B_PIN 26  // Blue LED
 #define G_PIN 14  // Green LED
 #define R_PIN 12  // Red LED
#endif

// =================================================================================================
// == Configurações do Display
// =================================================================================================
#ifdef HAS_SCREEN
  #include "User_Setup.h"
#include <TFT_eSPI.h>
  
  #define SCREEN_WIDTH 320 // Alterado para uint16_t para evitar overflow
  #define SCREEN_HEIGHT 480 // Alterado para uint16_t para evitar overflow
  #define BANNER_TEXT_SIZE 2
  #define MENU_FONT &FreeMono9pt7b
  #define BUTTON_ARRAY_LEN 15
  #define YMAX SCREEN_HEIGHT
  #define BOT_FIXED_AREA 60
  #define TEXT_HEIGHT 16
  #define TOUCH_CS -1 // Definido como -1 (ou outro pino não utilizado) para touch I2C
#endif

// =================================================================================================
// == Definições de Ataques e Modos (Serão expandidos)
// =================================================================================================
// ===== SCAN MODES =====
#define WIFI_SCAN_OFF                     0
#define WIFI_SCAN_PROBE                   1
#define WIFI_SCAN_AP                      2
#define WIFI_SCAN_PWN                     3
#define WIFI_SCAN_ESPRESSIF               4
#define WIFI_SCAN_ALL                     5
#define WIFI_SCAN_DEAUTH                  6
#define WIFI_SCAN_TARGET_AP               7
#define WIFI_SCAN_TARGET_AP_FULL          8
#define WIFI_SCAN_AP_STA                  9
#define WIFI_SCAN_STATION                 10
#define WIFI_SCAN_RAW_CAPTURE             11
#define WIFI_SCAN_STATION_WAR_DRIVE       12
#define WIFI_SCAN_WAR_DRIVE               13
#define WIFI_SCAN_SIG_STREN               14
#define WIFI_SCAN_PACKET_RATE             15
#define WIFI_SCAN_EAPOL                   16
#define WIFI_SCAN_ACTIVE_EAPOL            17
#define WIFI_SCAN_ACTIVE_LIST_EAPOL       18
#define WIFI_SCAN_EVIL_PORTAL             19
#define WIFI_SCAN_GPS_DATA                20
#define WIFI_SCAN_GPS_NMEA                21
#define WIFI_SCAN_CHAN_ANALYZER           22
// Ataques WiFi
#define WIFI_ATTACK_BEACON_SPAM           50
#define WIFI_ATTACK_AUTH                  51
#define WIFI_ATTACK_DEAUTH                52
#define WIFI_ATTACK_AP_SPAM               53
#define WIFI_ATTACK_RICK_ROLL             54
// Bluetooth
#define BT_SCAN_ALL                       100
#define BT_SCAN_SKIMMERS                  101
#define BT_SCAN_ANALYZER                  102
#define BT_ATTACK_SPAM_MAGSAFE            110
#define BT_ATTACK_SPAM_IOS17              111
#define BT_ATTACK_SPAM_SAMSUNG            112
#define BT_ATTACK_SPAM_WIN                113
#define BT_ATTACK_SPAM_ANDROID            114
#define BT_ATTACK_SPAM_ALL                115
#define BT_ATTACK_SOUR_APPLE              116
#define BT_SPOOF_AIRTAG                   117
#define BT_WARDRIVE                       118
// Updates
#define SD_UPDATE                         200
#define ESP_UPDATE                        201
#define WEB_UPDATE                        202
// LVGL
#define LV_ADD_SSID                       300
#define LV_JOIN_WIFI                      301

#define BUF_SIZE 2048
#define SNAP_LEN 68

#endif // configs_h
