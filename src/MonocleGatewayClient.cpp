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
#include <ArduinoJson.h>

/**
 * Constructors
 */
MonocleGatewayClient::MonocleGatewayClient(Client& client, const char* address, uint16_t port) : _ws(client, address, port) {
  // initialize active camera attributes
  _camera.uuid = "";
  _camera.name = "";
  _camera.manufacturer = "";
  _camera.model = "";
  _camera.error = "";
  _camera.ptz = false;

  // initialize callbacks
  cameraCallback = NULL;
}
MonocleGatewayClient::MonocleGatewayClient(Client& client, const String& address, uint16_t port) : _ws(client, address, port) {
  // initialize active camera attributes
  _camera.uuid = "";
  _camera.name = "";
  _camera.manufacturer = "";
  _camera.model = "";
  _camera.error = "";
  _camera.ptz = false;

  // initialize callbacks
  cameraCallback = NULL;
}
MonocleGatewayClient::MonocleGatewayClient(Client& client, const IPAddress& address, uint16_t port) : _ws(client, address, port) {
  // initialize active camera attributes
  _camera.uuid = "";
  _camera.name = "";
  _camera.manufacturer = "";
  _camera.model = "";
  _camera.error = "";
  _camera.ptz = false;

  // initialize callbacks
  cameraCallback = NULL;
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
  String data = "PRESET:#";
  data+= (preset-1);  // presets by index are zero based
  send(data);
}

/**
 * SEND RAW COMMAND (STRING) TO MONOCLE GATEWAY
 */
void MonocleGatewayClient::send(const String& data) {
  send(data.c_str());
}

/**
 * SEND RAW COMMAND (CHAR*) TO MONOCLE GATEWAY
 */
void MonocleGatewayClient::send(const char* data) {
  _ws.beginMessage(TYPE_TEXT);
  _ws.print(data);
  _ws.endMessage();
}

/**
 * REGISTERS A CALLBACK FUNCTION POINTER FOR CAMERA SOURCE CHANGES
 */
void MonocleGatewayClient::onCameraChange(void (*cameraCallback)(CameraSource& camera)){
  this->cameraCallback = cameraCallback;
}

/**
 * GET THE ACTIVE CAMERA SOURCE
 */
CameraSource MonocleGatewayClient::activeCameraSource(){
  return this->_camera;
}

/**
 * GET THE ACTIVE CAMERA ENABLED STATE
 */
bool MonocleGatewayClient::isCameraEnabled(){
  return (!this->_camera.error && this->_camera.ptz);
}

/**
 * THIS FUNTION MUST BE CALLED IN THE PROGRAM
 * MAIN LOOP TO SERVICE THE MONOCLE GATEWAY CLIENT
 * AND DISPATCH ANY EVENTS
 */
void MonocleGatewayClient::loop(){
    // no need to process anything if we are not connected
    if(!_ws.connected()) return;

    // we don't need to process the message queue on every loop iteraction
    // so we use this timing logic to only process the queue once per second
    if((millis() - _processingTimer) < MONOCLE_GATEWAY_PROCESSING_INTERVAL) return;
    _processingTimer = millis();

    // check if a message is available to be received
    int messageSize = _ws.parseMessage();
    if (messageSize > 0) {
      String raw = _ws.readString();

      // parse JSON message received from MonocleGateway
      DynamicJsonBuffer jsonBuffer;
      JsonObject& payload = jsonBuffer.parseObject(raw);

      // look for 'source' message (its the only one we currently care about)
      if(payload.containsKey("source")){
        JsonObject& source = payload["source"];

        // we have received a new source, lets reset all active camera attributes
        _camera.uuid = "";
        _camera.name = "";
        _camera.manufacturer = "";
        _camera.model = "";
        _camera.ptz = false;
        _camera.error = false;
        _camera.errorMessage = "";

        // populate the active source attributes from the source object in the JSON message
        if(source.containsKey("uuid"))
          _camera.uuid = source["uuid"];
        if(source.containsKey("name"))
          _camera.name = source["name"];
        if(source.containsKey("manufacturer"))
          _camera.manufacturer = source["manufacturer"];
        if(source.containsKey("model"))
          _camera.model = source["model"];
        if(source.containsKey("ptz"))
          _camera.ptz = source.get<bool>("ptz");
        if(source.containsKey("error")){
          _camera.errorMessage = source["error"];
          _camera.error = (strlen(_camera.errorMessage) > 0);
        }

        // raise callback for camera change
        if (cameraCallback != NULL) cameraCallback(_camera);
      }
      else {
        Serial.println("NO SOURCE");
      }
    }
}
