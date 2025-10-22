// ============================================================================
// User_Setup.h CORRIGIDO para ESP32-3248S035R (CYD 3.5" Resistivo)
// Driver: ST7796
// Resolução: 480x320
// Touch: XPT2046 (Resistivo)
// Projeto: LCA-Yellow
// Data: 2025-10-22
// ============================================================================

#ifndef USER_SETUP_H
#define USER_SETUP_H

// ===== Driver do Display =====
#define ST7796_DRIVER      // Driver ST7796 para display 3.5"

// ===== Resolução =====
#define TFT_WIDTH  320
#define TFT_HEIGHT 480

// ===== Inversão de Cores =====
// NOTA: No arquivo original estava OFF, mantido OFF
// Se o display mostrar cores invertidas, mude para TFT_INVERSION_ON
#define TFT_INVERSION_OFF
//#define TFT_INVERSION_ON

// ===== Ordem de Cores RGB =====
#define TFT_RGB_ORDER TFT_BGR   // BGR é correto para ESP32-3248S035R

// ===== Pinos do Display (SPI) =====
// CONFIGURAÇÃO CORRETA PARA ESP32-3248S035R
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select do display
#define TFT_DC    2  // Data/Command
#define TFT_RST  -1  // Reset não usado (conectado ao EN do ESP32)

// ===== Backlight =====
// CORREÇÃO CRÍTICA: Era GPIO 27 no arquivo original
// Para ESP32-3248S035R o correto é GPIO 21
#define TFT_BL   21            // LED back-light control pin
#define TFT_BACKLIGHT_ON HIGH  // HIGH para ligar backlight

// ===== Touch Screen (XPT2046 Resistivo) =====
#define TOUCH_CS 33     // Chip select para XPT2046 touch controller
#define TOUCH_OFFSET_ROTATION 1     // Offset de rotação do touch

// ===== DMA (Direct Memory Access) =====
#define ESP32_DMA       // Habilita DMA para melhor performance

// ===== Frequências SPI =====
// CORREÇÃO: Reduzido de 65MHz para 27MHz para estabilidade
#define SPI_FREQUENCY       27000000  // 27MHz para display (era 65MHz)
#define SPI_READ_FREQUENCY  20000000  // 20MHz para leitura
#define SPI_TOUCH_FREQUENCY  2500000  // 2.5MHz para touch

// ===== Porta SPI =====
#define USE_HSPI_PORT   // Usa HSPI port para display

// ===== Fontes =====
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font ~1820 bytes
#define LOAD_FONT2  // Font 2. Small 16 pixel high font ~3534 bytes
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font ~5848 bytes
#define LOAD_FONT6  // Font 6. Large 48 pixel font ~2666 bytes
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font ~2438 bytes
#define LOAD_FONT8  // Font 8. Large 75 pixel font ~3256 bytes
#define LOAD_GFXFF  // FreeFonts. Acesso às 48 Adafruit_GFX free fonts

// ===== Smooth Fonts =====
#define SMOOTH_FONT

// ===== Configurações do Touch (Calibração) =====
// Execute o exemplo Touch_calibrate da TFT_eSPI para obter valores precisos
// Valores abaixo são aproximados, ajuste conforme necessário
#define TOUCH_CALIB_X_MIN 300
#define TOUCH_CALIB_X_MAX 3800
#define TOUCH_CALIB_Y_MIN 300
#define TOUCH_CALIB_Y_MAX 3800

// ===== Suporte a Transações SPI =====
#define SUPPORT_TRANSACTIONS  // Necessário para múltiplos dispositivos SPI

// ===== Configurações Adicionais =====
// Descomente se necessário para debug ou features específicas

// #define TFT_SDA_READ   // Se display tiver SDA bidirecional

// #define USE_DMA_TO_TFT // DMA adicional (pode melhorar performance)

#endif // USER_SETUP_H

// ============================================================================
// INSTRUÇÕES DE INSTALAÇÃO
// ============================================================================
//
// Este arquivo deve substituir o User_Setup.h em:
// .pio/libdeps/esp32-3248s035r/TFT_eSPI/User_Setup.h
//
// OU ser colocado em:
// libraries/TFT_eSPI-CYD/3.5R/TFT_eSPI-master/User_Setup.h
//
// PRINCIPAIS CORREÇÕES APLICADAS:
// 1. TFT_BL mudado de GPIO 27 para GPIO 21
// 2. SPI_FREQUENCY reduzido de 65MHz para 27MHz
// 3. Adicionado ESP32_DMA
// 4. Confirmado TFT_INVERSION_OFF
// 5. Confirmado TFT_RGB_ORDER como TFT_BGR
// 6. Adicionado SUPPORT_TRANSACTIONS
//
// PARA TESTAR:
// 1. Compile e faça upload
// 2. O display deve mostrar imagem correta
// 3. Se cores estiverem invertidas: mude TFT_INVERSION_OFF para ON
// 4. Se touch estiver impreciso: execute calibração
//
// ============================================================================
