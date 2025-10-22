/**
 * @file lv_conf.h
 * Configuration file for v9.4.0
 */

/*
 * Copy this file as `lv_conf.h`
 * 1. simply next to `lvgl` folder
 * 2. or any other places and
 *    - define `LV_CONF_INCLUDE_SIMPLE`
 *    - add the path as include path
 */

/* clang-format off */
#if 1 /*Set it to "1" to enable content*/

#ifndef LV_CONF_H
#define LV_CONF_H

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 24 (RGB888), 32 (ARGB8888)*/
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/

/*Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_CLIB
#define LV_USE_STDLIB_STRING    LV_STDLIB_CLIB
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_CLIB

#define LV_SPRINTF_CUSTOM_INCLUDE <stdio.h>
#define LV_STDINT_INCLUDE <stdint.h>
#define LV_STDDEF_INCLUDE <stddef.h>
#define LV_STDBOOL_INCLUDE <stdbool.h>
#define LV_INTTYPES_INCLUDE <inttypes.h>
#define LV_LIMITS_INCLUDE <limits.h>
#define LV_STDARG_INCLUDE <stdarg.h>

/*====================
   HAL SETTINGS
 *====================*/

/*Default display refresh, input device read and animation step period.*/
#define LV_DEF_REFR_PERIOD  33      /*[ms]*/

/*Default Dot Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 * (Not so important, you can adjust it to modify default sizes and spaces)*/
#define LV_DPI_DEF 130     /*[px/inch]*/

/*====================
   FEATURE CONFIGURATION
 *====================*/

/*-------------
 * Logging
 *-----------*/

/*Enable the log module*/
#define LV_USE_LOG    0
#if LV_USE_LOG

    /*How important is the log. LV_LOG_LEVEL_TRACE (0xFFFF) is most important, LV_LOG_LEVEL_WARN (0x7FFF) is least*/
    #define LV_LOG_LEVEL    LV_LOG_LEVEL_WARN

    /*1: Print the log with 'printf';
    *0: User need to register a callback with lv_log_register_print_cb()*/
    #define LV_LOG_PRINTF   0

    /*Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs*/
    #define LV_LOG_TRACE_MEM        1
    #define LV_LOG_TRACE_TIMER      1
    #define LV_LOG_TRACE_INDEV      1
    #define LV_LOG_TRACE_DISP_REFR  1
    #define LV_LOG_TRACE_EVENT      1
    #define LV_LOG_TRACE_OBJ_CREATE 1
    #define LV_LOG_TRACE_LAYOUT     1
    #define LV_LOG_TRACE_ANIM       1

#endif  /*LV_USE_LOG*/

/*-------------
 * Asserts
 *-----------*/

/*Enable asserts if an operation is failed or an invalid data is found.
 *If LV_USE_LOG is enabled an error message will be printed related to the problem.*/
#define LV_USE_ASSERT_NULL          1   /*Check if the parameter is NULL. (Very fast, recommended)*/
#define LV_USE_ASSERT_MALLOC        1   /*Checks is the memory is successfully allocated or no. (Very fast, recommended)*/
#define LV_USE_ASSERT_STYLE         0   /*Check if the styles are properly initialized. (Very fast, recommended)*/
#define LV_USE_ASSERT_MEM_INTEGRITY 0   /*Check the integrity of `lv_mem` after critical operations. (Slow)*/
#define LV_USE_ASSERT_OBJ           0   /*Check the object's type and existence (e.g. not deleted). (Slow)*/

/*Add a custom handler when assert happens e.g. to restart the MCU*/
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER         while(1);   /*Halt by default*/

/*-------------
 * Others
 *-----------*/

/*1: Show CPU usage and FPS count*/
#define LV_USE_PERF_MONITOR 0
#if LV_USE_PERF_MONITOR
    #define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

    /*0: Displays performance data on the screen
    *1: Print the performance data on the debug output (e.g. to UART)*/
    #define LV_USE_PERF_MONITOR_LOG_MODE 0
#endif

