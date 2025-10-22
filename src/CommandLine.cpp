#include "CommandLine.h"
#include <ESPAsyncWebServer.h>
#include "WiFiScan.h"
#include "EvilPortal.h"

// DECLARAÇÕES EXTERNAS
extern WiFiScan wifi_scan_obj;
extern EvilPortal evil_portal_obj;
extern std::vector<ssid>* ssids;
extern std::vector<AccessPoint>* access_points;
extern LinkedList<Station>* stations;

void handleBTAttack(uint8_t attack_type, uint16_t color, String message) {
  #ifdef HAS_SCREEN
  display_obj.tft.setTextColor(color, TFT_BLACK);
  display_obj.tft.println(message);
  #endif
  // Implementar lógica do ataque BT
}

#include "lvgl.h"

#include "configs.h"
#include "GpsInterface.h"

CommandLine::CommandLine() {
}

void CommandLine::RunSetup() {
  Serial.println(this->ascii_art);

  Serial.println(F("\n\n--------------------------------\n"));
  Serial.println(F("           LCA Toolkit         \n"));
  Serial.println(String(F("            ")) + version_number + F("\n"));
  Serial.println(String(F("--------------------------------\n\n")));

  Serial.print("> ");
}

String CommandLine::getSerialInput() {
  String input = "";

  if (Serial.available() > 0)
    input = Serial.readStringUntil('\n');

  input.trim();
  return input;
}

void CommandLine::main(uint32_t currentTime) {
  String input = this->getSerialInput();

  this->runCommand(input);

  if (input != "")
    Serial.print("> ");
}

std::vector<String> CommandLine::parseCommand(String input, char* delim) {
  std::vector<String> cmd_args;

  bool inQuote = false;
  bool inApostrophe = false;
  String buffer = "";

  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);

    if (c == '"') {
      // Check if the quote is within an apostrophe
      if (inApostrophe) {
        buffer += c;
      } else {
        inQuote = !inQuote;
      }
    } else if (c == '\'') {
      // Check if the apostrophe is within a quote
      if (inQuote) {
        buffer += c;
      } else {
        inApostrophe = !inApostrophe;
      }
    } else if (!inQuote && !inApostrophe && strchr(delim, c) != NULL) {
      cmd_args.push_back(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }

  // Add the last argument
  if (!buffer.isEmpty()) {
    cmd_args.push_back(buffer);
  }

  return cmd_args;
}

int CommandLine::argSearch(std::vector<String>& cmd_args_list, String key) {
  for (size_t i = 0; i < cmd_args_list.size(); i++) {
    if (cmd_args_list[i] == key)
      return i;
  }

  return -1;
}

bool CommandLine::checkValueExists(std::vector<String>* cmd_args_list, int index) {
  if (index < cmd_args_list->size() - 1)
    return true;

  return false;
}

bool CommandLine::inRange(int max, int index) {
  if ((index >= 0) && (index < (int)access_points->size()))
    return true;

  return false;
}

bool CommandLine::apSelected() {
  for (size_t i = 0; i < access_points->size(); i++) {
    if ((*access_points)[i].selected) {
      return true;
    }
  }

  return false;
}

bool CommandLine::hasSSIDs() {
  if (ssids->size() == 0)
    return false;

  return true;
}

void CommandLine::showCounts(int selected, int unselected) {
  Serial.print(String(selected) + " selected");

  if (unselected != -1)
    Serial.print(", " + (String) unselected + " unselected");

  Serial.println("");
}

String CommandLine::toLowerCase(String str) {
  String result = str;
  for (int i = 0; i < str.length(); i++) {
    int charValue = str.charAt(i);
    if (charValue >= 65 && charValue <= 90) { // ASCII codes for uppercase letters
      charValue += 32;
      result.setCharAt(i, char(charValue));
    }
  }
  return result;
}

