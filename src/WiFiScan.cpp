#include "WiFiScan.h"
#include "lang_var.h"
#include "TouchDrvGT911.hpp"
//#include "MenuFunctions.h"

TouchDrvGT911 touch;

#if defined(CYD_24CAP) || defined(CYD_22CAP)
#include <bb_captouch.h>
#endif


bool was_pressed = false;
int8_t last_released = -1;
unsigned long last_release_time = 0;


int num_beacon = 0;
int num_deauth = 0;
int num_probe = 0;
int num_eapol = 0;

std::vector<ssid>* ssids;
std::vector<AccessPoint>* access_points;
std::vector<Station>* stations;
std::vector<AirTag>* airtags;
std::vector<Flipper>* flippers;

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3){
    if (arg == 31337)
      return 1;
    else
      return 0;
}

extern "C" {
  uint8_t esp_base_mac_addr[6];
  esp_err_t esp_ble_gap_set_rand_addr(const uint8_t *rand_addr);
}

#ifdef HAS_BT
  //ESP32 Sour Apple by RapierXbox
  //Exploit by ECTO-1A
  NimBLEAdvertising *pAdvertising;

  //// https://github.com/Spooks4576
  NimBLEAdvertisementData WiFiScan::GetUniversalAdvertisementData(EBLEPayloadType Type) {
    NimBLEAdvertisementData AdvData = NimBLEAdvertisementData();

    uint8_t* AdvData_Raw = nullptr;
    uint8_t i = 0;

    switch (Type) {
      case Microsoft: {

        const char* Name = generateRandomName();

        uint8_t name_len = strlen(Name);

        AdvData_Raw = new uint8_t[7 + name_len];

        AdvData_Raw[i++] = 7 + name_len - 1;
        AdvData_Raw[i++] = 0xFF;
        AdvData_Raw[i++] = 0x06;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x03;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x80;
        memcpy(&AdvData_Raw[i], Name, name_len);
        i += name_len;

        std::vector<uint8_t> advDataRawVector(AdvData_Raw.begin(), AdvData_Raw.end());
        AdvData.addData(advDataRawVector.data(), 7 + name_len);
        break;
      }
      case Apple: {
        AdvData_Raw = new uint8_t[17];

        AdvData_Raw[i++] = 17 - 1;    // Packet Length
        AdvData_Raw[i++] = 0xFF;        // Packet Type (Manufacturer Specific)
        AdvData_Raw[i++] = 0x4C;        // Packet Company ID (Apple, Inc.)
        AdvData_Raw[i++] = 0x00;        // ...
        AdvData_Raw[i++] = 0x0F;  // Type
        AdvData_Raw[i++] = 0x05;                        // Length
        AdvData_Raw[i++] = 0xC1;                        // Action Flags
        const uint8_t types[] = { 0x27, 0x09, 0x02, 0x1e, 0x2b, 0x2d, 0x2f, 0x01, 0x06, 0x20, 0xc0 };
        AdvData_Raw[i++] = types[rand() % sizeof(types)];  // Action Type
        esp_fill_random(&AdvData_Raw[i], 3); // Authentication Tag
        i += 3;
        AdvData_Raw[i++] = 0x00;  // ???
        AdvData_Raw[i++] = 0x00;  // ???
        AdvData_Raw[i++] =  0x10;  // Type ???
        esp_fill_random(&AdvData_Raw[i], 3);

        std::vector<uint8_t> advDataRawVector(AdvData_Raw.begin(), AdvData_Raw.end());
        AdvData.addData(advDataRawVector.data(), 17);
        break;
      }
      case Samsung: {

        AdvData_Raw = new uint8_t[15];

        uint8_t model = watch_models[rand() % 25].value;

        AdvData_Raw[i++] = 14; // Size
        AdvData_Raw[i++] = 0xFF; // AD Type (Manufacturer Specific)
        AdvData_Raw[i++] = 0x75; // Company ID (Samsung Electronics Co. Ltd.)
        AdvData_Raw[i++] = 0x00; // ...
        AdvData_Raw[i++] = 0x01;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x02;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x01;
        AdvData_Raw[i++] = 0x01;
        AdvData_Raw[i++] = 0xFF;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x00;
        AdvData_Raw[i++] = 0x43;
        AdvData_Raw[i++] = (model >> 0x00) & 0xFF; // Watch Model / Color (?)

        std::vector<uint8_t> advDataRawVector(AdvData_Raw.begin(), AdvData_Raw.end());
        AdvData.addData(advDataRawVector.data(), 15);

        break;
      }
      case Google: {
        AdvData_Raw = new uint8_t[14];
        AdvData_Raw[i++] = 3;
        AdvData_Raw[i++] = 0x03;
        AdvData_Raw[i++] = 0x2C; // Fast Pair ID
        AdvData_Raw[i++] = 0xFE;

        AdvData_Raw[i++] = 6;
        AdvData_Raw[i++] = 0x16;
        AdvData_Raw[i++] = 0x2C; // Fast Pair ID
        AdvData_Raw[i++] = 0xFE;
        AdvData_Raw[i++] = 0x00; // Smart Controller Model ID
        AdvData_Raw[i++] = 0xB7;
        AdvData_Raw[i++] = 0x27;

        AdvData_Raw[i++] = 2;
        AdvData_Raw[i++] = 0x0A;
        AdvData_Raw[i++] = (rand() % 120) - 100; // -100 to +20 dBm

        std::vector<uint8_t> advDataRawVector(AdvData_Raw.begin(), AdvData_Raw.end());
        AdvData.addData(advDataRawVector.data(), 14);
        break;
      }
      case FlipperZero: {
        // Generate a random 5-letter name for the advertisement
        char Name[6];  // 5 characters + null terminator
        generateRandomName(Name, sizeof(Name));

        uint8_t name_len = strlen(Name);
// Allocate space for the full Advertisement Data section based on the hex dump
std::vector<uint8_t> AdvData_Raw;

// Advertisement Data from the hex dump
AdvData_Raw.push_back(0x02);  // Flags length
AdvData_Raw.push_back(0x01);  // Flags type
AdvData_Raw.push_back(0x06);  // Flags value

AdvData_Raw.push_back(0x06);  // Name length (5 + type)
AdvData_Raw.push_back(0x09);  // Complete Local Name type

// Add the randomized 5-letter name
AdvData_Raw.insert(AdvData_Raw.end(), Name, Name + name_len);

AdvData_Raw.push_back(0x03);  // Incomplete List of 16-bit Service UUIDs length
AdvData_Raw.push_back(0x02);  // Incomplete List of 16-bit Service UUIDs type
AdvData_Raw.push_back(0x80 + (rand() % 3) + 1);   // Service UUID (part of hex dump)
AdvData_Raw.push_back(0x30);

AdvData_Raw.push_back(0x02);  // TX Power level length
AdvData_Raw.push_back(0x0A);  // TX Power level type
AdvData_Raw.push_back(0x00);  // TX Power level value

// Manufacturer specific data based on your hex dump
AdvData_Raw.push_back(0x05);  // Length of Manufacturer Specific Data section
AdvData_Raw.push_back(0xFF);  // Manufacturer Specific Data type
AdvData_Raw.push_back(0xBA);  // LSB of Manufacturer ID (Flipper Zero: 0x0FBA)
AdvData_Raw.push_back(0x0F);  // MSB of Manufacturer ID

AdvData_Raw.push_back(0x4C);  // Example data (remaining as in your dump)
AdvData_Raw.push_back(0x75);
AdvData_Raw.push_back(0x67);
AdvData_Raw.push_back(0x26);
AdvData_Raw.push_back(0xE1);
AdvData_Raw.push_back(0x80);

// Add the constructed Advertisement Data to the BLE advertisement
AdvData.addData(AdvData_Raw.data(), AdvData_Raw.size());

break;

      case Airtag: {
        for (int i = 0; i < airtags->size(); i++) {
          if (airtags->at(i).selected) {
            AdvData.addData(airtags->at(i).payload.data(), airtags->at(i).payloadSize);

            break;
          }
        }

        break;
      }
      default: {
        Serial.println("Please Provide a Company Type");
        break;
      }
    }


    return AdvData;
  }
  //// https://github.com/Spooks4576


  class BluetoothScanAllCallback : public NimBLEAdvertisedDeviceCallbacks {

    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {

        extern WiFiScan wifi_scan_obj;

        //#ifdef HAS_SCREEN
        //  int buf = display_obj.display_buffer->size();
        //#else
        int buf = 0;
        //#endif

        String display_string = "";

        if (wifi_scan_obj.currentScanMode == BT_SCAN_AIRTAG) {
          const std::vector<uint8_t>& payLoad = advertisedDevice->getPayloadData();
          size_t len = payLoad.size();

          bool match = false;
          for (int i = 0; i <= (int)payLoad.size() - 4; i++) {
            if (payLoad[i] == 0x1E && payLoad[i+1] == 0xFF && payLoad[i+2] == 0x4C && payLoad[i+3] == 0x00) {
              match = true;
              break;
            }
            if (payLoad[i] == 0x4C && payLoad[i+1] == 0x00 && payLoad[i+2] == 0x12 && payLoad[i+3] == 0x19) {
              match = true;
              break;
            }
          }

          if (match) {
            String mac = advertisedDevice->getAddress().toString().c_str();
            mac.toUpperCase();

            for (int i = 0; i < airtags->size(); i++) {
              if (mac == airtags->at(i).mac)
                return;
            }

            int rssi = advertisedDevice->getRSSI();
            Serial.print("RSSI: ");
            Serial.print(rssi);
            Serial.print(" MAC: ");
            Serial.println(mac);
            Serial.print("Len: ");
            Serial.print(len);
            Serial.print(" Payload: ");
            for (size_t i = 0; i < len; i++) {
              Serial.printf("%02X ", payLoad[i]);
            }
            Serial.println("\n");

            AirTag airtag;
            airtag.mac = mac;
            airtag.payload.assign(payLoad.begin(), payLoad.end());
            airtag.payloadSize = len;

            airtags->push_back(airtag);


            #ifdef HAS_SCREEN
              //display_string.concat("RSSI: ");
              display_string.concat((String)rssi);
              display_string.concat(" MAC: ");
              display_string.concat(mac);
              uint8_t temp_len = display_string.length();
              for (uint8_t i = 0; i < 40 - temp_len; i++)
              {
                display_string.concat(" ");
              }
              display_obj.display_buffer->push_back(display_string);
            #endif
          }
        }
        else if (wifi_scan_obj.currentScanMode == BT_SCAN_FLIPPER) {
          const std::vector<uint8_t>& payLoad = advertisedDevice->getPayloadData();
          size_t len = payLoad.size();

          bool match = false;
          String color = "";
          for (int i = 0; i <= (int)payLoad.size() - 4; i++) {
            if (payLoad[i] == 0x81 && payLoad[i+1] == 0x30) {
              match = true;
              color = "Black";
              break;
            }
            if (payLoad[i] == 0x82 && payLoad[i+1] == 0x30) {
              match = true;
              color = "White";
              break;
            }
            if (payLoad[i] == 0x83 && payLoad[i+1] == 0x30) {
              color = "Transparent";
              match = true;
              break;
            }
          }

          if (match) {
            String mac = advertisedDevice->getAddress().toString().c_str();
            String name = advertisedDevice->getName().c_str();
            mac.toUpperCase();

            for (int i = 0; i < flippers->size(); i++) {
              if (mac == flippers->at(i).mac)
                return;
            }

            int rssi = advertisedDevice->getRSSI();
            Serial.print("RSSI: ");
            Serial.print(rssi);
            Serial.print(" MAC: ");
            Serial.println(mac);
            Serial.print("Name: ");
            Serial.println(name);

            Flipper flipper;
            flipper.mac = mac;
            flipper.name = name;

            flippers->push_back(flipper);


            /*#ifdef HAS_SCREEN
              //display_string.concat("RSSI: ");
              display_string.concat((String)rssi);
              display_string.concat(" Flipper: ");
              display_string.concat(name);
              uint8_t temp_len = display_string.length();
              for (uint8_t i = 0; i < 40 - temp_len; i++)
              {
                display_string.concat(" ");
              }
              display_obj.display_buffer->push_back(display_string);
            #endif*/

            #ifdef HAS_SCREEN
              display_obj.display_buffer->push_back(String("Flipper: ") + name + ",                 ");
              display_obj.display_buffer->push_back("       MAC: " + String(mac) + ",             ");
              display_obj.display_buffer->push_back("      RSSI: " + String(rssi) + ",               ");
              display_obj.display_buffer->push_back("     Color: " + String(color) + "                ");
            #endif
          }
        }
        else if (wifi_scan_obj.currentScanMode == BT_SCAN_ALL) {
          if (buf >= 0)
          {
            display_string.concat(text_table4[0]);
            display_string.concat(advertisedDevice->getRSSI());
            Serial.print(" RSSI: ");
            Serial.print(advertisedDevice->getRSSI());

            display_string.concat(" ");
            Serial.print(" ");

            Serial.print("Device: ");
            if(advertisedDevice->getName().length() != 0)
            {
              display_string.concat(advertisedDevice->getName().c_str());
              Serial.print(advertisedDevice->getName().c_str());

            }
            else
            {
              display_string.concat(advertisedDevice->getAddress().toString().c_str());
              Serial.print(advertisedDevice->getAddress().toString().c_str());
            }

            #ifdef HAS_SCREEN
              uint8_t temp_len = display_string.length();
              for (uint8_t i = 0; i < 40 - temp_len; i++)
              {
                display_string.concat(" ");
              }

              Serial.println();

              while (display_obj.printing)
                delay(1);
              display_obj.loading = true;
              display_obj.display_buffer->push_back(display_string);
              display_obj.loading = false;
            #endif
          }
        }
        else if ((wifi_scan_obj.currentScanMode == BT_SCAN_WAR_DRIVE)  || (wifi_scan_obj.currentScanMode == BT_SCAN_WAR_DRIVE_CONT)) {
          #ifdef HAS_GPS
            if (gps_obj.getGpsModuleStatus()) {
              bool do_save = false;
              if (buf >= 0)
              {
                Serial.print("Device: ");
                if(advertisedDevice->getName().length() != 0)
                {
                  display_string.concat(advertisedDevice->getName().c_str());
                  Serial.print(advertisedDevice->getName().c_str());

                }
                else
                {
                  display_string.concat(advertisedDevice->getAddress().toString().c_str());
                  Serial.print(advertisedDevice->getAddress().toString().c_str());
                }

                if (gps_obj.getFixStatus()) {
                  do_save = true;
                  display_string.concat(" | Lt: " + gps_obj.getLat());
                  display_string.concat(" | Ln: " + gps_obj.getLon());
                }
                else {
                  display_string.concat(" | GPS: No Fix");
                }

                #ifdef HAS_SCREEN
                  uint8_t temp_len = display_string.length();
                  for (uint8_t i = 0; i < 40 - temp_len; i++)
                  {
                    display_string.concat(" ");
                  }

                  Serial.println();

                  unsigned long currentMillis = millis();
                  if (currentMillis - previousMillis >= interval) {
                    previousMillis = currentMillis;
                    display_obj.loading = true;
                    display_obj.display_buffer->push_back(display_string);
                    display_obj.loading = false;
                  }
                #endif

                String wardrive_line = (String)advertisedDevice->getAddress().toString().c_str() + ",,[BLE]," + gps_obj.getDatetime() + ",0," + (String)advertisedDevice->getRSSI() + "," + gps_obj.getLat() + "," + gps_obj.getLon() + "," + gps_obj.getAlt() + "," + gps_obj.getAccuracy() + ",BLE\n";
                Serial.print(wardrive_line);

                if (do_save)
                  buffer_obj.append(wardrive_line);
              }
            }
          #endif
        }
        else if (wifi_scan_obj.currentScanMode == BT_SCAN_ANALYZER) {
          wifi_scan_obj._analyzer_value++;

          if (wifi_scan_obj.analyzer_frames_recvd < 254)
            wifi_scan_obj.analyzer_frames_recvd++;

          if (wifi_scan_obj.analyzer_frames_recvd > ANALYZER_NAME_REFRESH) {
            display_string.concat(advertisedDevice->getRSSI());
            display_string.concat(" ");

            if(advertisedDevice->getName().length() != 0)
              display_string.concat(advertisedDevice->getName().c_str());
            else
              display_string.concat(advertisedDevice->getAddress().toString().c_str());

            wifi_scan_obj.analyzer_frames_recvd = 0;
            wifi_scan_obj.analyzer_name_string = display_string;
            wifi_scan_obj.analyzer_name_update = true;
          }
        }
      }
  };

#endif


WiFiScan::WiFiScan()
{
}

/*String WiFiScan::macToString(const Station& station) {
  char macStr[18]; // 6 pairs of hex digits + 5 colons + null terminator
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           station.mac[0], station.mac[1], station.mac[2],
           station.mac[3], station.mac[4], station.mac[5]);
  return String(macStr);
}*/

void WiFiScan::RunSetup() {
  if (ieee80211_raw_frame_sanity_check(31337, 0, 0) == 1)
    this->wsl_bypass_enabled = true;
  else
    this->wsl_bypass_enabled = false;

  ssids = new std::vector<ssid>();
  access_points = new std::vector<AccessPoint>();
  stations = new std::vector<Station>();
  airtags = new std::vector<AirTag>();
  flippers = new std::vector<Flipper>();

  #ifdef HAS_BT
    watch_models = new WatchModel[26] {
      {0x1A, "Fallback Watch"},
      {0x01, "White Watch4 Classic 44m"},
      {0x02, "Black Watch4 Classic 40m"},
      {0x03, "White Watch4 Classic 40m"},
      {0x04, "Black Watch4 44mm"},
      {0x05, "Silver Watch4 44mm"},
      {0x06, "Green Watch4 44mm"},
      {0x07, "Black Watch4 40mm"},
      {0x08, "White Watch4 40mm"},
      {0x09, "Gold Watch4 40mm"},
      {0x0A, "French Watch4"},
      {0x0B, "French Watch4 Classic"},
      {0x0C, "Fox Watch5 44mm"},
      {0x11, "Black Watch5 44mm"},
      {0x12, "Sapphire Watch5 44mm"},
      {0x13, "Purpleish Watch5 40mm"},
      {0x14, "Gold Watch5 40mm"},
      {0x15, "Black Watch5 Pro 45mm"},
      {0x16, "Gray Watch5 Pro 45mm"},
      {0x17, "White Watch5 44mm"},
      {0x18, "White & Black Watch5"},
      {0x1B, "Black Watch6 Pink 40mm"},
      {0x1C, "Gold Watch6 Gold 40mm"},
      {0x1D, "Silver Watch6 Cyan 44mm"},
      {0x1E, "Black Watch6 Classic 43m"},
      {0x20, "Green Watch6 Classic 43m"},
    };

    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
    NimBLEDevice::setScanDuplicateCacheSize(200);
    NimBLEDevice::init("");
    pBLEScan = NimBLEDevice::getScan(); // create new scan
    this->ble_initialized = true;

    this->shutdownBLE();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_AP_STA);
    esp_wifi_start();
    this->wifi_initialized = true;
    esp_wifi_get_mac(WIFI_IF_STA, this->sta_mac);
    delay(10);
    esp_wifi_get_mac(WIFI_IF_AP, this->ap_mac);
    this->setMac();
    this->shutdownWiFi();
  #endif

  this->initWiFi(1);
}

