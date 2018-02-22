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

     /**     
      * CONFIGURE THE JOYSTICK PAN AXIS
      * Provide the analog input pin and the ADC number of bits resolution
      */
     void setupPan(const int analogInputPin, const int resolutionBits);

     /**     
      * CONFIGURE THE JOYSTICK TILT AXIS
      * Provide the analog input pin and the ADC number of bits resolution
      */
     void setupTilt(const int analogInputPin, const int resolutionBits);
     
     /**     
      * CONFIGURE THE JOYSTICK ZOOM AXIS
      * Provide the analog input pin and the ADC number of bits resolution
      */
     void setupZoom(const int analogInputPin, const int resolutionBits);
     
     /**     
      * CONFIGURE THE JOYSTICK BUTTON 
      * Provide the digital input pin and the debounce interval
      */
     void setupButton(const int digitalPin, const int debounceInterval);

     /**     
      * CONFIGURE THE JOYSTICK PAN THRESHOLD FOR THE LOW SPEED STATE
      */
     void setPanThresholdLow(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK PAN THRESHOLD FOR THE MEDIUM SPEED STATE
      */     
     void setPanThresholdMed(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK PAN THRESHOLD FOR THE HIGH SPEED STATE
      */     
     void setPanThresholdHigh(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK PAN THRESHOLD FOR ALL SPEED STATES
      */     
     void setPanThresholds(int low, int med, int high);

     /**     
      * CONFIGURE THE JOYSTICK TILT THRESHOLD FOR THE LOW SPEED STATE
      */
     void setTiltThresholdLow(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK TILT THRESHOLD FOR THE MEDIUM SPEED STATE
      */     
     void setTiltThresholdMed(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK TILT THRESHOLD FOR THE HIGH SPEED STATE
      */     
     void setTiltThresholdHigh(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK TILT THRESHOLD FOR ALL SPEED STATES
      */     
     void setTiltThresholds(int low, int med, int high);

     /**     
      * CONFIGURE THE JOYSTICK ZOOM THRESHOLD FOR THE LOW SPEED STATE
      */
     void setZoomThresholdLow(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK ZOOM THRESHOLD FOR THE MEDIUM SPEED STATE
      */     
     void setZoomThresholdMed(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK ZOOM THRESHOLD FOR THE HIGH SPEED STATE
      */     
     void setZoomThresholdHigh(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK ZOOM THRESHOLD FOR ALL SPEED STATES
      */     
     void setZoomThresholds(int low, int med, int high);

     /**     
      * CONFIGURE THE JOYSTICK THRESHOLDS ON ALL AXIS FOR THE LOW SPEED STATE
      */
     void setAllThresholdLow(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK THRESHOLDS ON ALL AXIS FOR THE MEDIUM SPEED STATE
      */     
     void setAllThresholdMed(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK THRESHOLDS ON ALL AXIS FOR THE HIGH SPEED STATE
      */     
     void setAllThresholdHigh(int threshsold);

     /**     
      * CONFIGURE THE JOYSTICK THRESHOLDS ON ALL AXIS FOR ALL SPEED STATES
      */     
     void setAllThresholds(int low, int med, int high);
     
     /**     
      * CONFIGURE THE JOYSTICK PAN BUFFER; THIS IS THE DELTA VALUE OF 
      * CHANGE REQUIRED BEFORE A STATE CHANGE IS PERMITTED.  THIS IS 
      * SIMILAR TO DEBOUNCING BUT FOR THE ANALOG INPUT VALUES.
      */
     void setPanBuffer(int buffer);

     /**     
      * CONFIGURE THE JOYSTICK TILT BUFFER; THIS IS THE DELTA VALUE OF 
      * CHANGE REQUIRED BEFORE A STATE CHANGE IS PERMITTED.  THIS IS 
      * SIMILAR TO DEBOUNCING BUT FOR THE ANALOG INPUT VALUES.
      */
     void setTiltBuffer(int buffer);

     /**     
      * CONFIGURE THE JOYSTICK ZOOMN BUFFER; THIS IS THE DELTA VALUE OF 
      * CHANGE REQUIRED BEFORE A STATE CHANGE IS PERMITTED.  THIS IS 
      * SIMILAR TO DEBOUNCING BUT FOR THE ANALOG INPUT VALUES.
      */
     void setZoomBuffer(int buffer);

     /**
      * INVERT THE PAN (X) AXIS; THIS IS HELPFUL IF YOUR 
      * JOYSTICK IS WORKING BACKWARDS.
      */
     void invertPanAxis(bool invert);

     /**
      * INVERT THE TILT (Y) AXIS; THIS IS HELPFUL IF YOUR 
      * JOYSTICK IS WORKING BACKWARDS.
      */
     void invertTiltAxis(bool invert);

     /**
      * INVERT THE ZOOM (Z) AXIS; THIS IS HELPFUL IF YOUR 
      * JOYSTICK IS WORKING BACKWARDS.
      */     
     void invertZoomAxis(bool invert);

     /**
      * DEFINE AN EVENT DELAY FOR PTZ STATE CHANGE EVENTS
      */
     void setPTZEventDelay(unsigned int milliseconds);

     /**
      * REGISTERS A CALLBACK FUNCTION POINTER FOR JOYSTICK AXIS STATE CHANGE EVENTS
      */
     void onPTZ(void (*ptzCallback)(int, int, int));

     /**
      * REGISTERS A CALLBACK FUNCTION POINTER FOR JOYSTICK BUTTON PRESS EVENT
      */     
     void onButtonPress(void (*buttonCallback)(void));

     /**
      * ENABLE OR DISABLE MULTISTATE PTZ EVENTS
      * ---------------------------------------------
      * IF MULTISTATE IS DISABLED, THEN ONLY LOW STATE
      * EVENT WILL BE EVALUATED AND RAISED FOR EVENT CALLBACKS
      * THIS IS HELPFUL IF YOU ONLY WANT TO IMPLEMENT A 
      * SINGLE SPEED CONTROL FOR YOUR JOYSTICK
      */     
     void disableMultistate(bool disable);

     /**
      * GET THE LAST REPORTED/PROCESSED PAN ANALOG VALUE
      */
     int panValue();

     /**
      * GET THE LAST REPORTED/PROCESSED TILT ANALOG VALUE
      */     
     int tiltValue();

     /**
      * GET THE LAST REPORTED/PROCESSED ZOOM ANALOG VALUE
      */     
     int zoomValue();

     /**
      * GET THE LAST EVALUATED PAN STATE
      */
     int panState();

     /**
      * GET THE LAST EVALUATED TILT STATE
      */     
     int tiltState();

     /**
      * GET THE LAST EVALUATED ZOOM STATE
      */     
     int zoomState();

     /**
      * THIS METHOD MUST BE CALLED IN THE PROGRAM MAIN LOOP
      * TO SERVICE THIS CLASS AND PROCESS THESHOLD EVALUATIONS
      * AND AXIS STATE CHANGES
      */
     void loop();
};

#endif //MONOCLE_PTZ_JOYSTICK_H
