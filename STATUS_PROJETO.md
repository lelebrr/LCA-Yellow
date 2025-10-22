# Status e Lista de Tarefas do Projeto LCA

Este documento serve como um painel em tempo real para acompanhar o progresso de todas as funcionalidades planejadas para o LCA Toolkit.

## Fase 1: Recuperação e Estabilização da Base

-   **[FEITO]** Restaurar a Base de Código Original para um estado limpo.
-   **[FEITO]** Estruturar o projeto para o ambiente de desenvolvimento PlatformIO.
-   **[FEITO]** Corrigir a Configuração de Hardware (Driver de Display ST7796, Pinagem Paralela).
-   **[FEITO]** Reaplicar Modificações Essenciais (Rebranding para "LCA", Tradução para PT-BR).
-   **[FEITO]** Verificar e Estabilizar a Base do Firmware.

## Fase 2: Integração de Hardware Adicional

-   **[FEITO]** Integrar suporte de software para o Módulo GPS (GY-GPS6MV2).
-   **[FEITO]** Integrar suporte de software para o Sensor de Temperatura DS18B20.
-   **[PENDENTE]** Integrar suporte de software para o Sensor de Gestos PAJ7620.
-   **[PENDENTE]** Integrar suporte de software para o Buzzer/LED de feedback.
-   **[PENDENTE]** Integrar suporte de software para o Speaker (via DAC).
-   **[PENDENTE]** Integrar suporte de software para o Módulo NRF24L01.
-   **[PENDENTE]** Integrar suporte de software para o Módulo NFC PN532.

## Fase 3: Implementação dos Menus e Ataques

### Menu: WiFi & LAN (Ataques Padrão)
-   **[PENDENTE]** Deauth Flood
-   **[PENDENTE]** ARP Poisoning
-   **[PENDENTE]** Evil Twin AP
-   **[PENDENTE]** PMKID Capture
-   **[PENDENTE]** DNS Spoofing
-   **[PENDENTE]** Rogue DHCP
-   **[PENDENTE]** SYN Flood
-   **[PENDENTE]** WPS Pixie Dust
-   **[PENDENTE]** Probe Flood
-   **[PENDENTE]** Beacon Spam
-   **[PENDENTE]** Zero PMK Installation
-   **[PENDENTE]** EAP Client Crash
-   **[PENDENTE]** Beacon Frame Crash
-   **[PENDENTE]** Network Discovery + Port Scan
-   **[PENDENTE]** MAC Flooding
-   **[PENDENTE]** DHCP Starvation
-   **[PENDENTE]** Rogue Device Injection
-   **[PENDENTE]** WiFi DoS via Channel Jam
-   **[PENDENTE]** Handshake Capture Passive
-   **[PENDENTE]** VLAN Hopping

### Menu: WiFi & LAN (Ataques Destrutivos via WPS)
-   **[PENDENTE]** WPS PIN Flood DoS
-   **[PENDENTE]** WPS Rogue AP Overload
-   **[PENDENTE]** WPS PMKID Corruption
-   **[PENDENTE]** WPS Beacon Spam Crash
-   **[PENDENTE]** WPS ARP Cache Poison
-   **[PENDENTE]** WPS DHCP Exhaustion
-   **[PENDENTE]** WPS Rogue DHCP Injection
-   **[PENDENTE]** WPS PMK Overwrite
-   **[PENDENTE]** WPS Channel Jam Local
-   **[PENDENTE]** WPS Beacon Malformed Flood
-   **[PENDENTE]** WPS ARP Storm
-   **[PENDENTE]** WPS DHCP Option Overload
-   **[PENDENTE]** WPS Probe Response Poison
-   **[PENDENTE]** WPS EAP-Fail Injection
-   **[PENDENTE]** WPS PMKID Flood Invalid
-   **[PENDENTE]** WPS Rogue AP DHCP DoS
-   **[PENDENTE]** WPS Beacon TLV Overflow
-   **[PENDENTE]** WPS ARP Reply Storm
-   **[PENDENTE]** WPS Probe Request Malformed
-   **[PENDENTE]** WPS DHCP Lease Exhaust
-   **[PENDENTE]** WPS Rogue AP Beacon DoS
-   **[PENDENTE]** WPS EAP-Success Fake
-   **[PENDENTE]** WPS ARP Gratuitous Flood
-   **[PENDENTE]** WPS Probe Response Flood
-   **[PENDENTE]** WPS DHCP Option Malformed
-   **[PENDENTE]** WPS PMKID Replay Invalid
-   **[PENDENTE]** WPS Beacon IE Overflow
-   **[PENDENTE]** WPS Rogue AP IP Conflict
-   **[PENDENTE]** WPS ARP Request Storm
-   **[PENDENTE]** WPS PIN Brute-Force DoS