int WiFiScan::clearStations() {
  int num_cleared = stations->size();
  stations->clear();
  Serial.println("stations: " + (String)stations->size());

  // Now clear stations list from APs
  //for (int i = 0; i < access_points->size(); i++)
  // access_points->at(i).encryption = 0; // Ou o valor padrão apropriado para 'encryption'

  return num_cleared;
}

bool WiFiScan::checkMem() {
  #define MEM_LOWER_LIM 5000
  if (esp_get_free_heap_size() <= MEM_LOWER_LIM)
    return false;
  else
    return true;
}

int WiFiScan::clearAPs() {
  access_points->clear();
  Serial.println("access_points: " + (String)access_points->size());
  return 0;
}

int WiFiScan::clearAirtags() {
  int num_cleared = airtags->size();
  airtags->clear();
  Serial.println("airtags: " + (String)airtags->size());
  return num_cleared;
}

int WiFiScan::clearFlippers() {
  int num_cleared = flippers->size();
  flippers->clear();
  Serial.println("Flippers: " + (String)flippers->size());
  return num_cleared;
}

int WiFiScan::clearSSIDs() {
  int num_cleared = ssids->size();
  ssids->clear();
  Serial.println("ssids: " + (String)ssids->size());
  return num_cleared;
}

bool WiFiScan::addSSID(String essid) {
  ssid s = {essid, random(1, 12), {random(256), random(256), random(256), random(256), random(256), random(256)}, false};
  ssids->push_back(s);
  Serial.println(ssids->at(ssids->size() - 1).essid);

  return true;
}

