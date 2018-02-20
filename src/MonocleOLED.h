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


class MonocleOLED : public Adafruit_SSD1306
{
   private:
     int width = 128;
     int height = 64;
     int textLineStart = 0;
     int textLineHeight = 8;

   public:
    /*
     * Default Constructor
     */
     MonocleOLED(const int width, const int height);
     MonocleOLED(const int width, const int height, const int reset);

     void init();
     void logo(bool display = true);
     void clearText(bool display = true);
     void clearLine1(bool display = true);
     void clearLine2(bool display = true);
     void clearLine3(bool display = true);
     void clearLine4(bool display = true);
     void printText(const String& line1 = "", const String& line2 = "", const String& line3 = "", const String& line4 = "", bool display = true);
     void printLine(const int line, const String& data, bool display = true);
     void printLine1(const String& data, bool display = true);
     void printLine2(const String& data, bool display = true);
     void printLine3(const String& data, bool display = true);
     void printLine4(const String& data, bool display = true);
};

#endif //MONOCLE_OLED_H
