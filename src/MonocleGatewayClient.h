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
#ifndef MONOCLE_GATEWAY_CLIENT_H
#define MONOCLE_GATEWAY_CLIENT_H

#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

#define MONOCLE_GATEWAY_PROCESSING_INTERVAL 1000

struct CameraSource {
  const char* uuid;
  const char* name;
  const char* manufacturer;
  const char* model;
  bool  ptz;
  bool  error;
  const char* errorMessage;
};

class MonocleGatewayClient
{
   private:
     WebSocketClient _ws;
     unsigned long _processingTimer;
     CameraSource _camera;

   public:
     /*
      * Default Constructors
      */
     MonocleGatewayClient(Client& client, const char* address, uint16_t port);
     MonocleGatewayClient(Client& client, const String& address, uint16_t port);
     MonocleGatewayClient(Client& client, const IPAddress& address, uint16_t port);

     /* CALLBACKS */
     void (*cameraCallback)(CameraSource& camera);

    /**
     * START THE CONNECTION TO THE
     * TO THE MONOCLE GATEWAY
     */
     void begin();

    /**
     * DETEMINE THE CONNECTION STATE
     * RETURNS 'true' IF CURRENTLY CONNECTED
     * TO THE MONOCLE GATEWAY
     */
     bool connected();

     /**
      * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE
      * ACTIVE CAMERA TO STOP ALL MOVEMENT IMMEDIATELY
      */
     void stop();

     /**
      * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE
      * ACTIVE CAMERA TO RECALL AND MOVE TO ITS
      * PRECONFIGURED HOME POSITION
      */
     void home();

     /**
      * SEND INSTRUCTION TO MONOCLE GATEWAY FOR THE
      * ACTIVE CAMERA TO MOVE TO THE REQUESTED PRESET
      */
     void preset(const int preset);

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
     void ptz(const int pan, const int tilt, const int zoom);

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
     void pan(const int pan);

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
     void tilt(const int tilt);

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
     void zoom(const int zoom);

     /**
      * SEND RAW COMMAND (STRING) TO MONOCLE GATEWAY
      */
     void send(const String& data);

     /**
      * SEND RAW COMMAND (CHAR*) TO MONOCLE GATEWAY
      */
     void send(const char* data);

     /**
      * THIS FUNTION MUST BE CALLED IN THE PROGRAM
      * MAIN LOOP TO SERVICE THE MONOCLE GATEWAY CLIENT
      * AND DISPATCH ANY EVENTS
      */
     void loop();

     /**
      * REGISTERS A CALLBACK FUNCTION POINTER FOR CAMERA SOURCE CHANGES
      */
     void onCameraChange(void (*cameraCallback)(CameraSource& camera));

     /**
      * GET THE ACTIVE CAMERA SOURCE
      */
     CameraSource activeCameraSource();

     /**
      * GET THE ACTIVE CAMERA ENABLED STATE
      */
     bool isCameraEnabled();
};

#endif //MONOCLE_GATEWAY_CLIENT_H