int WiFiScan::generateSSIDs(int count) {
  uint8_t num_gen = count;
  for (uint8_t x = 0; x < num_gen; x++) {
    String essid = "";

    for (uint8_t i = 0; i < 6; i++)
      essid.concat(alfa[random(65)]);

    ssid s = {essid, random(1, 12), {random(256), random(256), random(256), random(256), random(256), random(256)}, false};
    ssids->push_back(s);
    Serial.println(ssids->at(ssids->size() - 1).essid);
  }

  return num_gen;
}

/*void WiFiScan::joinWiFi(String ssid, String password)
{
  static const char * btns[] ={text16, ""};
  int count = 0;

  if ((WiFi.status() == WL_CONNECTED) && (ssid == connected_network) && (ssid != "")) {
    #ifdef HAS_SCREEN
      lv_obj_t * mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
      lv_msgbox_set_text(mbox1, text_table4[2]);
      lv_msgbox_add_btns(mbox1, btns);
      lv_obj_set_width(mbox1, 200);
      lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); //Align to the corner
    #endif
    this->wifi_initialized = true;
    return;
  }
  else if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Already connected. Disconnecting...");
    WiFi.disconnect();
  }

  esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_NULL);
  esp_wifi_start();

  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    if (count == 10)
    {
      Serial.println("\nCould not connect to WiFi network");
      #ifdef HAS_SCREEN
        lv_obj_t * mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
        lv_msgbox_set_text(mbox1, text_table4[3]);
        lv_msgbox_add_btns(mbox1, btns);
        lv_obj_set_width(mbox1, 200);
        //lv_obj_set_event_cb(mbox1, event_handler);
        lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); //Align to the corner
      #endif
      WiFi.mode(WIFI_OFF);
      return;
    }
  }

  #ifdef HAS_SCREEN
    lv_obj_t * mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
    lv_msgbox_set_text(mbox1, text_table4[4]);
    lv_msgbox_add_btns(mbox1, btns);
    lv_obj_set_width(mbox1, 200);
    lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); //Align to the corner
  #endif
  connected_network = ssid;

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  this->wifi_initialized = true;
}*/

