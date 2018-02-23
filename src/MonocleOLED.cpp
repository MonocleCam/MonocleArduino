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

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MonocleOLED.h"

/**
 * MONOCLE LOGO BITMAP
 */
static const unsigned char PROGMEM MONOCLE_LOGO [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x00, 0xE0, 0x0F, 0xC0, 0x38, 0x0C, 0x07, 0xE0, 0x00, 0x79, 0x80, 0x0F, 0xF0, 0x00,
  0x00, 0x0D, 0x81, 0xB0, 0x3F, 0xF0, 0x64, 0x0C, 0x1C, 0x1C, 0x03, 0xC1, 0x80, 0x38, 0x00, 0x00,
  0x00, 0x0C, 0x81, 0x30, 0xFF, 0xF8, 0x66, 0x0C, 0x30, 0x06, 0x06, 0x01, 0x80, 0x20, 0x00, 0x00,
  0x00, 0x0C, 0xC1, 0x31, 0x80, 0x0C, 0x66, 0x0C, 0x60, 0x03, 0x0C, 0x01, 0x80, 0x60, 0x00, 0x00,
  0x00, 0x0C, 0xC3, 0x31, 0x80, 0x0E, 0x62, 0x0C, 0xC0, 0x01, 0x18, 0x01, 0x80, 0x60, 0x00, 0x00,
  0x00, 0x0C, 0xC3, 0x33, 0xC0, 0x0E, 0x63, 0x0C, 0xC0, 0x01, 0x90, 0x01, 0x80, 0x30, 0x00, 0x00,
  0x00, 0x0C, 0x43, 0x33, 0xC0, 0x0E, 0x63, 0x0C, 0xC0, 0x01, 0xB0, 0x01, 0x80, 0x1F, 0xF0, 0x00,
  0x00, 0x0C, 0x62, 0x33, 0xC0, 0x0E, 0x61, 0x8C, 0xC0, 0x01, 0xB0, 0x01, 0x80, 0x1F, 0xF0, 0x00,
  0x00, 0x0C, 0x66, 0x33, 0xC0, 0x0E, 0x61, 0x8C, 0xC0, 0x01, 0x90, 0x01, 0x80, 0x20, 0x00, 0x00,
  0x00, 0x0C, 0x66, 0x31, 0xC0, 0x1E, 0x60, 0x8C, 0xC0, 0x01, 0x18, 0x01, 0x80, 0x60, 0x00, 0x00,
  0x00, 0x0C, 0x26, 0x31, 0xE0, 0x1C, 0x60, 0xCC, 0x60, 0x03, 0x08, 0x00, 0x80, 0x60, 0x00, 0x00,
  0x00, 0x0C, 0x34, 0x30, 0xF0, 0x38, 0x60, 0xCC, 0x30, 0x06, 0x0E, 0x00, 0xC0, 0x20, 0x00, 0x00,
  0x00, 0x0C, 0x3C, 0x30, 0x7C, 0xF0, 0x60, 0x4C, 0x1C, 0x1C, 0x03, 0x80, 0x60, 0x38, 0x00, 0x00,
  0x00, 0x0C, 0x1C, 0x30, 0x1F, 0xC0, 0x60, 0x78, 0x07, 0xF0, 0x00, 0xF8, 0x3F, 0x0F, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/**
 * Default Constructors
 */
MonocleOLED::MonocleOLED(const int width, const int height) : Adafruit_SSD1306() {
  this->width = width;
  this->height = height;
  if(height >= 64) this->textLineStart = 24;
}
MonocleOLED::MonocleOLED(const int width, const int height, const int reset) : Adafruit_SSD1306(reset) {
  this->width = width;
  this->height = height;
}

/**
 * INITIALIZE THE OLED DISPLAY
 */
void MonocleOLED::init() {
  this->clearDisplay();
  this->logo();
  this->setTextColor(WHITE, 0);
  this->setTextSize(1);

  // if(this->textLineStart >= 64){
  //   this->setCursor(0,this->textLineStart);
  //   this->println("                    ");
  // } else {
    this->setCursor(0,24);
  // }
  this->println(" ... Please Wait ...");
  this->display();
  delay(1);
}

/**
 * DRAW THE MONOCLE LOGO
 */
void MonocleOLED::logo(bool display){
  this->drawBitmap(0, 0,  MONOCLE_LOGO, width, 16, 1);
  //if(this->textLineStart > 18){
    this->writeLine(0, 18, width, 18, WHITE);
  //}
  if(display) this->display();
}

/**
 * CLEAR THE TEXT LINES REGION (lines 1-4)
 */
void MonocleOLED::clearText(bool display){
  this->writeFillRect(0, this->textLineStart, this->width, this->height, BLACK);
  if(display) this->display();
}

/**
 * CLEAR TEXT LINE 1
 */
void MonocleOLED::clearLine1(bool display){
  this->writeFillRect(0, this->textLineStart, this->width, 8, BLACK);
  if(display) this->display();
}

/**
 * CLEAR TEXT LINE 2
 */
void MonocleOLED::clearLine2(bool display){
  this->writeFillRect(0, this->textLineStart+this->textLineHeight, this->width, 8, BLACK);
  if(display) this->display();
}

/**
 * CLEAR TEXT LINE 3
 */
void MonocleOLED::clearLine3(bool display){
  this->writeFillRect(0, this->textLineStart+(this->textLineHeight * 2), this->width, 8, BLACK);
  if(display) this->display();
}

/**
 * CLEAR TEXT LINE 4
 */
void MonocleOLED::clearLine4(bool display){
  this->writeFillRect(0, this->textLineStart+(this->textLineHeight * 3), this->width, 8, BLACK);
  if(display) this->display();
}

/**
 * PRINT TEXT TO A SPECIFIC LINE NUMBER
 */
void MonocleOLED::printLine(const int line, const String& data, bool display, bool center){
  this->writeFillRect(0, (line*this->textLineHeight) + this->textLineStart, 128, 8, BLACK);
  this->setCursor(0, (line*this->textLineHeight) + this->textLineStart);

  // pad for text centering
  if(center){
  int pad = LINE_CHARACTER_WIDTH_1 - data.length();
    if(pad > 0){
      for(int x = 0; x < pad; x = x+2){
        this->print(" ");
      }
    }
  }

  this->println(data);
  if(display) this->display();
}

/**
 * PRINT TEXT TO LINE 1
 */
void MonocleOLED::printLine1(const String& data, bool display, bool center){
  this->printLine(0, data, display, center);
}

/**
 * PRINT TEXT TO LINE 2
 */
void MonocleOLED::printLine2(const String& data, bool display, bool center){
  this->printLine(1, data, display, center);
}

/**
 * PRINT TEXT TO LINE 3
 */
void MonocleOLED::printLine3(const String& data, bool display, bool center){
  this->printLine(2, data, display, center);
}

/**
 * PRINT TEXT TO LINE 4
 */
void MonocleOLED::printLine4(const String& data, bool display, bool center){
  this->printLine(3, data, display, center);
}

/**
 * PRINT TEXT TO MULTIPLE LINES
 */
void MonocleOLED::printText(const String& line1, const String& line2,
     const String& line3, const String& line4, bool display, bool center){
  this->printLine1(line1, false, center);
  this->printLine2(line2, false, center);
  this->printLine3(line3, false, center);
  this->printLine4(line4, false, center);
  if(display) this->display();
}
