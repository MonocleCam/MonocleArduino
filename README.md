# Monocle IP Camera Arduino Library
This library works in conjunction with the MonocleCam cloud service to provide camera control and automation for ONVIF supported network/IP cameras.

PTZ (Pan, Tilt, Zoom) control, recalling presets and recalling the camera's home position are supported via a locally running Monocle Gateway service.  The Monocle Gateway service can communicate with the MonocleCam cloud services to obtain a listing of your configured cameras and subscribe to the current camera actively viewed by the Monocle Alexa Smart Home skill.

Sign up for a Monocle account at: https://MonocleCam.com

Learn more at:  https://www.hackster.io/monocle/monocle-view-control-ip-cameras-with-alexa-arduino-32bdd3

## Version History
* 0.1 - Initial Release (2018-02-24)

## Dependencies

This library depend on:
* [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Classes

This library provides the following classes:
 * [MonocleClientGateway](src/MonocleGatewayClient.h) - Client to Monocle Gateway Service
 * [MonoclePTZJoystick](src/MonoclePTZJoystick.h) Joystick Implementation for 2 or 3 Axis Analog Input Joysticks
 * [MonocleMenu](src/MonocleMenu.h)  Menu System for Monocle PTZ Controllers
 * [MonocleOLED](src/MonocleOLED.h) OLED Wrapper for Monocle PTZ Controllers
 * [MonocleOLEDMenuRenderer.h](src/MonocleOLEDMenuRenderer.h) OLED Menu Renderer for Monocle PTZ Controllers

## Sample Projects

The library includes the following sample PTZ controller projects:

![example-projects](examples/example-projects.png)

### Deluxe 3-Axis Joystick PTZ Controller
* [Monocle_PTZController_Deluxe_MKR1000](examples/Monocle_PTZController_Deluxe_MKR1000)

![Monocle_PTZController_Deluxe_MKR1000](examples/Monocle_PTZController_Deluxe_MKR1000/extras/Monocle_PTZController_Deluxe_MKR1000.png)


### Basic 2-Axis Joystick PTZ Controller
* [Monocle_PTZController_Basic_MKR1000](examples/Monocle_PTZController_Basic_MKR1000)

![Monocle_PTZController_Basic_MKR1000](examples/Monocle_PTZController_Basic_MKR1000/extras/Monocle_PTZController_Basic_MKR1000.png)


### Retro Gaming Joystick PTZ Controller
* [Monocle_PTZController_AtariJoystick_MKR1000](examples/Monocle_PTZController_AtariJoystick_MKR1000)

![Monocle_PTZController_AtariJoystick_MKR1000](examples/Monocle_PTZController_AtariJoystick_MKR1000/extras/Monocle_PTZController_AtariJoystick_MKR1000.png)

* [Monocle_PTZController_AtariJoystick_ESP8266](examples/Monocle_PTZController_AtariJoystick_ESP8266)

![Monocle_PTZController_AtariJoystick_ESP8266](examples/Monocle_PTZController_AtariJoystick_ESP8266/extras/Monocle_PTZController_AtariJoystick_ESP8266.png)

* [Monocle_PTZController_AtariJoystick_ESP32](examples/Monocle_PTZController_AtariJoystick_ESP32)

![Monocle_PTZController_AtariJoystick_ESP32](examples/Monocle_PTZController_AtariJoystick_ESP32/extras/Monocle_PTZController_AtariJoystick_ESP32.png)


### IR Remote Control PTZ Controller
* [Monocle_PTZController_IRRemote_MKR1000](examples/Monocle_PTZController_IRRemote_MKR1000)

![Monocle_PTZController_IRRemote_MKR1000](examples/Monocle_PTZController_IRRemote_MKR1000/extras/Monocle_PTZController_IRRemote_MKR1000.png)

* [Monocle_PTZController_IRRemote_ESP32](examples/Monocle_PTZController_IRRemote_ESP32)

![Monocle_PTZController_IRRemote_ESP32](examples/Monocle_PTZController_IRRemote_ESP32/extras/Monocle_PTZController_IRRemote_ESP32.png)