### Menu: Bluetooth
-   **[PENDENTE]** BLE Spam
-   **[PENDENTE]** BlueSmack
-   **[PENDENTE]** BlueBorne
-   **[PENDENTE]** KNOB Attack
-   **[PENDENTE]** BIAS Attack
-   **[PENDENTE]** BrakTooth V1
-   **[PENDENTE]** BrakTooth V2
-   **[PENDENTE]** Pairing Hijack
-   **[PENDENTE]** BLE Flood DoS
-   **[PENDENTE]** GATT Write Overflow
-   **[PENDENTE]** HCI Command Injection
-   **[PENDENTE]** BLE Device Spoofing
-   **[PENDENTE]** BlueSnarf
-   **[PENDENTE]** BlueBugging
-   **[PENDENTE]** BT Pairing Replay
-   **[PENDENTE]** LE Privacy Bypass
-   **[PENDENTE]** BT DoS via LMP
-   **[PENDENTE]** BLE Key Extraction
-   **[PENDENTE]** BT Classic Eavesdrop
-   **[PENDENTE]** BLE Battery DoS

### Menu: Infravermelho (IR)
-   **[PENDENTE]** IR Replay
-   **[PENDENTE]** IR Jamming
-   **[PENDENTE]** IR Code Injection
-   **[PENDENTE]** IR DoS
-   **[PENDENTE]** IR Spoofing
-   **[PENDENTE]** IR Man-in-the-Middle
-   **[PENDENTE]** IR Brute Force
-   **[PENDENTE]** IR Signal Cloning
-   **[PENDENTE]** IR Frequency Hopping
-   **[PENDENTE]** IR Denial of Service
-   **[PENDENTE]** IR Protocol Fuzzing
-   **[PENDENTE]** IR Multi-Device Control
-   **[PENDENTE]** IR Stealth Replay
-   **[PENDENTE]** IR Signal Amplification
-   **[PENDENTE]** IR Code Cracking
-   **[PENDENTE]** IR Jamming Selective
-   **[PENDENTE]** IR Remote Cloning
-   **[PENDENTE]** IR Buffer Overflow
-   **[PENDENTE]** IR Network Injection
-   **[PENDENTE]** IR DoS via Modulation

### Menu: Rádio Frequência (RF)
-   **[PENDENTE]** RF Replay
-   **[PENDENTE]** RF Jamming
-   **[PENDENTE]** Rolling Code Bypass
-   **[PENDENTE]** RF Brute Force
-   **[PENDENTE]** RF DoS
-   **[PENDENTE]** RF Signal Cloning
-   **[PENDENTE]** RF Man-in-the-Middle
-   **[PENDENTE]** RF Frequency Hopping Jam
-   **[PENDENTE]** RF Protocol Fuzzing
-   **[PENDENTE]** RF Selective Replay
-   **[PENDENTE]** RF Amplification Attack
-   **[PENDENTE]** RF Code Cracking
-   **[PENDENTE]** RF Multi-Device Control
-   **[PENDENTE]** RF Stealth Replay
-   **[PENDENTE]** RF Network Injection
-   **[PENDENTE]** RF Buffer Overflow
-   **[PENDENTE]** RF Denial of Service
-   **[PENDENTE]** RF Hopping Bypass
-   **[PENDENTE]** RF Cloning via NFC
-   **[PENDENTE]** RF Jamming Selective

