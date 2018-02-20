/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *                     MONOCLE PTZ JOYSTICK
 * -------------------------------------------------------------------
 *
 *  This library provides basic logic for a three-axis potentiometer
 *  based Joystick where the X-Axis serves as control for camera
 *  panning, the Y-Axis serves as control for camera tilting and
 *  the Z-Axis (rotation axis) serves as control for camera zoom.
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
#ifndef MONOCLE_PTZ_JOYSTICK_H
#define MONOCLE_PTZ_JOYSTICK_H

#include <Bounce2.h>

#define JOYSTICK_AXIS_HIGH 3
#define JOYSTICK_AXIS_MED  2
#define JOYSTICK_AXIS_LOW  1
#define JOYSTICK_AXIS_OFF  0

#define JOYSTICK_DEFAULT_BUFFER          100
#define JOYSTICK_DEFAULT_LOW_THRESHOLD   1000
#define JOYSTICK_DEFAULT_PTZ_EVENT_DELAY 100   // milliseconds

struct PinThreshold {
  int high;
  int med;
  int low = JOYSTICK_DEFAULT_LOW_THRESHOLD;
};

struct PinData {
  int pin = -1;
  int resolution;
  PinThreshold threshold;
  int value = 0;
  int range;
  int midpoint;
  bool inverted = false;
  int state = JOYSTICK_AXIS_OFF;
  int buffer = JOYSTICK_DEFAULT_BUFFER;
};

class MonoclePTZJoystick
{
   private:
    /* CREATE A BOUND INSTANCE */
    /* @see: https://github.com/thomasfredericks/Bounce2 */
    Bounce debouncer = Bounce();

    /* DATA STRUCTURE FOR EACH AXIS */
    PinData pan;
    PinData tilt;
    PinData zoom;

    /* CALLBACKS */
    void (*ptzCallback)(int pan, int tilt, int zoom);
    void (*buttonCallback)(void);

    /* event delay timer */
    unsigned int ptzEventTime = 0;
    unsigned int ptzEventDelay = JOYSTICK_DEFAULT_PTZ_EVENT_DELAY;
    bool multistateDisabled = false;

   public:
    /*
     * Default Constructor
     */
     MonoclePTZJoystick();

     void setupPan(const int analogInputPin, const int resolutionBits);
     void setupTilt(const int analogInputPin, const int resolutionBits);
     void setupZoom(const int analogInputPin, const int resolutionBits);
     void setupButton(const int digitalPin, const int debounceInterval);

     void setPanThresholdLow(int threshsold);
     void setPanThresholdMed(int threshsold);
     void setPanThresholdHigh(int threshsold);
     void setPanThresholds(int low, int med, int high);

     void setTiltThresholdLow(int threshsold);
     void setTiltThresholdMed(int threshsold);
     void setTiltThresholdHigh(int threshsold);
     void setTiltThresholds(int low, int med, int high);

     void setZoomThresholdLow(int threshsold);
     void setZoomThresholdMed(int threshsold);
     void setZoomThresholdHigh(int threshsold);
     void setZoomThresholds(int low, int med, int high);

     void setAllThresholdLow(int threshsold);
     void setAllThresholdMed(int threshsold);
     void setAllThresholdHigh(int threshsold);
     void setAllThresholds(int low, int med, int high);

     void setPanBuffer(int buffer);
     void setTiltBuffer(int buffer);
     void setZoomBuffer(int buffer);

     void invertPanAxis(bool invert);
     void invertTiltAxis(bool invert);
     void invertZoomAxis(bool invert);

     void setPTZEventDelay(unsigned int milliseconds);

     void onPTZ(void (*ptzCallback)(int, int, int));
     void onButtonPress(void (*buttonCallback)(void));
     void disableMultistate(bool disable);

     int panValue();
     int tiltValue();
     int zoomValue();

     int panState();
     int tiltState();
     int zoomState();

     void loop();
};

#endif //MONOCLE_PTZ_JOYSTICK_H
