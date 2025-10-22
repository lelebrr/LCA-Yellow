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
#define WIFI_SCAN_OFF 0
// ... (outras definições de ataque serão adicionadas aqui) ...

#define BUF_SIZE 2048
#define SNAP_LEN 68

#endif // configs_h