// Apply WiFi settings
void WiFiScan::initWiFi(uint8_t scan_mode) {
  // Set the channel
  if (scan_mode != WIFI_SCAN_OFF) {
    //Serial.println(F("Initializing WiFi settings..."));
    this->changeChannel();

    this->force_pmkid = settings_obj.loadSetting<bool>(text_table4[5]);
    this->force_probe = settings_obj.loadSetting<bool>(text_table4[6]);
    this->save_pcap = settings_obj.loadSetting<bool>(text_table4[7]);
    //Serial.println(F("Initialization complete"));
  }
}

bool WiFiScan::scanning() {
  if (this->currentScanMode == WIFI_SCAN_OFF)
    return false;
  else
    return true;
}

// Function to prepare to run a specific scan
void WiFiScan::StartScan(uint8_t scan_mode, uint16_t color)
{
  this->set_channel = 1;
  this->initWiFi(scan_mode);
  if (scan_mode == WIFI_SCAN_OFF)
    StopScan(scan_mode);
  else if (scan_mode == WIFI_SCAN_PROBE)
    RunProbeScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_STATION_WAR_DRIVE)
    RunProbeScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_EVIL_PORTAL)
    RunEvilPortal(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_EAPOL)
    RunEapolScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_ACTIVE_EAPOL)
    RunEapolScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_ACTIVE_LIST_EAPOL)
    RunEapolScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_AP)
    RunBeaconScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_WAR_DRIVE)
    RunBeaconScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_SIG_STREN)
    RunRawScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_RAW_CAPTURE)
    RunRawScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_STATION)
    RunStationScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_TARGET_AP)
    RunAPScan(scan_mode, color);
  else if (scan_mode == WIFI_SCAN_TARGET_AP_FULL)
    RunAPScan(scan_mode, color);

// Seed the random number generator once at the start of the program
void setup() {
    randomSeed(analogRead(0));
}