void CommandLine::filterAccessPoints(String filter) {
  int count_selected = 0;
  int count_unselected = 0;

  // Split the filter string into individual filters
  std::vector<String> filters;
  int start = 0;
  int end = filter.indexOf(" or ");
  while (end != -1) {
    filters.push_back(filter.substring(start, end));
    start = end + 4;
    end = filter.indexOf(" or ", start);
  }
  filters.push_back(filter.substring(start));

  // Loop over each access point and check if it matches any of the filters
  for (int i = 0; i < (int)access_points->size(); i++) {
    bool matchesFilter = false;
    for (int j = 0; j < (int)filters.size(); j++) {
      String f = toLowerCase(filters[j]);
      if (f.substring(0, 7) == "equals ") {
        String ssidEquals = f.substring(7);
        if ((ssidEquals.charAt(0) == '\"' && ssidEquals.charAt(ssidEquals.length() - 1) == '\"' && ssidEquals.length() > 1) ||
            (ssidEquals.charAt(0) == '\'' && ssidEquals.charAt(ssidEquals.length() - 1) == '\'' && ssidEquals.length() > 1)) {
          ssidEquals = ssidEquals.substring(1, ssidEquals.length() - 1);
        }
        if ((*access_points)[i].essid.equalsIgnoreCase(ssidEquals)) {
          matchesFilter = true;
          break;
        }
      } else if (f.substring(0, 9) == "contains ") {
        String ssidContains = f.substring(9);
        if ((ssidContains.charAt(0) == '\"' && ssidContains.charAt(ssidContains.length() - 1) == '\"' && ssidContains.length() > 1) ||
            (ssidContains.charAt(0) == '\'' && ssidContains.charAt(ssidContains.length() - 1) == '\'' && ssidContains.length() > 1)) {
          ssidContains = ssidContains.substring(1, ssidContains.length() - 1);
        }
        String essid = toLowerCase((*access_points)[i].essid);
        if (essid.indexOf(ssidContains) != -1) {
          matchesFilter = true;
          break;
        }
      }
    }
    // Toggles the selected state of the AP
    AccessPoint new_ap = (*access_points)[i];
    new_ap.selected = matchesFilter;
    (*access_points)[i] = new_ap;

    if (matchesFilter) {
      count_selected++;
    } else {
      count_unselected++;
    }
  }

  this->showCounts(count_selected, count_unselected);
}

