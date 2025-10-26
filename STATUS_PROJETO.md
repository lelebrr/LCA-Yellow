# Status e Lista de Tarefas do Projeto LCA

Este documento serve como um painel em tempo real para acompanhar o progresso de todas as funcionalidades planejadas para o LCA Toolkit.

## Fase 1: Recuperação e Refatoração Estrutural

-   **[CONCLUÍDO]** Restaurar a Base de Código Original para um estado limpo.
-   **[CONCLUÍDO]** Estruturar o projeto para o ambiente de desenvolvimento PlatformIO.
-   **[CONCLUÍDO]** Corrigir a Configuração de Hardware (Driver de Display ST7796, Pinagem Paralela).
-   **[CONCLUÍDO]** Reaplicar Modificações Essenciais (Rebranding para "LCA", Tradução para PT-BR).
-   **[CONCLUÍDO]** Verificar e Estabilizar a Base do Firmware.
-   **[CONCLUÍDO]** **Refatoração da UI:** Migração completa da `LinkedList` para `std::vector` no sistema de menus.
-   **[CONCLUÍDO]** **Atualização da Biblioteca Gráfica:** Migração da API da LVGL v7 para v8, garantindo compatibilidade.
-   **[CONCLUÍDO]** **Criação da Arquitetura de Ataques:** Implementação de módulos dedicados (`WifiAttacks.cpp`, `BleAttacks.cpp`) para organização do código.

## Fase 2: Integração de Hardware Adicional

-   **[CONCLUÍDO]** Integrar suporte de software para o Módulo GPS (GY-GPS6MV2).
-   **[CONCLUÍDO]** Integrar suporte de software para o Sensor de Temperatura DS18B20.
-   **[PENDENTE]** Integrar suporte de software para o Sensor de Gestos PAJ7620.
-   **[PENDENTE]** Integrar suporte de software para o Buzzer/LED de feedback.
-   **[PENDENTE]** Integrar suporte de software para o Speaker (via DAC).
-   **[PENDENTE]** Integrar suporte de software para o Módulo NRF24L01.
-   **[PENDENTE]** Integrar suporte de software para o Módulo NFC PN532.

## Fase 3: Implementação dos Menus e Ataques

### Menu: WiFi & LAN (Ataques Padrão)
-   **[EM PROGRESSO]** Deauthentication Flood
-   **[PENDENTE]** EAPOL 4-Way Handshake Capture
-   **[PENDENTE]** PMKID Attack
-   **[EM PROGRESSO]** Evil Twin AP
-   **[PENDENTE]** KARMA Attack
-   **[EM PROGRESSO]** Channel Flood
-   **[EM PROGRESSO]** Disassociation Flood
-   **[EM PROGRESSO]** Authentication Flood
-   **[PENDENTE]** Null Data Frame Flood
-   **[PENDENTE]** Probe Response Flood
-   **[PENDENTE]** CTS/RTS Flood
-   **[EM PROGRESSO]** Beacon Spam
-   **[PENDENTE]** QoS Null Flood
-   **[PENDENTE]** Association Flood
-   **[PENDENTE]** Fake AP DoS
-   **[PENDENTE]** ACK Flood
-   **[PENDENTE]** Channel Switch Announcement
-   **[PENDENTE]** SSID Confusion
-   **[PENDENTE]** Management Frame DoS
-   **[PENDENTE]** Power Save Attack
-   **[PENDENTE]** Fragmentation Attack
-   **[PENDENTE]** BaPS Flood
-   **[PENDENTE]** Client Isolation Bypass
-   **[PENDENTE]** WPA3 SAE Downgrade
-   **[PENDENTE]** Beacon Timing Attack
-   **[PENDENTE]** Probe Request Flood
-   **[PENDENTE]** DTIM DoS
-   **[PENDENTE]** Country Code Attack
-   **[PENDENTE]** Vendor Specific DoS

### Menu: Ataques WPS
-   **[PENDENTE]** Pixie Dust Attack
-   **[PENDENTE]** WPS Brute Force
-   **[PENDENTE]** WPS Lock Bypass
-   **[PENDENTE]** Online WPS Attack
-   **[PENDENTE]** WPS Flood
-   **[PENDENTE]** PIN Check Bypass
-   **[PENDENTE]** WPS Session Flood
-   **[PENDENTE]** WPS Deauth + Pixie
-   **[PENDENTE]** WPS Config Reload
-   **[PENDENTE]** WPS Dictionary

### Menu: Bluetooth (BLE)
-   **[EM PROGRESSO]** BLE Spam Flood
-   **[EM PROGRESSO]** Sour Apple Attack
-   **[EM PROGRESSO]** Swift Pair Spam
-   **[EM PROGRESSO]** AirTag Spoofing
-   **[EM PROGRESSO]** BLE Beacon Flood
-   **[PENDENTE]** Connection Spam
-   **[PENDENTE]** Service Discovery DoS
-   **[PENDENTE]** Notification Flood
-   **[EM PROGRESSO]** Flipper Zero Spoof
-   **[PENDENTE]** CC Skimmer Detect
-   **[EM PROGRESSO]** Battery Drain Attack
-   **[EM PROGRESSO]** UUID Flood
-   **[EM PROGRESSO]** Advertising Interval DoS
-   **[PENDENTE]** Legacy BLE Flood
-   **[PENDENTE]** Extended Adv Flood
-   **[PENDENTE]** Manufacturer Spam
-   **[PENDENTE]** Rssi Manipulation
-   **[PENDENTE]** Periodic Adv Flood
-   **[PENDENTE]** GATT Write Flood
-   **[PENDENTE]** Read Request Flood
-   **[PENDENTE]** Disconnect Flood
-   **[PENDENTE]** MTU Negotiation DoS
-   **[PENDENTE]** Security Manager DoS
-   **[PENDENTE]** L2CAP Echo Flood
-   **[PENDENTE]** Scan Request Flood
-   **[EM PROGRESSO]** Device Name Spoof
-   **[EM PROGRESSO]** Appearance Spoof
-   **[EM PROGRESSO]** Tx Power Spoof
-   **[PENDENTE]** Channel Map DoS
-   **[PENDENTE]** LE Coded PHY Flood

## Fase 4: Finalização e Documentação

-   **[PENDENTE]** Refinamento final da GUI, ícones de ajuda ("?") e usabilidade.
-   **[PENDENTE]** Criação da documentação completa do usuário (`manual.md`, `ataques.md`, etc.).
-   **[PENDENTE]** Verificação Final, Pré-Commit e Submissão do Projeto Completo.
