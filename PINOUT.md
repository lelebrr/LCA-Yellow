# Pinout Final e Definitivo - Projeto LCA (v2)

Este documento detalha a pinagem final e validada para todos os componentes de hardware do projeto LCA, considerando as restrições da interface de display paralela da placa **ESP32-3248S05R (ESP32-S3)**.

## Tabela de Mapeamento de GPIOs

| Pino (GPIO) | Uso Principal                     | Módulo/Componente          | Barramento/Tipo      | Observações                                    |
|-------------|-----------------------------------|----------------------------|----------------------|------------------------------------------------|
| **0**       | *Boot Mode*                       | -                          | *Interno*            | **Não usar** (Puxado para GND para flashar)     |
| **1**       | *Disponível*                      | -                          | -                    | -                                              |
| **2**       | *Disponível*                      | -                          | -                    | -                                              |
| **3**       | `BUZZER_LED_PIN`                  | Buzzer / LED               | Digital Out          | Feedback sonoro/visual.                        |
| **4**       | `TFT_D2` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **5**       | `TFT_D3` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **6**       | `TFT_D4` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **7**       | `TFT_D5` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **8**       | `TFT_D6` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **9**       | `TOUCH_SDA` (Fixo)                | Touchscreen / I2C Bus      | I2C (SDA)            | **PN532** e **PAJ7620** compartilham este pino. |
| **10**      | `TOUCH_SCL` (Fixo)                | Touchscreen / I2C Bus      | I2C (SCL)            | **PN532** e **PAJ7620** compartilham este pino. |
| **11**      | `TOUCH_INT` (Fixo)                | Touchscreen                | Interrupt            | Ocupado pelo touchscreen.                      |
| **12**      | `TOUCH_RST` (Fixo)                | Touchscreen                | Reset                | Ocupado pelo touchscreen.                      |
| **13**      | `SPI_MOSI`                        | SPI Bus                    | SPI (MOSI/COPI)      | P/ SD1, SD2, CC1101, NRF24.                     |
| **14**      | `SPI_SCK`                         | SPI Bus                    | SPI (SCK)            | P/ SD1, SD2, CC1101, NRF24.                     |
| **15**      | `NRF24_CE`                        | NRF24L01                   | Digital Out          | Chip Enable para NRF24.                        |
| **16**      | `DS18B20_PIN`                     | DS18B20 Temp Sensor        | One-Wire             | Requer pull-up de 4.7kΩ.                       |
| **17**      | `SPEAKER_PIN`                     | Alto-falante (4 ohms)      | DAC (Canal 1)        | Saída de áudio.                                |
| **18**      | `SPI_MISO`                        | SPI Bus                    | SPI (MISO/CIPO)      | P/ SD1, CC1101, NRF24.                          |
| **19**      | `CC1101_CS1`                      | CC1101 #1                  | SPI (CS)             | Chip Select para o primeiro CC1101.            |
---
| **VCC**     | *Alimentação*                     | Shield de Bateria 4x18650  | Power                | Fornece **5V** e **3.3V** para os módulos.      |
| **GND**     | *Terra*                           | Shield de Bateria / ESP32  | Power                | Conectar todos os GNDs em um ponto comum.      |
| **20**      | `CC1101_CS2`                      | CC1101 #2                  | SPI (CS)             | Chip Select para o segundo CC1101.             |
| **21**      | `SD2_CS`                          | SD Card 2 (Externo)        | SPI (CS)             | Chip Select para o segundo SD.                 |
| **33**      | `NRF24_CS`                        | NRF24L01                   | SPI (CS)             | Chip Select para NRF24.                        |
| **34**      | *Input Only*                      | -                          | -                    | *Disponível (Apenas Entrada)*                  |
| **35**      | `IR_TX_PIN`                       | Transmissor IR             | Digital Out          | -                                              |
| **36**      | `GPS_RX` (ESP RX)                 | GPS Module                 | UART2 (RX)           | Conectar ao TX do GPS.                         |
| **37**      | `GPS_TX` (ESP TX)                 | GPS Module                 | UART2 (TX)           | Conectar ao RX do GPS.                         |
| **38**      | `TFT_D7` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **39**      | `TFT_D0` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **40**      | `TFT_D1` (Fixo)                   | Display On-Board           | Paralelo             | Ocupado pelo display.                          |
| **41**      | `SD_CS` (Fixo)                    | SD Card 1 (On-Board)       | SPI (CS)             | Chip Select para o SD Card principal.          |
| **42**      | `TFT_RS` (Fixo)                   | Display On-Board           | Paralelo (DC/RS)     | Ocupado pelo display.                          |
| **43**      | `UART0_TX`                        | *Debug/Serial*             | *Interno*            | **Não usar** (Usado para a porta USB/Serial).   |
| **44**      | `UART0_RX`                        | *Debug/Serial*             | *Interno*            | **Não usar** (Usado para a porta USB/Serial).   |
| **45**      | `TFT_CS` (Fixo)                   | Display On-Board           | Paralelo (CS)        | Ocupado pelo display.                          |
| **46**      | `TFT_WR` (Fixo)                   | Display On-Board           | Paralelo (WR)        | Ocupado pelo display.                          |
| **47**      | `TFT_RD` (Fixo)                   | Display On-Board           | Paralelo (RD)        | Ocupado pelo display.                          |
| **48**      | `TFT_BL` (Fixo)                   | Display On-Board           | Backlight            | Controle do brilho da tela.                    |
