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
#ifndef MONOCLE_GATEWAY_CLIENT_H
#define MONOCLE_GATEWAY_CLIENT_H

#include <ArduinoHttpClient.h>

class MonocleGatewayClient 
{   
   private:
     WebSocketClient _ws;
       
   public:
    /*
     * Default Constructor
     */
     MonocleGatewayClient(Client& client, const char* address, uint16_t port);
     MonocleGatewayClient(Client& client, const String& address, uint16_t port);
     MonocleGatewayClient(Client& client, const IPAddress& address, uint16_t port);

     void begin();
     bool connected();
     void stop();
     void home();     
     void preset(const int preset);     
     void ptz(const int pan, const int tilt, const int zoom);
     void pan(const int pan);
     void tilt(const int tilt);
     void zoom(const int zoom);
     void send(const String& data);
     void send(const char* data);
};

#endif //MONOCLE_GATEWAY_CLIENT_H
