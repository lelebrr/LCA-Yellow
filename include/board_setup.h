#ifndef BOARD_SETUP_H
#define BOARD_SETUP_H

// ============================================================================
// board_setup.h para ESP32-3248S035R (CYD 3.5" Resistivo)
// Projeto: LCA-Yellow
// Data: 2025-10-22
// ============================================================================

// ===== Definições de Pinos =====
// Display ST7796
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1  // Reset não usado
#define TFT_BL   21  // Backlight

// Touch XPT2046
#define TOUCH_CS 33

// SD Card (se usado)
#define SD_CS 5

// Outros pinos (se usados)
// ... adicione outros pinos conforme necessário ...

// ===== Configurações de Hardware =====
// Frequência do CPU
#define CPU_FREQUENCY 240000000L

// Frequência da Flash
#define FLASH_FREQUENCY 80000000L

// Tamanho da PSRAM
#define PSRAM_SIZE 4194304 // 4MB

// Tamanho da Flash
#define FLASH_SIZE 16777216 // 16MB

// ===== Configurações LVGL =====
#define LV_HOR_RES_MAX 320
#define LV_VER_RES_MAX 480

// ===== Configurações Adicionais do Display =====
#define ST7796_VSCRDEF 0x33  // Define para VSCRDEF
#define ST7796_VSCRSADD 0x37 // Define para VSCRSADD
#define TFT_INVERSION_ON
#define TFT_RGB_ORDER TFT_BGR

#endif // BOARD_SETUP_H
