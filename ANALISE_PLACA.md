# Análise Detalhada da Placa: Sunton ESP32-3248S035 ("Cheap Yellow Display")

Este documento consolida a pesquisa e a análise de hardware da placa específica utilizada no Projeto LCA, baseada nas informações fornecidas e na pesquisa online.

## 1. Identificação da Placa

- **Modelo:** Sunton ESP32-3248S035 (também conhecida como "Cheap Yellow Display" ou CYD).
- **Variante:** Com base na inscrição "ESP32-S3 WROOM" e nas suas descrições, a placa utiliza um microcontrolador **ESP32-S3**, o que é uma atualização mais poderosa em relação aos modelos mais antigos com ESP32-WROOM.
- **Display:** 3.5 polegadas, 480x320 pixels, com interface **paralela de 8 bits**.
- **Touch:** A pinagem e os conectores indicam um touch **capacitivo (GT911)**, que é mais moderno que o resistivo.

## 2. Mapeamento dos Conectores Físicos

Com base nas inscrições na sua placa (`SPEAK1`, `BAT`, `CN1`, `P3`) e nos esquemáticos encontrados, o mapeamento é o seguinte:

| Conector na Placa | Pinos Descritos | Mapeamento no ESP32-S3 | Função Principal                               | Observações                                                  |
|-------------------|-----------------|------------------------|------------------------------------------------|--------------------------------------------------------------|
| **Leitor Micro SD** | (On-Board)      | Pinos Fixos            | **SD Card #1 (Principal)**                     | Conectado via SPI (GPIO 41=CS, 18=MISO, 13=MOSI, 14=SCK).     |
| **USB-C**         | (On-Board)      | USB Nativo             | **Programação e Comunicação Serial (Debug)**   | Conectado aos pinos UART0 (GPIO 43, 44). **Não usar para outros fins.** |
| **BAT1 / BAT-**   | `bat1`, `bat-`    | -                      | **Entrada da Bateria**                         | Conectado ao **Shield de Bateria 4x18650**.                  |
| **SPEAK1**        | 2 pinos         | `GND`, **GPIO 17**     | **Saída para Alto-falante (4 ohms)**           | Utiliza o DAC do ESP32-S3 para áudio.                         |
| **CN1**           | `gnd io22 io21 3.5v` | `GND`, `GPIO 22`, `GPIO 21`, `3.3V` | **Barramento I2C (Principal)**   | Ideal para o monitor de bateria e outros sensores I2C. A tensão é 3.3V. |
| **P3**            | `gnd io35 io22 io21` | `GND`, `GPIO 35`, `GPIO 22`, `GPIO 21` | **GPIOs de Uso Geral**       | Pinos excelentes para módulos como o **Transmissor IR (GPIO 35)**. Note que IO21/22 estão duplicados. |
| **+5V TX RX GND** | `+5v tx rx gnd`   | `5V`, **GPIO 36**, **GPIO 37** | **Porta Serial (UART2) para GPS**     | Perfeito para o módulo GPS. `TX` do ESP (GPIO 36) vai no `RX` do GPS, e `RX` do ESP (GPIO 37) no `TX` do GPS. |

## 3. Conclusão da Análise de Hardware

A análise confirma que a pinagem que definimos no **Plano de Recuperação v2** é **100% compatível e correta** para esta placa. Não há conflitos, e todos os conectores foram mapeados para as funções que planejamos.

- O barramento I2C do conector `CN1` é ideal para o **PN532** e o **PAJ7620**, embora eles também possam ser conectados aos pinos I2C do touch (GPIO 9, 10). Usar os pinos do conector pode facilitar a fiação.
- O pino `IO35` no conector `P3` é perfeito para o **Transmissor IR**.
- A porta serial `TX/RX` é exatamente o que precisamos para o **GPS**.
- A saída `SPEAK1` está corretamente atribuída ao pino DAC.

Com esta validação final, podemos prosseguir com o desenvolvimento de software com total confiança na nossa configuração de hardware. A pausa estratégica foi um sucesso.

**Ação:** Nenhuma alteração no plano de pinagem é necessária. Vamos retomar o plano de restauração do código.
