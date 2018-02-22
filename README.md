# Monocle IP Camera Arduino Library
This library works in conjunction with the MonocleCam cloud service to provide camera control and automation for ONVIF supported network/IP cameras.

PTZ (Pan, Tilt, Zoom) control, recalling presets and recalling the camera's home position are supported via a locally running Monocle Gateway service.  The Monocle Gateway service can communicate with the MonocleCam cloud services to obtain a listing of your configured cameras and subscribe to the current camera actively viewed by the Monocle Alexa Smart Home skill.

Sign up for a Monocle account at: https://MonocleCam.com

__Learn more at:__  https://www.hackster.io/monocle/monocle-view-control-ip-cameras-with-alexa-arduino-32bdd3


## Version History
* 0.1 - Initial Release (2018-02-24)

## Library Dependencies

This library depends on:
* [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Classes

This library provides the following classes:
 * [MonocleClientGateway](src/MonocleGatewayClient.h) - Client to Monocle Gateway Service
 * [MonoclePTZJoystick](src/MonoclePTZJoystick.h) Joystick Implementation for 2 or 3 Axis Analog Input Joysticks
 * [MonocleMenu](src/MonocleMenu.h)  Menu System for Monocle PTZ Controllers
 * [MonocleOLED](src/MonocleOLED.h) OLED Wrapper for Monocle PTZ Controllers
 * [MonocleOLEDMenuRenderer.h](src/MonocleOLEDMenuRenderer.h) OLED Menu Renderer for Monocle PTZ Controllers

## Sample Projects

The library includes the following Arduino sample PTZ controller projects:

![example-projects](examples/example-projects.png)

### Deluxe 3-Axis Joystick PTZ Controller

This project implements a 3-axis joystick controller with an Arduino MKR1000 to provide the most sophisticated and feature rich controller of all the project samples we provide. This project implements a small OLED module (128x64 pixels) to serve as a user interface for menu navigation. The third axis on this joystick is a rotational axis that is used for zoom control. All three axis on this joystick provide positional feedback (potentiometers) so we use this information to ramp PTZ movement speed proportionally with the position of the joystick relative to it's center.

#### Source Code
* [Monocle_PTZController_Deluxe_MKR1000](examples/Monocle_PTZController_Deluxe_MKR1000)

#### Project Dependencies

| Library       | Purpose     | URL  |
| ------------- |-------------| -----|
| ArduinoHttpClient      | used for web-socket communication | https://github.com/arduino-libraries/ArduinoHttpClient |
| Adafruit_GFX      | used for OLED display | https://github.com/adafruit/Adafruit-GFX-Library |
| Adafruit_SSD1306  | used for OLED display |  https://github.com/adafruit/Adafruit_SSD1306 |
| Arduino-MenuSystem  | used for menu navigation on OLED display | https://github.com/jonblack/arduino-menusystem |
| Bounce2  | used for debouncing the joystick button |  https://github.com/thomasfredericks/Bounce2 |


#### Bill Of Materials

| Qnty | Item        |  Buy     |
| ---- | ----------- |----------|
| 1 | Arduino MKR1000 (WiFI) | https://store.arduino.cc/usa/arduino-mkr1000 |
| 1 | Diymall 0.96" Inch Yellow Blue I2C Oled 128x64 for Arduino (128x64) |  http://amzn.to/2CvIJG8 |
| 1 | Uxcell 10K Momentary Pushbutton Switch Joystick Potentiometer | http://amzn.to/2BBTWrU |
| 1 | Hammond 1591TSBK Plastic Enclosure (Black) | http://amzn.to/2CA4812 |
| 1 | 10-wire Ribbon Cable (Hook up wire) | http://amzn.to/2ECzv0N |
| 1 | (*OPTIONAL*) Adafruit Lithium Ion Polymer Battery 3.7V 1200mAh | http://amzn.to/2EDDZV2 |
| 1 | (*OPTIONAL*) Micro USB Regulated Power Supply (5VDC 1A) | http://amzn.to/2HqFFyT |


#### Wiring Diagram:

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
