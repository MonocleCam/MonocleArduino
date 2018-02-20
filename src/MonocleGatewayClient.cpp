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
 *  to a Moncole Gateway service to perform camera control.
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
 * Constructor
 *
 */
MonocleGatewayClient::MonocleGatewayClient(Client& client, const char* address, uint16_t port) : _ws(client, address, port) {
}

MonocleGatewayClient::MonocleGatewayClient(Client& client, const String& address, uint16_t port) : _ws(client, address, port) {
}

MonocleGatewayClient::MonocleGatewayClient(Client& client, const IPAddress& address, uint16_t port) : _ws(client, address, port) {
}

void MonocleGatewayClient::begin() {
  _ws.begin();
}

bool MonocleGatewayClient::connected() {
  return _ws.connected();
}

void MonocleGatewayClient::home() {
  send("HOME");
}

void MonocleGatewayClient::ptz(const int pan, const int tilt, const int zoom) {
  String data = "PTZ:";
  data = data + pan;
  data = data + ":" + tilt;
  data = data + ":" + zoom;
  send(data);
}

void MonocleGatewayClient::stop() {
  send("STOP");
}

void MonocleGatewayClient::pan(const int pan) {
  String data = "PAN:";
  data+= pan;
  send(data);
}

void MonocleGatewayClient::tilt(const int tilt) {
  String data = "TILT:";
  data+= tilt;
  send(data);
}

void MonocleGatewayClient::zoom(const int zoom) {
  String data = "ZOOM:";
  data+= zoom;
  send(data);
}

void MonocleGatewayClient::preset(const int preset) {
  String data = "PRESET:";
  data+= preset;
  send(data);
}

void MonocleGatewayClient::send(const String& data) {
  send(data.c_str());
}

void MonocleGatewayClient::send(const char* data) {
  _ws.beginMessage(TYPE_TEXT);
  _ws.print(data);
  _ws.endMessage();
}