/*1: Use the one line font*/
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/*An experimentally crafted font with a rendered line for all ASCII chars*/
#define LV_FONT_MONTSERRAT_12_SUBPX      0
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0  /*bpp = 3*/
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0  /*Hebrew, Arabic, Wi 254 codes only*/
#define LV_FONT_SIMSUN_16_CJK            0  /*1000 most common CJK radicals*/

/*Pixel perfect monospace fonts*/
#define LV_FONT_UNSCII_8  0
#define LV_FONT_UNSCII_16 0

/*Optionally declare custom fonts here.
 *You can use these fonts as default font too and they will be available globally.
 *E.g. #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2)*/
#define LV_FONT_CUSTOM_DECLARE

/*Always set a default font*/
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/*Enable handling large font and/or fonts with a lot of characters.
 *The limit depends on the font size, font face and bpp.
 *Compiler error will be triggered if a font needs it.*/
#define LV_FONT_FMT_TXT_LARGE   0

/*Enables/disables support for compressed fonts.*/
#define LV_USE_FONT_COMPRESSED 0

/*Enable subpixel rendering*/
#define LV_USE_FONT_SUBPX 0

/*==================
 *  TEXT SETTINGS
 *==================*/

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/*Can break (wrap) texts on these chars*/
#define LV_TXT_BREAK_CHARS " ,.;:-_"

#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/*Support bidirectional texts. Allows mixing Left-to-Right and Right-to-Left texts.
 *The direction will be processed according to the Unicode Bidirectional Algorithm:
 *https://www.w3.org/International/articles/inline-bidi-markup/uba-basics*/
#define LV_USE_BIDI     0
#if LV_USE_BIDI
    /*Set the default direction. Supported values:
    *`LV_BASE_DIR_LTR` Left-to-Right
    *`LV_BASE_DIR_RTL` Right-to-Left
    *`LV_BASE_DIR_AUTO` detect text direction*/
    #define LV_BIDI_BASE_DIR_DEF  LV_BASE_DIR_AUTO
#endif

/*Enable Arabic/Persian processing
 *In these languages characters should be replaced with an other form based on their position in the text*/
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*==================
 *  WIDGETS
 *==================*/

/*Documentation of the widgets: https://docs.lvgl.io/latest/en/html/widgets/index.html*/

#define LV_USE_ANIMIMG    1

#define LV_USE_ARC        1

#define LV_USE_BAR        1

#define LV_USE_BUTTON     1

#define LV_USE_BUTTONMATRIX  1

#define LV_USE_CANVAS     1

#define LV_USE_CHECKBOX   1

#define LV_USE_DROPDOWN   1   /*Requires: lv_label*/

#define LV_USE_IMAGE      1   /*Requires: lv_label*/

#define LV_USE_IMGBTN     1

#define LV_USE_KEYBOARD   1   /*Requires: lv_btnm*/

#define LV_USE_LABEL      1
#if LV_USE_LABEL
    #define LV_LABEL_TEXT_SELECTION 1 /*Enable selecting text of the label*/
    #define LV_LABEL_LONG_TXT_HINT 1  /*Store some extra info in labels to speed up drawing of very long text*/
#endif

#define LV_USE_LINE       1

#define LV_USE_ROLLER     1   /*Requires: lv_label*/
#if LV_USE_ROLLER
    #define LV_ROLLER_INF_PAGES 7 /*Number of extra "pages" when infinite mode is used for the roller*/
#endif

#define LV_USE_SLIDER     1   /*Requires: lv_bar*/

#define LV_USE_SWITCH     1

#define LV_USE_TEXTAREA   1  /*Requires: lv_label*/
#define LV_USE_TABLE      1

/*==================
 *  THEMES
 *==================*/

/*A simple, impressive and very complete theme*/
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT

    /*0: Light mode; 1: Dark mode*/
    #define LV_THEME_DEFAULT_DARK 0

    /*1: Enable grow on press*/
    #define LV_THEME_DEFAULT_GROW 1

    /*Default transition time in [ms]*/
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/*A very simple theme that is a good starting point for a custom theme*/
#define LV_USE_THEME_SIMPLE 1

#define LV_USE_THEME_MONO   1

/*==================
 * LAYOUTS
 *==================*/

/*A layout similar to Flexbox in CSS.*/
#define LV_USE_FLEX 1

