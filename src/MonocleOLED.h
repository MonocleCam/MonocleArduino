/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *                    MONOCLE OLED DISPLAY
 * -------------------------------------------------------------------
 *
 *  This library provides a client implementation to the display
 *  Monocle state and menus on a 128x63 or 128x32 OLED dipslay.
 *
 *  Author:   Robert Savage
 *  Date:     2018-02-18
 *  Website:  http://monoclecam.com
 *
 * -------------------------------------------------------------------
 *        COPYRIGHT SHADEBLUE, LLC @ 2018, ALL RIGHTS RESERVED
 * -------------------------------------------------------------------
 *
 **********************************************************************
 */
#ifndef MONOCLE_OLED_H
#define MONOCLE_OLED_H

#include <Adafruit_SSD1306.h>

/* NUMBER OF TEXT CHARACTERS PER LINE AT TEXT SIZE 1 */
#define LINE_CHARACTER_WIDTH_1  21

class MonocleOLED : public Adafruit_SSD1306
{
   private:
     int width = 128;
     int height = 64;
     int textLineStart = 0;
     int textLineHeight = 8;

   public:
    /*
     * Default Constructors
     */
     MonocleOLED(const int width, const int height);
     MonocleOLED(const int width, const int height, const int reset);

    /**
     * INITIALIZE THE OLED DISPLAY
     */
     void init();

    /**
     * DRAW THE MONOCLE LOGO
     */
     void logo(bool display = true);

    /**
     * CLEAR THE TEXT LINES REGION (lines 1-4)
     */
     void clearText(bool display = true);

    /**
     * CLEAR TEXT LINE 1
     */
     void clearLine1(bool display = true);

    /**
     * CLEAR TEXT LINE 2
     */
     void clearLine2(bool display = true);

    /**
     * CLEAR TEXT LINE 3
     */
     void clearLine3(bool display = true);

    /**
     * CLEAR TEXT LINE 4
     */
     void clearLine4(bool display = true);

     /**
      * PRINT TEXT TO MULTIPLE LINES
      */
     void printText(const String& line1 = "", const String& line2 = "", const String& line3 = "", const String& line4 = "", bool display = true, bool center = false);

     /**
      * PRINT TEXT TO A SPECIFIC LINE NUMBER
      */
     void printLine(const int line, const String& data, bool display = true, bool center = false);

     /**
      * PRINT TEXT TO LINE 1
      */
     void printLine1(const String& data, bool display = true, bool center = false);

     /**
      * PRINT TEXT TO LINE 2
      */
     void printLine2(const String& data, bool display = true, bool center = false);

     /**
      * PRINT TEXT TO LINE 3
      */
     void printLine3(const String& data, bool display = true, bool center = false);

     /**
      * PRINT TEXT TO LINE 4
      */
     void printLine4(const String& data, bool display = true, bool center = false);
};

#endif //MONOCLE_OLED_H
