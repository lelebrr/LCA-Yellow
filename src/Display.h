#pragma once

#ifndef Display_h
#define Display_h

#include "configs.h"
#include <lvgl.h>

#ifdef HAS_SCREEN

#include <FS.h>
#include <functional>
#include <JPEGDecoder.h>
#include <vector> // Adicionado para substituir LinkedList

#include <SPI.h>
#include <Ticker.h>
#include "SPIFFS.h"
#include "Assets.h"
#include <Wire.h>
#include <TFT_eSPI.h>



#define OTA_UPDATE 100
#define SHOW_INFO 101
#define WIFI_SCAN_OFF 0
#define WIFI_SCAN_PROBE 1
#define WIFI_SCAN_AP 2
#define WIFI_SCAN_PWN 3
#define WIFI_SCAN_EAPOL 4
#define WIFI_SCAN_DEAUTH 5
#define WIFI_SCAN_ALL 6
#define WIFI_PACKET_MONITOR 7
#define WIFI_ATTACK_BEACON_SPAM 8
#define WIFI_ATTACK_RICK_ROLL 9
#define BT_SCAN_ALL 10
#define BT_SCAN_SKIMMERS 11
#define WIFI_SCAN_ESPRESSIF 12
#define LV_JOIN_WIFI 13
#define LV_ADD_SSID 14
#define WIFI_ATTACK_BEACON_LIST 15

#define RED_KEY ";red;"
#define GREEN_KEY ";grn;"
#define CYAN_KEY ";cyn;"
#define MAGENTA_KEY ";mgn;"
#define WHITE_KEY ";wht;"

class Display
{
  private:
    bool SwitchOn = false;
    bool run_setup = true;
    byte data = 0;
    boolean change_colour = 1;
    boolean selected = 1;

    void drawFrame();

    #ifdef SCREEN_BUFFER
      void scrollScreenBuffer(bool down = false);
    #endif
    void processAndPrintString(TFT_eSPI& tft, const String& originalString);

  public:
    Display();
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSPI_Button key[7];

    const String PROGMEM version_number = LCA_VERSION;

    bool printing = false;
    bool loading = false;
    bool tteBar = false;
    bool draw_tft = false;
    bool exit_draw = false;
    bool headless_mode = false;

    uint8_t TOP_FIXED_AREA = 0;
    uint8_t TOP_FIXED_AREA_2 = 48;
    uint8_t print_delay_1, print_delay_2 = 10;
    uint16_t current_banner_pos = SCREEN_WIDTH;;

    std::vector<String>* display_buffer;

    #ifdef SCREEN_BUFFER
      std::vector<String>* screen_buffer;
    #endif

    uint16_t yDraw = YMAX - BOT_FIXED_AREA - TEXT_HEIGHT;
    uint16_t xPos = 0;
    uint16_t yStart = TOP_FIXED_AREA_2;
    uint16_t yArea = YMAX - TOP_FIXED_AREA_2 - BOT_FIXED_AREA;

    int blank[19];

    // Display constants
    const uint16_t FRAME_X = 10;
    const uint16_t FRAME_Y = 10;
    const uint16_t FRAME_W = 300;
    const uint16_t FRAME_H = 220;

    const uint16_t REDBUTTON_X = 30;
    const uint16_t REDBUTTON_Y = 200;
    const uint16_t REDBUTTON_W = 100;
    const uint16_t REDBUTTON_H = 30;

    const uint16_t GREENBUTTON_X = 190;
    const uint16_t GREENBUTTON_Y = 200;
    const uint16_t GREENBUTTON_W = 100;
    const uint16_t GREENBUTTON_H = 30;

    const uint16_t HEIGHT_1 = 240;

    const uint16_t EXT_BUTTON_WIDTH = 30;
    const uint16_t STATUS_BAR_WIDTH = 20;
    const uint16_t CHAR_WIDTH = 6;

    // Function to get minimum value
    template<typename T>
    T minimum(T a, T b) { return (a < b) ? a : b; }

    void tftDrawRedOnOffButton();
    void tftDrawGreenOnOffButton();
    void tftDrawGraphObjects(byte x_scale);
    void tftDrawEapolColorKey();
    void tftDrawColorKey();
    void tftDrawXScaleButtons(byte x_scale);
    void tftDrawYScaleButtons(byte y_scale);
    void tftDrawChannelScaleButtons(int set_channel, bool lnd_an = true);
    void tftDrawExitScaleButtons(bool lnd_an = true);
    void buildBanner(String msg, int xpos);
    void clearScreen();
    void displayBuffer(bool do_clear = false);
    // void drawJpeg(const char *filename, int xpos, int ypos); // Commented out in current code
    void getTouchWhileFunction(bool pressed);
    void initScrollValues(bool tte = false);
    void jpegInfo();
    void jpegRender(int xpos, int ypos);
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void listFiles();
    void main(uint8_t scan_mode);
    void RunSetup();
    void scrollAddress(uint16_t vsp);
    int scroll_line(uint32_t color);
    void setupScrollArea(uint16_t tfa, uint16_t bfa);
    void showCenterText(String text, int y);
    void touchToExit();
    void twoPartDisplay(String center_text);
    void updateBanner(String msg);
};

#endif
#endif