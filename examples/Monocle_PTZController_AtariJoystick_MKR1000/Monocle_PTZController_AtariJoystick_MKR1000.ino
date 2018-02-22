/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *        MONOCLE PTZ CONTROLLER - ATARI JOYSTICK (MKR1000)
 * -------------------------------------------------------------------
 *
 *  This project implements a Wireless PTZ camera controller using
 *  an Atari/Commodore compatible Joystick with a 9-pin DB9 connector.
 *  This project connects to a local Monocle Gateway service which
 *  provides direct communication with your ONVIF supported network
 *  cameras and the Monocle hosted services.
 *
 *  When used in conjunction with the Monocle Alexa Smart Home Skill,
 *  this PTZ controller will automatically switch to the current/
 *  active camera as last selected on your Amazon Echo Show, Echo
 *  Spot or FireTV device.
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

/**
 * ------------------------------------------------------------------------
 * PROJECT ABSTRACT
 * ------------------------------------------------------------------------
 * This project builds a fully functional Atari/Commodore Joystick based
 * PTZ (pan-tilt-zoom) controller for your ONVIF supported network (IP)
 * cameras.  This project integrates with the Monocle platform and Monocle
 * Alexa Smart Home skill to actively and automatically control the last
 * camera selected via your Amazon Alexa-video enabled device such as Echo
 * Show, Echo Spot or Fire TV.
 *
 * This project uses a basic contact closure microswitch or reed based
 * joystick controller to perform pan, tilt and zoom functions. The basic
 * control works as follows:
 *
 *  [LEFT]         - PAN LEFT
 *  [RIGHT]        - PAN RIGHT
 *  [UP]           - TILT UP
 *  [DOWN]         - TILT DOWN
 *  [FIRE + UP]    - ZOOM IN    (hold the fire button down while pushing up)
 *  [FIRE + DOWN]  - ZOOM OUT   (hold the fire button down while pushing down)
 *
 * (Please see the Bill--Of-Materials section for more information
 * on this joystick controller.)
 */

/**
 * ------------------------------------------------------------------------
 * PROJECT DOCUMENTATION
 * ------------------------------------------------------------------------
 *
 * This project was developed and contributed as part of the
 *   "The Alexa and Arduino Smart Home Challenge"
 * https://www.hackster.io/contests/alexasmarthome
 *
 * You can find the fully documented project here:
 * https://www.hackster.io/monocle/monocle-view-control-ip-cameras-with-alexa-arduino-32bdd3
 */

 /**
  * ------------------------------------------------------------------------
  * MONOCLE CLOUD SERVICE
  * ------------------------------------------------------------------------
  *
  * This project is used in conjunction with the Monocle cloud service.
  * The cloud service integrates the Monocle Alexa smart home skill as
  * well as a provide a central location for you to configure your
  * network of IP cameras.  You will need to sign up and create an
  * account on MonocleCam and configure your netowrk cameras to use this
  * service.
  *
  * https://monoclecam.com | https://monocle.cam (not .com)
  */

/**
 * ------------------------------------------------------------------------
 * ALEXA SKILL
 * ------------------------------------------------------------------------
 *
 * This project is used in conjunction with the Monocle Alexa Smart Home
 * skill.  The PTZ controller can dynamically control the last selected
 * camera requested on your Alexa video-enabled device such as Echo Spot,
 * Echo Show or Fire TV.
 *
 * http://amzn.to/2CvKAuA
 */