### Menu: NFC (Padrão)
-   **[PENDENTE]** NFC Relay
-   **[PENDENTE]** NFC Cloning
-   **[PENDENTE]** NFC Skimming
-   **[PENDENTE]** NFC Eavesdropping
-   **[PENDENTE]** NFC Replay
-   **[PENDENTE]** NFC DoS
-   **[PENDENTE]** NFC Buffer Overflow
-   **[PENDENTE]** NFC Man-in-the-Middle
-   **[PENDENTE]** NFC Tag Spoofing
-   **[PENDENTE]** NFC Brute Force
-   **[PENDENTE]** NFC Relay to Remote
-   **[PENDENTE]** NFC Data Injection
-   **[PENDENTE]** NFC Protocol Downgrade
-   **[PENDENTE]** NFC Jamming
-   **[PENDENTE]** NFC Key Extraction
-   **[PENDENTE]** NFC Multi-Tag Flood
-   **[PENDENTE]** NFC Stealth Cloning
-   **[PENDENTE]** NFC Network Injection
-   **[PENDENTE]** NFC Write-Only Attack
-   **[PENDENTE]** NFC Fuzzing

### Menu: NFC (Ataques Destrutivos)
-   **[PENDENTE]** Tag Kill Command
-   **[PENDENTE]** Memory Wipe Full
-   **[PENDENTE]** UID Corrupt Overwrite
-   **[PENDENTE]** Sector Lock Permanent
-   **[PENDENTE]** NDEF Overwrite Noise
-   **[PENDENTE]** Tag Reset Loop Force
-   **[PENDENTE]** Authentication Flood Fail
-   **[PENDENTE]** Memory Fragmentation Write
-   **[PENDENTE]** Protocol Command Mismatch
-   **[PENDENTE]** Power Query Overload
-   **[PENDENTE]** Sector Data Inversion
-   **[PENDENTE]** Tag Halt Permanent
-   **[PENDENTE]** UID Nullification
-   **[PENDENTE]** NDEF Header Corruption
-   **[PENDENTE]** Authentication Key Wipe
-   **[PENDENTE]** Tag Collision Force
-   **[PENDENTE]** Memory Sector Skip Write
-   **[PENDENTE]** Tag Wakeup Flood
-   **[PENDENTE]** UID Bit Flip
-   **[PENDENTE]** Tag Format Reversal

### Menu: GPS
-   **[PENDENTE]** GPS Spoofing (Injeção NMEA)
-   **[PENDENTE]** GPS Jamming (com Módulo RF)
-   **[PENDENTE]** GPS Replay (Gravar/Reproduzir NMEA)
-   **[PENDENTE]** GPS DoS (Flood de Sentenças)
-   **[PENDENTE]** GPS Meaconing (Replay com Atraso)
-   **[PENDENTE]** GPS Fuzzing (Sentenças Malformadas)
-   **[PENDENTE]** GPS Navigation Hijack (Alteração Gradual)
-   **[PENDENTE]** GPS Signal Injection
-   **[PENDENTE]** GPS Frequency Hopping Jam
-   **[PENDENTE]** GPS Buffer Overflow
-   **[PENDENTE]** GPS Man-in-the-Middle
-   **[PENDENTE]** GPS Selective Spoof
-   **[PENDENTE]** GPS Denial of Service
-   **[PENDENTE]** GPS Code Cracking
-   **[PENDENTE]** GPS Multi-Sat Spoof
-   **[PENDENTE]** GPS Stealth Replay
-   **[PENDENTE]** GPS Network Injection
-   **[PENDENTE]** GPS Amplification
-   **[PENDENTE]** GPS Protocol Downgrade
-   **[PENDENTE]** GPS Tracking Bypass

## Fase 4: Finalização e Documentação

-   **[PENDENTE]** Refinamento final da GUI, ícones de ajuda ("?") e usabilidade.
-   **[PENDENTE]** Criação da documentação completa do usuário (`manual.md`, `ataques.md`, etc.).
-   **[PENDENTE]** Verificação Final, Pré-Commit e Submissão do Projeto Completo.
