/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *                    MONOCLE GATEWAY CLIENT
 * -------------------------------------------------------------------
 *
 *  This library provides a client implementation to connect locally
 *  to a Monocle Gateway service to perform camera control.
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

#include "MonocleGatewayClient.h"
#include <ArduinoHttpClient.h>

/**
 * Constructors
 */
MonocleGatewayClient::MonocleGatewayClient(Client& client, const char* address, uint16_t port) : _ws(client, address, port) {
}
MonocleGatewayClient::MonocleGatewayClient(Client& client, const String& address, uint16_t port) : _ws(client, address, port) {
}
MonocleGatewayClient::MonocleGatewayClient(Client& client, const IPAddress& address, uint16_t port) : _ws(client, address, port) {
}

/**
 * START THE CONNECTION TO THE 
 * TO THE MONOCLE GATEWAY
 */
void MonocleGatewayClient::begin() {
  _ws.begin();
}

/**
 * DETEMINE THE CONNECTION STATE
 * RETURNS 'true' IF CURRENTLY CONNECTED 
 * TO THE MONOCLE GATEWAY
 */
bool MonocleGatewayClient::connected() {
  return _ws.connected();
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO RECALL AND MOVE TO ITS 
 * PRECONFIGURED HOME POSITION
 */
void MonocleGatewayClient::home() {
  send("HOME");
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO BEGIN A COMPLEX PTZ MOVEMENT 
 * AT A GIVEN DIRECTION AND SPEED FOR EACH AXIS.
 * --------------------------------------------
 * SUPPORTED PAN VALUES:
 *   -3 : PAN LEFT FAST
 *   -2 : PAN LEFT MED
 *   -1 : PAN LEFT SLOW
 *    0 : PAN STOP
 *    1 : PAN RIGHT SLOW
 *    2 : PAN RIGHT MED
 *    3 : PAN RIGHT FAST
 *    
 * SUPPORTED TILT VALUES:
 *   -3 : TILT DOWN FAST
 *   -2 : TILT DOWN MED
 *   -1 : TILT DOWN SLOW
 *    0 : TILT STOP
 *    1 : TILE UP SLOW
 *    2 : TILE UP MED
 *    3 : TILE UP FAST
 *    
 * SUPPORTED ZOOM VALUES:
 *   -3 : ZOOM OUT FAST
 *   -2 : ZOOM OUT MED
 *   -1 : ZOOM OUT SLOW
 *    0 : ZOOM STOP
 *    1 : ZOOM IN SLOW
 *    2 : ZOOM IN MED
 *    3 : ZOOM IN FAST
 */
 void MonocleGatewayClient::ptz(const int pan, const int tilt, const int zoom) {
  String data = "PTZ:";
  data = data + pan;
  data = data + ":" + tilt;
  data = data + ":" + zoom;
  send(data);
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO STOP ALL MOVEMENT IMMEDIATELY
 */
void MonocleGatewayClient::stop() {
  send("STOP");
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO BEGIN PANNING AT A GIVEN 
 * DIRECTION AND SPEED.
 * --------------------------------------------
 * SUPPORTED PAN VALUES:
 *   -3 : PAN LEFT FAST
 *   -2 : PAN LEFT MED
 *   -1 : PAN LEFT SLOW
 *    0 : PAN STOP
 *    1 : PAN RIGHT SLOW
 *    2 : PAN RIGHT MED
 *    3 : PAN RIGHT FAST
 */
void MonocleGatewayClient::pan(const int pan) {
  String data = "PAN:";
  data+= pan;
  send(data);
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO BEGIN TILTING AT A GIVEN 
 * DIRECTION AND SPEED.
 * --------------------------------------------
 * SUPPORTED TILT VALUES:
 *   -3 : TILT DOWN FAST
 *   -2 : TILT DOWN MED
 *   -1 : TILT DOWN SLOW
 *    0 : TILT STOP
 *    1 : TILE UP SLOW
 *    2 : TILE UP MED
 *    3 : TILE UP FAST
 */
void MonocleGatewayClient::tilt(const int tilt) {
  String data = "TILT:";
  data+= tilt;
  send(data);
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO BEGIN ZOOMING AT A GIVEN 
 * DIRECTION AND SPEED.
 * --------------------------------------------
 * SUPPORTED ZOOM VALUES:
 *   -3 : ZOOM OUT FAST
 *   -2 : ZOOM OUT MED
 *   -1 : ZOOM OUT SLOW
 *    0 : ZOOM STOP
 *    1 : ZOOM IN SLOW
 *    2 : ZOOM IN MED
 *    3 : ZOOM IN FAST
 */
void MonocleGatewayClient::zoom(const int zoom) {
  String data = "ZOOM:";
  data+= zoom;
  send(data);
}

/**
 * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE  
 * ACTIVE CAMERA TO MOVE TO THE REQUESTED PRESET
 */
void MonocleGatewayClient::preset(const int preset) {
  String data = "PRESET:";
  data+= preset;
  send(data);
}

/**
 * SEND RAW COMMAND (STRING) TO MONOCLE GATEWAY 
 */
void MonocleGatewayClient::send(const String& data) {
  send(data.c_str());
}

/**
 * SEND RAW COMMAND (CAHR*) TO MONOCLE GATEWAY 
 */
void MonocleGatewayClient::send(const char* data) {
  _ws.beginMessage(TYPE_TEXT);
  _ws.print(data);
  _ws.endMessage();
}