/**
 * ------------------------------------------------------------------------
 * BILL OF MATERIALS
 * ------------------------------------------------------------------------
 *
 * This project was built using the following components:
 *
 *  1 @  Arduino MKR1000 (WiFI)
 *       https://store.arduino.cc/usa/arduino-mkr1000
 *       $34.99 USD
 *
 *  1 @  DB9 Male Solder D-SUB Connector with Plastic Shell
 *       http://amzn.to/2FeytF7
 *       $3.80 USD  <AMAZON PRIME>
 *
 *  1 @  CirKa "A77" Premium Joystick Controller for Atari 2600
 *       (or any Atari/Commodore compatible joystick)
 *       http://amzn.to/2CvvN3j
 *       $14.99 USD  <AMAZON PRIME>
 *
 *  1 @  2.2"x1.4"x 0.6" Plastic Electric Project Case
 *       http://amzn.to/2GxxyiS
 *       $8.14 USD (5 pc)  <AMAZON PRIME>
 *
 *  OPTIONAL COMPONENTS:
 *
 *  If you are like me, then you might prefer to but a bulk pack rather than a single connector:
 *  1 @  Connectors Pro 10 Sets Solder Type DB9 Male and Plastic Hoods, D-Sub Connector
 *       http://amzn.to/2EEgtqT
 *       $11.95 USD  <AMAZON PRIME>
 *  (or)
 *  1 @  20 Pcs Replacement Converter DB9 Male Solder
 *       http://amzn.to/2EF10qD
 *       $8.13 USD   <AMAZON PRIME>
 *
 *  If you prefer not to solder the DB9 connector and use screw terminals:
 *  1 @  DB9 RS232 D-SUB Male Adapter 9-pin Port Adapter to Terminal Connector Signal Module With case
 *       http://amzn.to/2sEgDJd
 *       $7.88 USD   <AMAZON PRIME>
 *  (or)
 *  1 @  DB9 D-SUB 9 Pin Male Adapter RS232 to Terminal Connector Signal Module
 *       http://amzn.to/2ENA8E7
 *       $6.75 USD   <AMAZON PRIME>
 *
 *  1 @  Micro USB Regulated Power Supply (5VDC 1A)
 *       http://amzn.to/2HqFFyT
 *       $7.99 USD   <AMAZON PRIME>
 *
 *  1 @ Makerfocus Breadboard Kit Breadboard Jumper wires USB cable Hookup for Arduino
 *      http://amzn.to/2C6ZprU
 *      $24.99 USD   <AMAZON PRIME>
 *
 * (NOTE: prices listed are at the time of this writing: 2018-02-18)
 */

 /**
  * ------------------------------------------------------------------------
  * PROJECT DEPENDENCIES
  * ------------------------------------------------------------------------
  *
  * This project makes use of additional thrid-party Arduino libraries.
  * The following libraries must be installed to compile this project:
  *
  * - ArduinoHttpClient
  *   https://github.com/arduino-libraries/ArduinoHttpClient
  *   (used for web-socket communication)
  *
  * - Bounce2
  *   https://github.com/thomasfredericks/Bounce2
  *   (used for debouncing the joystick button)  *
  */

/**
 * ------------------------------------------------------------------------
 * PROGRAM LIBRARIES
 * ------------------------------------------------------------------------
 */

/* REQUIRED FOR WIRELESS NETWORK ON ARDUINO MKR1000 */
#include <WiFiClient.h>
#include <WiFi101.h>

/* REQUIRED FOR MONOCLE GATEWAY CLIENT */
#include <ArduinoHttpClient.h>

/* REQUIRED FOR JOYSTICK DIGITAL INPUTS */
#include <Bounce2.h>

/* MONOCLE IMPLEMENTATION MODULES */
#include <MonocleGatewayClient.h>

/* YOUR PRIVATE INFORMATION */
#include "private.h"


/**
 * ------------------------------------------------------------------------
 * PROGRAM CONSTANTS
 * ------------------------------------------------------------------------
 */

/* PROGRAM NAME AND VERSION */
#define PROGRAM_NAME    "Monocle PTZ Controller - AtariJoystick (ESP8622)"
#define PROGRAM_VERSION "0.0.1"

/* DEFINE PAN, TILT, ZOOM SPEEDS */
#define PAN_SPEED   2 // 1=low, 2=medium; 3=high
#define TILT_SPEED  2 // 1=low, 2=medium; 3=high
#define ZOOM_SPEED  2 // 1=low, 2=medium; 3=high


