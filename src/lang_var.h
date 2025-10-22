#pragma once

#ifndef lang_var_h
#define lang_var_h

#include "configs.h"

// Textos da janela de inicialização
PROGMEM const char text0_0[] = "Dando espaco para HardwareSerial...";
PROGMEM const char text0_1[] = "Serial iniciada";
PROGMEM const char text0_2[] = "RAM verificada";
PROGMEM const char text0_3[] = "Cartao SD inicializado";
PROGMEM const char text0_4[] = "Falha ao inicializar o cartao SD";
PROGMEM const char text0_5[] = "Configuracao da bateria verificada";
PROGMEM const char text0_6[] = "Interface de temperatura inicializada";
PROGMEM const char text0_7[] = "Interface de LED inicializada";
PROGMEM const char text0_8[] = "Iniciando...";

// Textos de biblioteca única (ação)/Usados com frequência
PROGMEM const char text00[] = "Nivel da bateria alterado: ";
PROGMEM const char text01[] = "arquivo fechado";
PROGMEM const char text02[] = "Falha ao abrir o arquivo '";
PROGMEM const char text03[] = "LIGADO";
PROGMEM const char text04[] = "DESLIGADO";
PROGMEM const char text05[] = "Carregar";
PROGMEM const char text06[] = "Salvar Como";
PROGMEM const char text07[] = "Sair";
PROGMEM const char text08[] = "Configuracoes";
PROGMEM const char text09[] = "Voltar";
PROGMEM const char text10[] = "Canal:";
PROGMEM const char text11[] = "Toque na tela para sair";
PROGMEM const char text12[] = "Cancelar";
PROGMEM const char text13[] = "Salvar";
PROGMEM const char text14[] = "Sim";
PROGMEM const char text15[] = "Abrindo /update.bin...";
PROGMEM const char text16[] = "Fechar";
PROGMEM const char text17[] = "FALHA";
PROGMEM const char text18[] = "pacotes/seg: ";

// Textos de Menufunctions.cpp
PROGMEM const char text1_0[] = "Lista de SSIDs";
PROGMEM const char text1_1[] = "Adicionar SSIDs";
PROGMEM const char text1_2[] = "SSID: ";
PROGMEM const char text1_3[] = "Senha:";
PROGMEM const char text1_4[] = "Configuracao desativada";
PROGMEM const char text1_5[] = "Configuracao ativada";
PROGMEM const char text1_6[] = "LCA Toolkit ";
PROGMEM const char text1_7[] = "WiFi ";
PROGMEM const char text1_8[] = "Bad USB ";
PROGMEM const char text1_9[] = "Dispositivo ";
PROGMEM const char text1_10[] = "Apps Gerais ";
PROGMEM const char text1_11[] = "Atualizando... ";
PROGMEM const char text1_12[] = "Selecione o Metodo ";
PROGMEM const char text1_13[] = "Confirmar Atualizacao ";
PROGMEM const char text1_14[] = "Atualizacao ESP8266 ";
PROGMEM const char text1_15[] = "Atualizar Firmware ";
PROGMEM const char text1_16[] = "Idioma ";
PROGMEM const char text1_17[] = "Info do Dispositivo ";
PROGMEM const char text1_18[] = "Configuracoes ";
PROGMEM const char text1_19[] = "Bluetooth ";
PROGMEM const char text1_20[] = "Sniffers WiFi ";
PROGMEM const char text1_21[] = "Ataques WiFi ";
PROGMEM const char text1_22[] = "WiFi Geral ";
PROGMEM const char text1_23[] = "Sniffers Bluetooth ";
PROGMEM const char text1_24[] = "Bluetooth Geral ";
PROGMEM const char text1_25[] = "Desligar WiFi ";
PROGMEM const char text1_26[] = "Desligar BLE ";
PROGMEM const char text1_27[] = "Gerar SSIDs ";
PROGMEM const char text1_28[] = "Limpar SSIDs ";
PROGMEM const char text1_29[] = "Limpar APs ";
PROGMEM const char text1_30[] = "Reiniciar";
PROGMEM const char text1_31[] = "Sniffers";
PROGMEM const char text1_32[] = "Ataques";
PROGMEM const char text1_33[] = "Geral";
PROGMEM const char text1_34[] = "Sniffer Bluetooth";
PROGMEM const char text1_35[] = "Detectar Skimmers";
PROGMEM const char text1_36[] = "Testar BadUSB";
PROGMEM const char text1_37[] = "Executar Script Ducky";
PROGMEM const char text1_38[] = "Desenhar";
PROGMEM const char text1_39[] = "Atualizacao Web";
PROGMEM const char text1_40[] = "Atualizacao SD";
PROGMEM const char text1_41[] = "Atualizacao ESP8266";
PROGMEM const char text1_42[] = "Sniff de Probe Request";
PROGMEM const char text1_43[] = "Sniff de Beacon";
PROGMEM const char text1_44[] = "Sniff de Deauth";
PROGMEM const char text1_45[] = "Monitor de Pacotes";
PROGMEM const char text1_46[] = "Scan EAPOL/PMKID";
PROGMEM const char text1_47[] = "Detectar Pwnagotchi";
PROGMEM const char text1_48[] = "Detectar Espressif";
PROGMEM const char text1_49[] = "Scan de APs";
PROGMEM const char text1_50[] = "Spam de Beacon (Lista)";
PROGMEM const char text1_51[] = "Spam de Beacon (Aleatorio)";
PROGMEM const char text1_52[] = "Beacon Rick Roll";
PROGMEM const char text1_53[] = "Flood de Probe Req";
PROGMEM const char text1_54[] = "Flood de Deauth";
PROGMEM const char text1_55[] = "Conectar ao WiFi";
PROGMEM const char text1_56[] = "Selecionar APs";
PROGMEM const char text1_57[] = "Spam de Clone de AP";
PROGMEM const char text1_58[] = "Captura Raw";
PROGMEM const char text1_59[] = "Sniff de Estacao";
PROGMEM const char text1_60[] = "Limpar Estacoes";
PROGMEM const char text1_61[] = "Selecionar Estacoes";
PROGMEM const char text1_62[] = "Deauth Direcionado";

