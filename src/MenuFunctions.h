#pragma once

class WiFiScan;
#ifndef MenuFunctions_h
#define MenuFunctions_h

#include "configs.h"

#define LVGL_TICK_PERIOD 5     // ✅ ms
#define WIDTH_1 480            // ✅
#define HEIGHT_1 320           // ✅

#ifdef HAS_SCREEN
  #include "lv_conf.h"
  #include <lvgl.h>
#endif

#ifdef HAS_SCREEN
  #define BATTERY_ANALOG_ON 0

// #include "structs.h" // ✅ Comentado - structs já definidas em WiFiScan.h
  #include "WiFiScan.h"  // ✅ Incluir header primeiro
  #include "BatteryInterface.h"
  #include "SDInterface.h"
  #include "settings.h"
  #include <LinkedList.h>

  #ifdef HAS_BUTTONS
    #include "Switches.h"
    extern Switches u_btn;
    extern Switches d_btn;
    extern Switches l_btn;
    extern Switches r_btn;
    extern Switches c_btn;
  #endif

  extern WiFiScan wifi_scan_obj;
  extern SDInterface sd_obj;
  extern BatteryInterface battery_obj;
  extern Settings settings_obj;

  #define FLASH_BUTTON 0

  #if BATTERY_ANALOG_ON == 1
    #if !defined(CYD_32CAP) || !defined(CYD_35CAP)  || !defined(CYD_24CAP) || !defined(CYD_22CAP)
      #define BATTERY_PIN 13
      #define ANALOG_PIN 34
      #define CHARGING_PIN 27
    #endif
  #endif

  // Icon definitions (merged from both versions)
  #define ATTACKS 0
  #define BEACON_SNIFF 1
  #define BLUETOOTH 2
  #define BLUETOOTH_SNIFF 3
  #define DEAUTH_SNIFF 4
  #define DRAW 5
  #define PACKET_MONITOR 6
  #define PROBE_SNIFF 7
  #define SCANNERS 8
  #define CC_SKIMMERS 9
  #define SNIFFERS 10
  #define WIFI 11
  #define BEACON_SPAM 12
  #define RICK_ROLL 13
  #define REBOOT 14
  #define GENERAL_APPS 15
  #define UPDATE 16
  #define DEVICE 17
  #define DEVICE_INFO 18
  #define SD_UPDATE 19
  #define WEB_UPDATE 20
  #define EAPOL 21
  #define STATUS_BAT 22
  #define STATUS_SD 23
  #define PWNAGOTCHI 24
  #define SHUTDOWN 25
  #define BEACON_LIST 26
  #define GENERATE 27
  #define CLEAR_ICO 28
  #define KEYBOARD_ICO 29
  #define JOIN_WIFI 30
  #define LANGUAGE 31
  #define STATUS_GPS 32
  #define GPS_MENU 33
  #define DISABLE_TOUCH 34
  #define FLIPPER 35  // From current code
  #define BLANK 36    // From current code

  void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
  bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
  
  static lv_draw_ctx_t disp_buf;
  static lv_color_t buf[LV_HOR_RES_MAX * 10];

  PROGMEM static void ta_event_cb(lv_obj_t * ta, lv_event_t event);
  PROGMEM static void add_ssid_keyboard_event_cb(lv_obj_t * keyboard, lv_event_t event);
  PROGMEM static void html_list_cb(lv_obj_t * btn, lv_event_t event);
  PROGMEM static void ap_list_cb(lv_obj_t * btn, lv_event_t event);
  PROGMEM static void ap_info_list_cb(lv_obj_t * btn, lv_event_t event);
  PROGMEM static void at_list_cb(lv_obj_t * btn, lv_event_t event);
  PROGMEM static void station_list_cb(lv_obj_t * btn, lv_event_t event);
  PROGMEM static void setting_dropdown_cb(lv_obj_t * btn, lv_event_t event);

  // lvgl stuff
  PROGMEM static lv_obj_t *kb;
  PROGMEM static lv_obj_t * save_as_kb;

  struct Menu;

  // Individual Nodes of a menu
  /*struct MenuNode {
    String name;
    bool command;
    uint16_t color;
    uint8_t icon;
    TFT_eSPI_Button* button;
    bool selected;
    std::function<void()> callable;
  };*/

  struct MenuNode {
    String name;
    bool command;
    uint8_t color;
    uint8_t icon;
    TFT_eSPI_Button* button;
    bool selected;
    std::function<void()> callable;
  };

  // Full Menus
  struct Menu {
    String name;
    ::LinkedList<MenuNode>* list;
    Menu                * parentMenu;
    uint16_t               selected = 0;
  };

  class MenuFunctions
  {
    private:
      String u_result = "";
      float _graph_scale = 1.0;
      uint32_t initTime = 0;
      int menu_start_index = 0;
      uint8_t mini_kb_index = 0;
      uint8_t old_gps_sat_count = 0;
      uint8_t max_graph_value = 0;

      // Main menu stuff
      Menu mainMenu;
      Menu wifiMenu;
      Menu bluetoothMenu;
      Menu badusbMenu;
      Menu deviceMenu;

      // Device menu stuff
      Menu whichUpdateMenu;
      Menu failedUpdateMenu;
      Menu confirmMenu;
      Menu updateMenu;
      Menu settingsMenu;
      Menu specSettingMenu;
      Menu languageMenu;
      Menu sdDeleteMenu;

      // WiFi menu stuff
      Menu wifiSnifferMenu;
      Menu wifiAttackMenu;
      #ifdef HAS_GPS
        Menu wardrivingMenu;
      #endif
      Menu wifiGeneralMenu;
      Menu wifiAPMenu;
      #ifdef HAS_BT
        Menu airtagMenu;
      #endif
      #if !defined(HAS_ILI9341) && !defined(HAS_ST7789) && !defined(HAS_ST7796)
        Menu wifiStationMenu;
      #endif

      // WiFi General Menu
      Menu htmlMenu;
      Menu miniKbMenu;
      Menu saveFileMenu;
      Menu genAPMacMenu;
      Menu cloneAPMacMenu;
      Menu setMacMenu;

      // Bluetooth menu stuff
      Menu bluetoothSnifferMenu;
      Menu bluetoothAttackMenu;

      // Settings things menus
      Menu generateSSIDsMenu;

      static void lv_tick_handler();

      // Menu icons

      uint16_t getColor(uint16_t color);
      void drawAvgLine(int16_t value);
      void drawMaxLine(int16_t value, uint16_t color);
      float calculateGraphScale(int16_t value);
      float graphScaleCheck(const int16_t array[TFT_WIDTH]);
      void drawGraph(int16_t *values);
      void renderGraphUI(uint8_t scan_mode = 0);
      //void addNodes(Menu* menu, String name, uint16_t color, Menu* child, int place, std::function<void()> callable, bool selected = false, String command = "");
      void addNodes(Menu* menu, String name, uint8_t color, Menu* child, int place, std::function<void()> callable, bool selected = false, String command = "");
      void battery(bool initial = false);
      void battery2(bool initial = false);
      void showMenuList(Menu* menu, int layer);
      String callSetting(String key);
      void runBoolSetting(String ley);
      void displaySetting(String key, Menu* menu, int index);
      void buttonSelected(int b, int x = -1);
      void buttonNotSelected(int b, int x = -1);
      #if !defined(HAS_ILI9341) && !defined(HAS_ST7796) && !defined(HAS_ST7789) && defined(HAS_BUTTONS)
        void miniKeyboard(Menu * targetMenu);
      #endif

      #ifdef HAS_GPS
        void displayGPSInfo();
      #endif

      // Unified updateTouch function with conditional signatures
      #if defined(CYD_32CAP) || defined(CYD_35CAP)
        uint8_t updateTouch(int16_t *x, int16_t *y, uint16_t threshold = 600);  // Capacitive version
      #else
        uint8_t updateTouch(uint16_t *x, uint16_t *y, uint16_t threshold = 600);  // Resistive version
      #endif

    public:
      MenuFunctions();

      Menu* current_menu;
      Menu clearSSIDsMenu;
      Menu clearAPsMenu;

      // Save Files Menu (merged from both)
      Menu saveSSIDsMenu;
      Menu loadSSIDsMenu;
      Menu saveAPsMenu;
      Menu loadAPsMenu;
      Menu saveATsMenu;  // From current code
      Menu loadATsMenu;  // From current code

      #ifdef HAS_GPS
        // GPS Menu
        Menu gpsInfoMenu;
      #endif

      Menu infoMenu;
      Menu apInfoMenu;

      Ticker tick;
      uint16_t x = -1, y = -1;
      boolean pressed = false;

      bool disable_touch;

      String loaded_file = "";

      void setGraphScale(float scale);
      void initLVGL();
      void deinitLVGL();
      void selectEPHTMLGFX();
      void updateStatusBar();
      void addSSIDGFX();
      void addAPGFX(String type = "AP");  // From current code
      void addStationGFX();
      void buildButtons(Menu* menu, int starting_index = 0, String button_name = "");
      void changeMenu(Menu* menu);
      void drawStatusBar();
      void displayCurrentMenu(int start_index = 0);
      void main(uint32_t currentTime);
      void RunSetup();
      void orientDisplay();
  };

#endif
#endif