/*A layout similar to Grid in CSS.*/
#define LV_USE_GRID 1

/*====================
 * 3RD PARTY LIBRARIES
 *====================*/

/*File system interfaces for common APIs*/

/*API for fopen, fread, etc*/
#define LV_USE_FS_STDIO 0
#if LV_USE_FS_STDIO
    #define LV_FS_STDIO_LETTER '\0'     /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
    #define LV_FS_STDIO_PATH ""         /*Set the working directory. File/directory paths will be appended to it.*/
    #define LV_FS_STDIO_CACHE_SIZE 0    /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for open, read, etc*/
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
    #define LV_FS_POSIX_LETTER '\0'     /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
    #define LV_FS_POSIX_PATH ""         /*Set the working directory. File/directory paths will be appended to it.*/
    #define LV_FS_POSIX_CACHE_SIZE 0    /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for CreateFile, ReadFile, etc*/
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
    #define LV_FS_WIN32_LETTER '\0'     /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
    #define LV_FS_WIN32_PATH ""         /*Set the working directory. File/directory paths will be appended to it.*/
    #define LV_FS_WIN32_CACHE_SIZE 0    /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for FATFS (needs to be added separately). Uses f_open, f_read, etc*/
#define LV_USE_FS_FATFS  0
#if LV_USE_FS_FATFS
    #define LV_FS_FATFS_LETTER '\0'     /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
    #define LV_FS_FATFS_PATH ""         /*Set the working directory. File/directory paths will be appended to it.*/
    #define LV_FS_FATFS_CACHE_SIZE 0    /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*PNG decoder library*/
#define LV_USE_PNG 0

/*BMP decoder library*/
#define LV_USE_BMP 0

/* JPG + split JPG decoder library.
 * Split JPG is a custom format optimized for embedded systems. */
#define LV_USE_TJPGD 0

/*GIF decoder library*/
#define LV_USE_GIF 0

/*QR code library*/
#define LV_USE_QRCODE 0

/* FreeType library */
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
    /*Memory used by FreeType to cache characters [bytes] (-1 = unlimited)*/
    #define LV_FREETYPE_CACHE_SIZE (16 * 1024)
#endif

/*Rlottie library*/
#define LV_USE_RLOTTIE 0

/*FFmpeg library for image decoding and playing videos
 *Supports all major image formats so do not enable other image decoder with it*/
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
    /*Dump input information to stderr*/
    #define LV_FFMPEG_DUMP_FORMAT 0
#endif

/*==================
 * OTHERS
 *==================*/

/*1: Enable the `lv_fs` interface*/
#define LV_USE_FS 0

/*1: Enable the extended `lv_fs` interface. (Default: 0)*/
#define LV_USE_FS_EXT 0

/*1: Enable the extended `lv_fs` interface. (Default: 0)*/
#define LV_USE_FS_POSIX_UNISTD 0

/*==================
* EXAMPLES
*==================*/

/*Enable the examples to be built with the library*/
#define LV_BUILD_EXAMPLES 1

/*===================
 * DEMO USAGE
 ====================*/

/*Show some widget. It might be required to increase the `LV_MEM_SIZE` */
#define LV_USE_DEMO_WIDGETS 1

/*Demonstrate the usage of encoder and keyboard*/
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 1

/*Benchmark your system*/
#define LV_USE_DEMO_BENCHMARK 1
#if LV_USE_DEMO_BENCHMARK
    /*Use some specific devices only for benchmark*/
    #define LV_DEMO_BENCHMARK_Arduino_GFX 0
#endif

/*Stress test for LVGL*/
#define LV_USE_DEMO_STRESS 1

/*Music player*/
#define LV_USE_DEMO_MUSIC 1
#if LV_USE_DEMO_MUSIC
    #define LV_DEMO_MUSIC_SQUARE    0
    #define LV_DEMO_MUSIC_LANDSCAPE 0
    #define LV_DEMO_MUSIC_ROUND     0
    #define LV_DEMO_MUSIC_LARGE     0

    /*Automatically start playing when set up*/
    #define LV_DEMO_MUSIC_AUTO_PLAY 0
#endif

/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/