// Textos de SDInterface.cpp
PROGMEM const char text2_0[] = "Erro, nao foi possivel encontrar update.bin";
PROGMEM const char text2_1[] = "Iniciando atualizacao via SD...";
PROGMEM const char text2_2[] = "Erro, update.bin esta vazio";
PROGMEM const char text2_3[] = "\nReiniciando...\n";
PROGMEM const char text2_4[] = "Nao foi possivel carregar update.bin de /";
PROGMEM const char text2_5[] = "Tamanho do arquivo: ";
PROGMEM const char text2_6[] = "Gravando arquivo na particao...";
PROGMEM const char text2_7[] = "Gravado: ";
PROGMEM const char text2_8[] = "Gravado apenas : ";
PROGMEM const char text2_9[] = ". Tentar novamente?";
PROGMEM const char text2_10[] = " com sucesso";
PROGMEM const char text2_11[] = "Atualizacao completa";
PROGMEM const char text2_12[] = "A atualizacao nao pode ser concluida";
PROGMEM const char text2_13[] = "Ocorreu um erro. Erro #: ";
PROGMEM const char text2_14[] = "Sem espaco suficiente para iniciar o OTA";

// Textos de Web.cpp
PROGMEM const char text3_0[] = "Configurando servidor de atualizacao...\n\n";
PROGMEM const char text3_1[] = "Endereco IP: ";
PROGMEM const char text3_2[] = "Atualizacao: ";
PROGMEM const char text3_3[] = "Bytes concluidos: ";
PROGMEM const char text3_4[] = "Sucesso na Atualizacao: ";
PROGMEM const char text3_5[] = "\nConfiguracao do servidor de atualizacao concluida";