void CommandLine::runCommand(String input) {
  if (input == "") return;

  if(wifi_scan_obj.scanning() && wifi_scan_obj.currentScanMode == WIFI_SCAN_GPS_NMEA){
    if(input != STOPSCAN_CMD) return;
  }
  else
    Serial.println("#" + input);

  std::vector<String> cmd_args = this->parseCommand(input, " ");

  //// Admin commands
  // Help
  if (cmd_args[0] == HELP_CMD) {
    Serial.println(F("============ Comandos Disponiveis ============"));
    Serial.println(F(" channel -s <canal>       -> Define o canal WiFi"));
    Serial.println(F(" settings                 -> Mostra as configuracoes"));
    Serial.println(F(" clearap -a|-s|-c         -> Limpa listas de APs, SSIDs ou Estacoes"));
    Serial.println(F(" reboot                   -> Reinicia o dispositivo"));
    Serial.println(F(" update -s                -> Atualiza o firmware via SD"));
    Serial.println(F(" ls <dir>                 -> Lista arquivos no cartao SD"));
    Serial.println(F(" led -s <hex>             -> Define a cor do LED (se aplicavel)"));
    Serial.println(F(" gpsdata                  -> Mostra dados do GPS em tempo real"));
    Serial.println(F(" gps -g <info>            -> Obtem informacao especifica do GPS"));
    Serial.println(F(" nmea                     -> Inicia o stream de sentencas NMEA"));
    Serial.println(F("\n--- Varredura e Sniffing WiFi ---"));
    Serial.println(F(" evilportal -c start      -> Inicia o ataque Evil Portal"));
    Serial.println(F(" packetcount              -> Conta pacotes por segundo"));
    Serial.println(F(" sigstrength              -> Mede a forca do sinal WiFi"));
    Serial.println(F(" scanall                  -> Varre APs e Estacoes"));
    Serial.println(F(" scanap                   -> Varre apenas Access Points"));
    Serial.println(F(" scansta                  -> Varre apenas Estacoes"));
    Serial.println(F(" sniffraw                 -> Captura pacotes raw 802.11"));
    Serial.println(F(" sniffbeacon              -> Captura pacotes Beacon"));
    Serial.println(F(" sniffprobe               -> Captura pacotes Probe Request"));
    Serial.println(F(" sniffpwn                 -> Captura handshakes (Pwnagotchi)"));
    Serial.println(F(" sniffesp                 -> Detecta dispositivos Espressif"));
    Serial.println(F(" sniffdeauth              -> Captura pacotes de Deauth"));
    Serial.println(F(" sniffpmkid               -> Captura PMKIDs"));
    Serial.println(F(" stopscan                 -> Para todas as varreduras e ataques"));
    #ifdef HAS_GPS
      Serial.println(F(" wardrive                 -> Inicia Wardriving (APs)"));
    #endif
    Serial.println(F("\n--- Ataques WiFi ---"));
    Serial.println(F(" attack -t <tipo> [...]   -> Inicia um ataque (use 'attack -h' para ajuda)"));
    Serial.println(F("\n--- Comandos Auxiliares ---"));
    Serial.println(F(" info -a <indice>         -> Mostra informacoes de um AP"));
    Serial.println(F(" list -a|-s|-c            -> Lista APs, SSIDs ou Estacoes"));
    Serial.println(F(" select -a|-s|-c <indices>-> Seleciona itens para ataques"));
    Serial.println(F(" ssid -a -n <nome>        -> Adiciona um SSID a lista"));
    Serial.println(F(" save -a|-s               -> Salva a lista de APs ou SSIDs"));
    Serial.println(F(" load -a|-s               -> Carrega a lista de APs ou SSIDs"));
    Serial.println(F("\n--- Bluetooth ---"));
    #ifdef HAS_BT
      Serial.println(F(" btsniff                  -> Inicia a varredura de dispositivos Bluetooth"));
      Serial.println(F(" btspam -t <tipo>         -> Inicia ataques de spam Bluetooth"));
      Serial.println(F(" btspoof -t <indice>      -> Spoof de um dispositivo (ex: AirTag)"));
      #ifdef HAS_GPS
        Serial.println(F(" btwardrive               -> Inicia Wardriving Bluetooth"));
      #endif
      Serial.println(F(" btskim                   -> Detecta skimmers de cartao BLE"));
    #endif
    Serial.println(F("=============================================="));
    return;
  }

  // Stop Scan
  if (cmd_args[0] == STOPSCAN_CMD) {
    //if (wifi_scan_obj.currentScanMode == OTA_UPDATE) {
    //  wifi_scan_obj.currentScanMode = WIFI_SCAN_OFF;
    //#ifdef HAS_SCREEN
    //  menu_function_obj.changeMenu(menu_function_obj.updateMenu.parentMenu);
    //#endif
    //  WiFi.softAPdisconnect(true);
    //  web_obj.shutdownServer();
    //  return;
    //}

    uint8_t old_scan_mode=wifi_scan_obj.currentScanMode;

    wifi_scan_obj.StartScan(WIFI_SCAN_OFF);

    if(old_scan_mode == WIFI_SCAN_GPS_NMEA)
      Serial.println("FIM DO STREAM NMEA");
    else if(old_scan_mode == WIFI_SCAN_GPS_DATA)
      Serial.println("Parando atualizacoes de dados GPS");
    else
      Serial.println("Parando transmissao/recepcao WiFi");

    // If we don't do this, the text and button coordinates will be off
    #ifdef HAS_SCREEN
      display_obj.tft.init();
      menu_function_obj.changeMenu(menu_function_obj.current_menu);
    #endif
  }
  else if (cmd_args[0] == GPS_DATA_CMD) {
    #ifdef HAS_GPS
      if (gps_obj.getGpsModuleStatus()) {
        Serial.println("Obtendo dados do GPS. Pare com " + (String)STOPSCAN_CMD);
        wifi_scan_obj.currentScanMode = WIFI_SCAN_GPS_DATA;
        #ifdef HAS_SCREEN
          menu_function_obj.changeMenu(&menu_function_obj.gpsInfoMenu);
        #endif
        wifi_scan_obj.StartScan(WIFI_SCAN_GPS_DATA, TFT_CYAN);
      }
    #endif
  }
  else if (cmd_args[0] == GPS_CMD) {
    #ifdef HAS_GPS
      if (gps_obj.getGpsModuleStatus()) {
        int get_arg = this->argSearch(cmd_args, "-g");
        int nmea_arg = this->argSearch(cmd_args, "-n");

        if (get_arg != -1) {
          String gps_info = cmd_args[get_arg + 1];

          if (gps_info == "fix")
            Serial.println("Fixacao: " + gps_obj.getFixStatusAsString());
          else if (gps_info == "sat")
            Serial.println("Satelites: " + gps_obj.getNumSatsString());
          else if (gps_info == "lat")
            Serial.println("Latitude: " + gps_obj.getLat());
          else if (gps_info == "lon")
            Serial.println("Longitude: " + gps_obj.getLon());
          else if (gps_info == "alt")
            Serial.println("Altitude: " + (String)gps_obj.getAlt());
          else if (gps_info == "accuracy")
            Serial.println("Precisao: " + (String)gps_obj.getAccuracy());
          else if (gps_info == "date")
            Serial.println("Data/Hora: " + gps_obj.getDatetime());
          else if (gps_info == "text"){
            Serial.println(gps_obj.getText());
          }
          else if (gps_info == "nmea"){
            int notparsed_arg = this->argSearch(cmd_args, "-p");
            int notimp_arg = this->argSearch(cmd_args, "-i");
            int recd_arg = this->argSearch(cmd_args, "-r");
            if(notparsed_arg == -1 && notimp_arg == -1 && recd_arg == -1){
              Serial.println(gps_obj.generateGXgga());
              Serial.println(gps_obj.generateGXrmc());
            }
            else if(notparsed_arg == -1 && notimp_arg == -1)
              Serial.println(gps_obj.getNmea());
            else if(notparsed_arg == -1)
              Serial.println(gps_obj.getNmeaNotimp());
            else
              Serial.println(gps_obj.getNmeaNotparsed());
          }
          else
            Serial.println("Erro: Argumento inválido.");
        }
        else if(nmea_arg != -1) {
          String nmea_type = cmd_args[nmea_arg + 1];

          if (nmea_type == "native" || nmea_type == "all" || nmea_type == "gps" || nmea_type == "glonass"
              || nmea_type == "galileo" || nmea_type == "navic" || nmea_type == "qzss" || nmea_type == "beidou"){
            if(nmea_type == "beidou"){
              int beidou_bd_arg = this->argSearch(cmd_args, "-b");
              if(beidou_bd_arg != -1) {
                nmea_type="beidou_bd";
            }
            int type_int = nmea_type.toInt();
            gps_obj.setType(type_int);
            Serial.println("Tipo de saida GPS definido para: " + nmea_type);
          }
          else
            Serial.println("Erro: Argumento inválido.");
        }
        else if(cmd_args.size() > 1)
          Serial.println("Erro: Flag inválida.");
        else
          Serial.println("Nenhum argumento fornecido");
      }
    #endif
  }
  else if (cmd_args[0] == NMEA_CMD) {
    #ifdef HAS_GPS
      if (gps_obj.getGpsModuleStatus()) {
        #ifdef HAS_SCREEN
          menu_function_obj.changeMenu(&menu_function_obj.gpsInfoMenu);
        #endif
        Serial.println("NMEA STREAM FOLLOWS");
        wifi_scan_obj.currentScanMode = WIFI_SCAN_GPS_NMEA;
        wifi_scan_obj.StartScan(WIFI_SCAN_GPS_NMEA, TFT_CYAN);
      }
    #endif
  }
  // LED command
  else if (cmd_args[0] == LED_CMD) {
    int hex_arg = this->argSearch(cmd_args, "-s");
    int pat_arg = this->argSearch(cmd_args, "-p");
    #ifdef PIN
      if (hex_arg != -1) {
        String hexstring = cmd_args[hex_arg + 1];
        int number = (int)strtol(&hexstring[1], NULL, 16);
        int r = number >> 16;
        int g = number >> 8 & 0xFF;
        int b = number & 0xFF;
        //Serial.println(r);
        //Serial.println(g);
        //Serial.println(b);
        //led_obj.setColor(r, g, b);
        //led_obj.setMode(MODE_CUSTOM);
      }
    #else
      Serial.println("This hardware does not support neopixel");
    #endif
  }
  // ls command
  else if (cmd_args[0] == LS_CMD) {
    #ifdef HAS_SD
      if (cmd_args.size() > 1)
        sd_obj.listDir(cmd_args[1]);
      else
        Serial.println("Você não forneceu um diretório para listar");
    #else
      Serial.println("Suporte a SD desativado, nao e possivel usar o comando");
      return;
    #endif
  }

  // Channel command
  else if (cmd_args[0] == CH_CMD) {
    // Search for channel set arg
    int ch_set = this->argSearch(cmd_args, "-s");

    if (cmd_args.size() == 1) {
      Serial.println("Canal atual: " + (String)wifi_scan_obj.set_channel);
    }
    else if (ch_set != -1) {
      wifi_scan_obj.set_channel = cmd_args[ch_set + 1].toInt();
      wifi_scan_obj.changeChannel();
      Serial.println("Canal definido para: " + (String)wifi_scan_obj.set_channel);
    }
  }
  // Clear APs
  else if (cmd_args[0] == CLEARAP_CMD) {
    int ap_sw = this->argSearch(cmd_args, "-a"); // APs
    int ss_sw = this->argSearch(cmd_args, "-s"); // SSIDs
    int cl_sw = this->argSearch(cmd_args, "-c"); // Stations

    if (ap_sw != -1) {
      #ifdef HAS_SCREEN
        menu_function_obj.changeMenu(&menu_function_obj.clearAPsMenu);
      #endif
      wifi_scan_obj.RunClearAPs();
    }

    if (ss_sw != -1) {
      #ifdef HAS_SCREEN
        menu_function_obj.changeMenu(&menu_function_obj.clearSSIDsMenu);
      #endif
      wifi_scan_obj.RunClearSSIDs();
    }

    if (cl_sw != -1) {
      #ifdef HAS_SCREEN
        menu_function_obj.changeMenu(&menu_function_obj.clearAPsMenu);
      #endif
      wifi_scan_obj.RunClearStations();
    }
  }

  else if (cmd_args[0] == SETTINGS_CMD) {
    int ss_sw = this->argSearch(cmd_args, "-s"); // Set setting
    int re_sw = this->argSearch(cmd_args, "-r"); // Reset setting
    int en_sw = this->argSearch(cmd_args, "enable"); // enable setting
    int da_sw = this->argSearch(cmd_args, "disable"); // disable setting

    if (re_sw != -1) {
      settings_obj.createDefaultSettings(SPIFFS);
      return;
    }

    if (ss_sw == -1) {
      settings_obj.printJsonSettings(settings_obj.getSettingsString());
    }
    else {
      bool result = false;
      String setting_name = cmd_args[ss_sw + 1];
      if (en_sw != -1)
        result = settings_obj.saveSetting<bool>(setting_name, true);
      else if (da_sw != -1)
        result = settings_obj.saveSetting<bool>(setting_name, false);
      else {
        Serial.println("Voce nao ativou/desativou esta configuracao corretamente.");
        return;
      }

      if (!result) {
        Serial.println("Nao foi possivel atualizar a configuracao \"" + setting_name + "\"");
        return;
      }
    }
  }

  else if (cmd_args[0] == REBOOT_CMD) {
    Serial.println("Reiniciando...");
    ESP.restart();
  }

  //// WiFi/Bluetooth Scan/Attack commands
  if (!wifi_scan_obj.scanning()) {
    // Dump pcap/log to serial too, valid for all scan/attack commands
    wifi_scan_obj.save_serial = this->argSearch(cmd_args, "-serial") != -1;

    // Signal strength scan
    if (cmd_args[0] == SIGSTREN_CMD) {
      Serial.println("Starting Signal Strength Scan. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_SIG_STREN, TFT_MAGENTA);
      wifi_scan_obj.renderPacketRate();
    }
    // Packet count
    else if (cmd_args[0] == PACKET_COUNT_CMD) {
      Serial.println("Starting Packet Count Scan. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_PACKET_RATE, TFT_ORANGE);
      // wifi_scan_obj.renderPacketRate(); // Método não implementado, comentado
    }
    // Wardrive
    else if (cmd_args[0] == WARDRIVE_CMD) {
      #ifdef HAS_GPS
        if (gps_obj.getGpsModuleStatus()) {
          int sta_sw = this->argSearch(cmd_args, "-s");

          if (sta_sw == -1) {
            Serial.println("Starting Wardrive. Stop with " + (String)STOPSCAN_CMD);
            #ifdef HAS_SCREEN
              display_obj.clearScreen();
              menu_function_obj.drawStatusBar();
            #endif
            wifi_scan_obj.StartScan(WIFI_SCAN_WAR_DRIVE, TFT_GREEN);
          }
          else {Serial.println("Starting Station Wardrive. Stop with " + (String)STOPSCAN_CMD);
            #ifdef HAS_SCREEN
              display_obj.clearScreen();
              menu_function_obj.drawStatusBar();
            #endif
            wifi_scan_obj.StartScan(WIFI_SCAN_STATION_WAR_DRIVE, TFT_GREEN);
          }
        }
        else
          Serial.println("GPS Module not detected");
      #else
        Serial.println("GPS not supported");
      #endif
    }
    // AP Scan
    else if (cmd_args[0] == EVIL_PORTAL_CMD) {
      int cmd_sw = this->argSearch(cmd_args, "-c");
      int html_sw = this->argSearch(cmd_args, "-w");

      if (cmd_sw != -1) {
        String et_command = cmd_args[cmd_sw + 1];
        if (et_command == "start") {
          Serial.println("Starting Evil Portal. Stop with " + (String)STOPSCAN_CMD);
          #ifdef HAS_SCREEN
            display_obj.clearScreen();
            menu_function_obj.drawStatusBar();
          #endif
          if (html_sw != -1) {
            String target_html_name = cmd_args[html_sw + 1];
            evil_portal_obj.target_html_name = target_html_name;
            evil_portal_obj.using_serial_html = false;
            Serial.println("Set html file as " + evil_portal_obj.target_html_name);
          }
          //else {
          //  evil_portal_obj.target_html_name = "index.html";
          //}
          wifi_scan_obj.StartScan(WIFI_SCAN_EVIL_PORTAL, TFT_MAGENTA);
        }
        else if (et_command == "reset") {

        }
        else if (et_command == "ack") {

        }
        else if (et_command == "sethtml") {
          String target_html_name = cmd_args[cmd_sw + 2];
          evil_portal_obj.target_html_name = target_html_name;
          evil_portal_obj.using_serial_html = false;
          Serial.println("Set html file as " + evil_portal_obj.target_html_name);
        }
        else if (et_command == "sethtmlstr") {
          evil_portal_obj.setHtmlFromSerial();
        }
        else if (et_command == "setap") {

        }
      }
    }
    else if (cmd_args[0] == SCAN_ALL_CMD) {
      Serial.println("Scanning for APs and Stations. Stop with " + (String)STOPSCAN_CMD);
      wifi_scan_obj.StartScan(WIFI_SCAN_AP_STA, TFT_MAGENTA);
    }
    else if (cmd_args[0] == SCANAP_CMD) {
      int full_sw = -1;
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif

      if (full_sw == -1) {
        Serial.println("Starting AP scan. Stop with " + (String)STOPSCAN_CMD);
        wifi_scan_obj.StartScan(WIFI_SCAN_TARGET_AP, TFT_MAGENTA);
      }
      else {
        Serial.println("Starting Full AP scan. Stop with " + (String)STOPSCAN_CMD);
        wifi_scan_obj.StartScan(WIFI_SCAN_TARGET_AP_FULL, TFT_MAGENTA);
      }
    }
    // Raw sniff
    else if (cmd_args[0] == SNIFF_RAW_CMD) {
      Serial.println("Starting Raw sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_RAW_CAPTURE, TFT_WHITE);
    }
    // Scan stations
    else if (cmd_args[0] == SCANSTA_CMD) {
      if(access_points->size() < 1)
        Serial.println("The AP list is empty. Scan APs first with " + (String)SCANAP_CMD);

      Serial.println("Starting Station scan. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_STATION, TFT_ORANGE);
    }
    // Beacon sniff
    else if (cmd_args[0] == SNIFF_BEACON_CMD) {
      Serial.println("Starting Beacon sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_AP, TFT_MAGENTA);
    }
    // Probe sniff
    else if (cmd_args[0] == SNIFF_PROBE_CMD) {
      Serial.println("Starting Probe sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_PROBE, TFT_MAGENTA);
    }
    // Deauth sniff
    else if (cmd_args[0] == SNIFF_DEAUTH_CMD) {
      Serial.println("Starting Deauth sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_DEAUTH, TFT_RED);
    }
    // Pwn sniff
    else if (cmd_args[0] == SNIFF_PWN_CMD) {
      Serial.println("Starting Pwnagotchi sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_PWN, TFT_MAGENTA);
    }
    // Espressif sniff
    else if (cmd_args[0] == SNIFF_ESP_CMD) {
      Serial.println("Starting Espressif device sniff. Stop with " + (String)STOPSCAN_CMD);
      #ifdef HAS_SCREEN
        display_obj.clearScreen();
        menu_function_obj.drawStatusBar();
      #endif
      wifi_scan_obj.StartScan(WIFI_SCAN_ESPRESSIF, TFT_MAGENTA);
    }
    // PMKID sniff
    else if (cmd_args[0] == SNIFF_PMKID_CMD) {
      int ch_sw = this->argSearch(cmd_args, "-c");
      int d_sw = this->argSearch(cmd_args, "-d"); // Deauth for pmkid
      int l_sw = this->argSearch(cmd_args, "-l"); // Only run on list

      if (l_sw != -1) {
        if (!this->apSelected()) {
          Serial.println("You don't have any targets selected. Use " + (String)SEL_CMD);
          return;
        }
      }

      if (ch_sw != -1) {
        wifi_scan_obj.set_channel = cmd_args[ch_sw + 1].toInt();
        wifi_scan_obj.changeChannel();
        Serial.println("Set channel: " + (String)wifi_scan_obj.set_channel);

      }

      if (d_sw == -1) {
        Serial.println("Starting PMKID sniff on channel " + (String)wifi_scan_obj.set_channel + ". Stop with " + (String)STOPSCAN_CMD);
        wifi_scan_obj.StartScan(WIFI_SCAN_EAPOL, TFT_VIOLET);
      }
      else if ((d_sw != -1) && (l_sw != -1)) {
        Serial.println("Starting TARGETED PMKID sniff with deauthentication on channel " + (String)wifi_scan_obj.set_channel + ". Stop with " + (String)STOPSCAN_CMD);
        wifi_scan_obj.StartScan(WIFI_SCAN_ACTIVE_LIST_EAPOL, TFT_VIOLET);
      }
      else {
        Serial.println("Starting PMKID sniff with deauthentication on channel " + (String)wifi_scan_obj.