/* BELOW IS THE PINOUT FOR A ATARI/COMMODORE JOYSTICK DB9 CONNECTOR */
//  Pin 1 :  Up
//  Pin 2 :  Down
//  Pin 3 :  Left
//  Pin 4 :  Right
//  Pin 5 :  <not used>
//  Pin 6 :  Trigger/Fire
//  Pin 7 :  <not used>
//  Pin 8 :  Ground
//  Pin 9 :  <not used>

/* DEFINE JOYSTICK DIGITAL INPUT PINS */
#define JOYSTICK_PIN_UP       1 // <digital input pin>
#define JOYSTICK_PIN_DOWN     2 // <digital input pin>
#define JOYSTICK_PIN_LEFT     3 // <digital input pin>
#define JOYSTICK_PIN_RIGHT    4 // <digital input pin>
#define JOYSTICK_PIN_FIRE     5 // <digital input pin>

/**
 * ------------------------------------------------------------------------
 * PROGRAM VARIABLES
 * ------------------------------------------------------------------------
 */

 /* WIRELESS NETWORK SSID AND PASSWORD ARE STORED IN 'private.h' */
char* ssid     = WIFI_SSID;
char* password = WIFI_PASS;

// wifi client; needed for Monocle Gateway Client
WiFiClient wifi;

// create Monocle Gateway Client instance
MonocleGatewayClient monocle = MonocleGatewayClient(wifi, MONOCLE_GATEWAY_ADDRESS, MONOCLE_GATEWAY_PORT);

// create an array of buttons
const uint8_t JOYSTICK_PINS[] = {JOYSTICK_PIN_UP, JOYSTICK_PIN_DOWN, JOYSTICK_PIN_LEFT, JOYSTICK_PIN_RIGHT, JOYSTICK_PIN_FIRE};
Bounce * debounce = new Bounce[sizeof(JOYSTICK_PINS)];

// create PTZ instance values
int pan  = 0;
int tilt = 0;
int zoom = 0;

// create PTZ last reported values
int lastPan  = 0;
int lastTilt = 0;
int lastZoom = 0;

// double-click timer tracking variable
unsigned long doubleClickTimer = 0;


/**
 * ------------------------------------------------------------------------
 * PROGRAM INITIALIZATION
 * ------------------------------------------------------------------------
 */
void setup() {

  // define default UART baud rate
  // @see: https://www.arduino.cc/en/serial/begin
  Serial.begin(115200);

  // configure joystick digital input pins
  // we use a PULLUP to give these pins a HIGH (3.3VDC bias)
  // when the joystick makes a contact closure, it will ground each pin
  // so we need them to be "Pulled Up (to high)" by default
  // we could use 4.7 - 10K resistors to pull up, but the embedded chip
  // pull up in software is easier for this prototype
  pinMode(JOYSTICK_PIN_UP,    INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_DOWN,  INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_LEFT,  INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_RIGHT, INPUT_PULLUP);
  pinMode(JOYSTICK_PIN_FIRE,  INPUT_PULLUP);

  // attach each joystick pin to the debounce instance
  for (int i = 0; i < sizeof(JOYSTICK_PINS); i++) {
    debounce[i].attach(JOYSTICK_PINS[i] , INPUT_PULLUP);
    debounce[i].interval(10);   // interval in ms
  }

  Serial.println("================================================");
  Serial.print(" PROGRAM: ");
  Serial.println(PROGRAM_NAME);
  Serial.print(" VERSION: ");
  Serial.println(PROGRAM_VERSION);
  Serial.println("================================================");

  // let the user know that we are attempting to connect to the wireless network
  Serial.print("Connecting to wirless network: ");
  Serial.println(ssid);

  // start the connection to the user's wireless access point
  // @see: https://www.arduino.cc/en/Reference/WiFiBegin
  WiFi.begin(ssid, password);

  // wait until the wireless network connection has been established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // print something the let the user know we are still working
  }

  // let the user know we have successfully connected to the network
  IPAddress myIP = WiFi.localIP();
  String ip_address = String(myIP[0])+"."+String(myIP[1])+"."+String(myIP[2])+"."+String(myIP[3]);
  Serial.println("Successfully connected to wireless network:");
  Serial.print(" - SSID       : ");
  Serial.println(WiFi.SSID());
  Serial.print(" - IP Address : ");
  Serial.println(ip_address);
  Serial.println("================================================");
}