// Textos de WiFiScan.cpp
PROGMEM const char text4_0[] = " RSSI: ";
PROGMEM const char text4_1[] = "Skimmer Potencial: ";
PROGMEM const char text4_2[] = "Ja Conectado";
PROGMEM const char text4_3[] = "Falha ao conectar";
PROGMEM const char text4_4[] = "Conectado";
PROGMEM const char text4_5[] = "ForcarPMKID";
PROGMEM const char text4_6[] = "ForcarProbe";
PROGMEM const char text4_7[] = "SalvarPCAP";
PROGMEM const char text4_8[] = "Flood de Probe";
PROGMEM const char text4_9[] = "Limpando APs...";
PROGMEM const char text4_10[] = "APs Limpos: ";
PROGMEM const char text4_11[] = "Limpando SSIDs...";
PROGMEM const char text4_12[] = "SSIDs Limpos: ";
PROGMEM const char text4_13[] = "Gerando SSIDs...";
PROGMEM const char text4_14[] = "SSIDs Gerados: ";
PROGMEM const char text4_15[] = "    Total de SSIDs: ";
PROGMEM const char text4_16[] = "Desligando WiFi...";
PROGMEM const char text4_17[] = "WiFi nao inicializado no momento";
PROGMEM const char text4_18[] = "Desligando BLE...";
PROGMEM const char text4_19[] = "BLE nao inicializado no momento";
PROGMEM const char text4_20[] = "Firmware: LCA Toolkit";
PROGMEM const char text4_21[] = "Versao: ";
PROGMEM const char text4_22[] = "ESP-IDF: ";
PROGMEM const char text4_23[] = "Bypass WSL: ativado";
PROGMEM const char text4_24[] = "Bypass WSL: desativado";
PROGMEM const char text4_25[] = "MAC da Estacao: ";
PROGMEM const char text4_26[] = "MAC do AP: ";
PROGMEM const char text4_27[] = "";
PROGMEM const char text4_28[] = "Cartao SD: Conectado";
PROGMEM const char text4_29[] = "Tamanho do SD: ";
PROGMEM const char text4_30[] = "Cartao SD: Nao Conectado";
PROGMEM const char text4_31[] = "Tamanho do SD: 0";
PROGMEM const char text4_32[] = "I2C IP5306: suportado";
PROGMEM const char text4_33[] = "Nivel Bat.: ";
PROGMEM const char text4_34[] = "I2C IP5306: nao suportado";
PROGMEM const char text4_35[] = "Temp. interna: ";
PROGMEM const char text4_36[] = " Detectar Espressif ";
PROGMEM const char text4_37[] = " Detectar Pwnagotchi ";
PROGMEM const char text4_38[] = " Sniffer de Beacon ";
PROGMEM const char text4_39[] = " Sniffer de Deauth ";
PROGMEM const char text4_40[] = " Sniffer de Probe Req ";
PROGMEM const char text4_41[] = " Sniff Bluetooth ";
PROGMEM const char text4_42[] = " Detectar Skimmers ";
PROGMEM const char text4_43[] = "Procurando por\nskimmers com Bluetooth\nHC-03, HC-05 e HC-06...";
PROGMEM const char text4_44[] = " Scan de AP ";
PROGMEM const char text4_45[] = "Limpando Estacoes...";
PROGMEM const char text4_46[] = "Estacoes Limpas: ";
PROGMEM const char text4_47[] = "Deauth Direcionado";

// ... (as tabelas de texto permanecem as mesmas, apenas apontando para as novas strings)
PROGMEM const char *text_table0[] = {text0_0,text0_1, text0_2, text0_3, text0_4, text0_5, text0_6, text0_7, text0_8};
PROGMEM const char *text_table1[] = {text1_0,text1_1,text1_2,text1_3,text1_4,text1_5,text1_6,text1_7,text1_8,text1_9,text1_10,text1_11,text1_12,text1_13,text1_14,text1_15,text1_16,text1_17,text1_18,text1_19,text1_20,text1_21,text1_22,text1_23,text1_24,text1_25,text1_26,text1_27,text1_28,text1_29,text1_30,text1_31,text1_32,text1_33,text1_34,text1_35,text1_36,text1_37,text1_38,text1_39,text1_40,text1_41,text1_42,text1_43,text1_44,text1_45,text1_46,text1_47,text1_48,text1_49,text1_50,text1_51,text1_52,text1_53,text1_54,text1_55,text1_56,text1_57,text1_58,text1_59,text1_60,text1_61,text1_62};
PROGMEM const char *text_table2[] = {text2_0,text2_1,text2_2,text2_3,text2_4,text2_5,text2_6,text2_7,text2_8,text2_9,text2_10,text2_11,text2_12,text2_13,text2_14};
PROGMEM const char *text_table3[] = {text3_0,text3_1,text3_2,text3_3,text3_4,text3_5};
PROGMEM const char *text_table4[] = {text4_0,text4_1,text4_2,text4_3,text4_4,text4_5,text4_6,text4_7,text1_54,text4_9,text4_10,text4_11,text4_12,text4_13,text4_14,text4_15,text4_16,text4_17,text4_18,text4_19,text4_20,text4_21,text4_22,text4_23,text4_24,text4_25,text4_26,text4_27,text4_28,text4_29,text4_30,text4_31,text4_32,text4_33,text4_34,text4_35,text4_36,text4_37,text4_38,text4_39,text4_40,text4_41,text4_42,text4_43,text4_44,text4_45,text4_46,text4_47};


#endif
