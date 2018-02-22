/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *           MONOCLE PTZ CONTROLLER - IR REMOTE (MKR1000)
 * -------------------------------------------------------------------
 *
 *  This project implements a Wireless PTZ camera controller using
 *  a simple IR remote control.  This project connects to a local
 *  Monocle Gateway service which provides direct communication with
 *  your ONVIF supported network cameras and the Monocle hosted
 *  services.
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
 * This project builds a fully functional IR (infrared) remote controlled
 * PTZ (pan-tilt-zoom) controller for your ONVIF supported network (IP)
 * cameras.  This project integrates with the Monocle platform and Monocle
 * Alexa Smart Home skill to actively and automatically control the last
 * camera selected via your Amazon Alexa-video enabled device such as Echo
 * Show, Echo Spot or Fire TV.  In additional to direct PTZ control,
 * you also have access from the remote control to recall the camera's
 * home position or any of 1 to 9 camera presets.
 *
 * This project uses a basic 38KHz infrared receiver and remote control
 * to perform pan, tilt, zoom, home and preset recall. The basic control
 * works as follows for each remote control button. (of course you can
 * remap these as desired.)
 *
 *  [LEFT]  - PAN LEFT
 *  [RIGHT] - PAN RIGHT
 *  [UP]    - TILT UP
 *  [DOWN]  - TILT DOWN
 *  [*]     - ZOOM IN
 *  [#]     - ZOOM OUT
 *  [0]     - GOTO HOME POSITION
 *  [1]     - RECALL PRESET 1
 *  [2]     - RECALL PRESET 2
 *  [3]     - RECALL PRESET 3
 *  [4]     - RECALL PRESET 4
 *  [5]     - RECALL PRESET 5
 *  [6]     - RECALL PRESET 6
 *  [7]     - RECALL PRESET 7
 *  [8]     - RECALL PRESET 8
 *  [9]     - RECALL PRESET 9
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
 *  1 @  WINGONEER IR Wireless Remote Control Sensor Module Kit for Arduino
 *       http://amzn.to/2sDvXWv
 *       $6.90 USD  <AMAZON PRIME>
 *
 *  OPTIONAL COMPONENTS:
 *
 *  1 @  AIRSUNNY 5 pairs Infrared Diode LED 38KHz IR Emission and Receiver
 *       http://amzn.to/2BBQ5v6
 *       $5.98 USD (for 5 pairs)  <AMAZON PRIME>
 *
 *  1 @  Micro USB Regulated Power Supply (5VDC 1A)
 *       http://amzn.to/2HqFFyT
 *       $7.99 USD  <AMAZON PRIME>
 *
 *  1 @ Makerfocus Breadboard Kit Breadboard Jumper wires USB cable Hookup for Arduino
 *      http://amzn.to/2C6ZprU
 *      $24.99 USD  <AMAZON PRIME>
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
  * - Arduino-IRremote
  *   https://github.com/z3t0/Arduino-IRremote
  *   (used for receiving and decoding infrared signals)
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

/* REQUIRED FOR RECEIVING IR SIGNALS */
#include <IRremote.h>

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
#define PROGRAM_NAME    "Monocle PTZ Controller - IR Remote (MKR1000)"
#define PROGRAM_VERSION "0.0.1"

/* DEFINE THE PIN NUMBER USED TO CONNECT THE DATA INPUT FROM THE IR RECEIVER */
#define IR_REMOTE_RECEIVE_DATA_PIN  6

/* DEFINE IR CODES FOR YOUR REMOTE CONTROL HERE */
#define REMOTE_OK_BUTTON     0xFF38C7  // (STOP)
#define REMOTE_UP_BUTTON     0xFF18E7  // (TILT UP)
#define REMOTE_DOWN_BUTTON   0xFF4AB5  // (TILT DOWN)
#define REMOTE_LEFT_BUTTON   0xFF10EF  // (PAN LEFT)
#define REMOTE_RIGHT_BUTTON  0xFF5AA5  // (PAN RIGHT)
#define REMOTE_STAR_BUTTON   0xFF6897  // (*)
#define REMOTE_HASH_BUTTON   0xFFB04F  // (#)
#define REMOTE_0_BUTTON      0xFF9867  // (HOME PRESET)
#define REMOTE_1_BUTTON      0xFFA25D  // (PRESET 1)
#define REMOTE_2_BUTTON      0xFF629D  // (PRESET 2)
#define REMOTE_3_BUTTON      0xFFE21D  // (PRESET 3)
#define REMOTE_4_BUTTON      0xFF22DD  // (PRESET 4)
#define REMOTE_5_BUTTON      0xFF02FD  // (PRESET 5)
#define REMOTE_6_BUTTON      0xFFC23D  // (PRESET 6)
#define REMOTE_7_BUTTON      0xFFE01F  // (PRESET 7)
#define REMOTE_8_BUTTON      0xFFA857  // (PRESET 8)
#define REMOTE_9_BUTTON      0xFF906F  // (PRESET 9)

// when a button on this remote is held, this code is continually emitted
#define REMOTE_REPEAT        0xFFFFFFFF

// define the PAN, TILT, ZOOM speeds to use when pressing the remote buttons
#define PAN_SPEED   2 // 1=low, 2=medium; 3=high
#define TILT_SPEED  2 // 1=low, 2=medium; 3=high
#define ZOOM_SPEED  2 // 1=low, 2=medium; 3=high

/**
 * ------------------------------------------------------------------------
 * PROGRAM VARIABLES
 * ------------------------------------------------------------------------
 */

 /* WIRELESS NETWORK SSID AND PASSWORD ARE STORED IN 'private.h' */
const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASS;

// local connection state tracking variable
bool gateway_connected = false;

// wifi client; needed for Monocle Gateway Client
WiFiClient wifi;

// create Monocle Gateway Client instance
MonocleGatewayClient monocle = MonocleGatewayClient(wifi, MONOCLE_GATEWAY_ADDRESS, MONOCLE_GATEWAY_PORT);

// create IR receiver instance with the configured data pin
IRrecv irrecv(IR_REMOTE_RECEIVE_DATA_PIN);

// variable holder for decoded IR signal data
decode_results results;

// time interval tracking variable
unsigned long irTimeout = 0;

/**
 * ------------------------------------------------------------------------
 * PROGRAM INITIALIZATION
 * ------------------------------------------------------------------------
 */
void setup() {
  // define default UART baud rate
  // @see: https://www.arduino.cc/en/serial/begin
  Serial.begin(115200);

  delay(2000); // <-- this is an artificial delay to see this data in the debug console when using Arduino IDE
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

  // start the IR receiver
  // @see: https://github.com/z3t0/Arduino-IRremote
  irrecv.enableIRIn();
}


/**
 * ------------------------------------------------------------------------
 * PROGRAM MAINLINE (LOOP)
 * ------------------------------------------------------------------------
 */
void loop() {
  // reset local connection tracking state
  gateway_connected = false;

  // let the user know we are going to attempt a connection to the Monocle Gateway
  Serial.println("Connecting to Monocle Gateway");

  // attmept to connect to the Monocle Gateway now
  monocle.begin();

  // continious loop while we are connected to the Monocle Gateway
  while (monocle.connected()) {

    // let the user know we are connected to the Monocle Gateway
    if(!gateway_connected) {
      gateway_connected = true; // update local tracking state
      Serial.println("Successfully connected to Monocle Gateway.");
    }

    // if the IR timeout is active, then check to see if 200 milliseconds
    // have passed without any IR repeat signals before sending the
    // PTZ stop command.
    if(irTimeout > 0){
      if((millis() - irTimeout) > 200){
          irTimeout = 0; // reset timeout
          Serial.println("--> STOP");
          monocle.stop();
      }
    }

    // listen for decoded IR input codes
    if (irrecv.decode(&results)) {

      // process the received IR code and try and match it to one of the known button codes
      switch(results.value){

        // if we receive the IR repeat signal, then continually reset the IR timeout timer
        case REMOTE_REPEAT : {
          if(irTimeout > 0) irTimeout = millis();
          break;
        }

        // handle the functions for the specific IR remote control buttons
        case REMOTE_OK_BUTTON: {
          Serial.println("--> STOP");
          monocle.stop();
          break;
        }
        case REMOTE_LEFT_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> PAN LEFT");
          monocle.pan(-PAN_SPEED); // negative speed value means pan left
          break;
        }
        case REMOTE_RIGHT_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> PAN RIGHT");
          monocle.pan(PAN_SPEED); // positive speed value means pan right
          break;
        }
        case REMOTE_UP_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> TILT UP");
          monocle.tilt(TILT_SPEED); // positive speed value means tilt up
          break;
        }
        case REMOTE_DOWN_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> TILT DOWN");
          monocle.tilt(-TILT_SPEED); // negative speed value means tilt down
          break;
        }
        case REMOTE_STAR_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> ZOOM IN");
          monocle.zoom(ZOOM_SPEED); // positive speed value means zoom in
          break;
        }
        case REMOTE_HASH_BUTTON: {
          irTimeout = millis(); // reset IR timeout
          Serial.println("--> ZOOM OUT");
          monocle.zoom(-ZOOM_SPEED); // negative speed value means zoom out
          break;
        }
        case REMOTE_0_BUTTON: {
          Serial.println("--> HOME");
          monocle.home();
          break;
        }
        case REMOTE_1_BUTTON: {
          Serial.println("--> PRESET #1");
          monocle.preset(1);
          break;
        }
        case REMOTE_2_BUTTON: {
          Serial.println("--> PRESET #2");
          monocle.preset(2);
          break;
        }
        case REMOTE_3_BUTTON: {
          Serial.println("--> PRESET #3");
          monocle.preset(3);
          break;
        }
        case REMOTE_4_BUTTON: {
          Serial.println("--> PRESET #4");
          monocle.preset(4);
          break;
        }
        case REMOTE_5_BUTTON: {
          Serial.println("--> PRESET #5");
          monocle.preset(5);
          break;
        }
        case REMOTE_6_BUTTON: {
          Serial.println("--> PRESET #6");
          monocle.preset(6);
          break;
        }
        case REMOTE_7_BUTTON: {
          Serial.println("--> PRESET #7");
          monocle.preset(7);
          break;
        }
        case REMOTE_8_BUTTON: {
          Serial.println("--> PRESET #8");
          monocle.preset(8);
          break;
        }
        case REMOTE_9_BUTTON: {
          Serial.println("--> PRESET #9");
          monocle.preset(9);
          break;
        }
      }

      // display the IR code to the user
      // DEBUG - enable this if you need to see the raw decoded IR button values
      //Serial.print("<< IR BUTTON RX: ");
      //Serial.print(results.value, HEX);
      //Serial.println(" >>");

      // resume processing IR input
      irrecv.resume();
    }
  }

  // let the user know that we are now disconnected from the Monocle Gateway
  Serial.println("Disconnected from Monocle Gateway.");
  Serial.println("We will attempt to reconnect to the Monocle Gateway in 5 seconds.");
  delay(5000); // wait 5 seconds before attempting to reconnect
}