/**
 * ------------------------------------------------------------------------
 * PROGRAM MAINLINE (LOOP)
 * ------------------------------------------------------------------------
 */
void loop() {

  // let the user know we are going to attempt a connection to the Monocle Gateway
  Serial.println("Connecting to Monocle Gateway");

  // attmept to connect to the Monocle Gateway now
  monocle.begin();

  // let the user know we are connected to the Monocle Gateway
  if (monocle.connected()) {
    Serial.println("Successfully connected to Monocle Gateway.");
  }

  // continious loop while we are connected to the Monocle Gateway
  while (monocle.connected()) {

    // iterate over all the joystick pins in the debounce instance and update them
    for (int i = 0; i < sizeof(JOYSTICK_PINS); i++)  {
      debounce[i].update();
    }

    // WATCH FOR DOUBLE CLICKS ON THE FIRE BUTTON (2 clicks within 250 ms)
    // (if detected, send the camera to its home position)
    if(debounce[4].fell()){
      if(doubleClickTimer > 0 && millis() - doubleClickTimer < 250){
        Serial.println("--> HOME");
        monocle.home();
        doubleClickTimer = 0;
      }
      else {
        doubleClickTimer = millis();
      }
    }

    // PROCESS PAN (X-AXIS)
    if(debounce[2].read() == LOW)       // PA LEFT
      pan = -PAN_SPEED;                 // (negative pan speed means 'left')
    else if(debounce[3].read() == LOW)  // PA RIGHT
      pan = PAN_SPEED;                  // (positive pan speed means 'right')
    else                                //
      pan = 0;                          // PAN STOP

    // PROCESS TILT (Y-AXIS) <when fire button is not pressed>
    if(debounce[4].read() == HIGH && debounce[0].read() == LOW)       // TILT UP
      tilt = TILT_SPEED;                                              // (positive tilt speed means 'up')
    else if(debounce[4].read() == HIGH && debounce[1].read() == LOW)  // TILT DOWN
      tilt = -TILT_SPEED;                                             // (negative tilt speed means 'down')
    else                                                              //
      tilt = 0;                                                       // TILT STOP

    // PROCESS ZOOM (Y-AXIS) <when fire button is pressed>
    if(debounce[4].read() == LOW && debounce[0].read() == LOW)        // ZOOM IN
      zoom = ZOOM_SPEED;                                              // (positive zoom speed means 'in')
    else if(debounce[4].read() == LOW && debounce[1].read() == LOW)   // ZOOM OUT DOWN
      zoom = -ZOOM_SPEED;                                             // (negative zoom speed means 'out')
    else                                                              //
      zoom = 0;                                                       // ZOOM STOP

    // do we need to send a PTZ command to the Monocle gateway?
    if(pan != lastPan || tilt != lastTilt || zoom != lastZoom){
      // sycn last known PTZ states
      lastPan  = pan;
      lastTilt = tilt;
      lastZoom = zoom;

      // build a display string of the current  PTZ action(s)
      String info = "--> ";
      if(pan > 0) info+="PAN RIGHT; ";
      if(pan < 0) info+="PAN LEFT; ";
      if(tilt > 0) info+="TILT UP; ";
      if(tilt < 0) info+="TILT DOWN; ";
      if(zoom > 0) info+="ZOOM IN; ";
      if(zoom < 0) info+="ZOOM OUT; ";
      if(pan == 0 && tilt == 0 && zoom == 0) info+="STOP";
      Serial.println(info);

      // send PTZ to Monocle gateway
      monocle.ptz(pan, tilt, zoom);
    }
    delay(10);
  }

  // let the user know that we are now disconnected from the Monocle Gateway
  Serial.println("Disconnected from Monocle Gateway.");
  Serial.println("We will attempt to reconnect to the Monocle Gateway in 5 seconds.");
  delay(5000); // wait 5 seconds before attempting to reconnect
}
