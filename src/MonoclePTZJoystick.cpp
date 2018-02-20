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

#include "Arduino.h"
#include <Bounce2.h>
#include "MonoclePTZJoystick.h"

bool processRead(PinData &pin){

  // abort for any pin that is not configured
  if(pin.pin < 0) return false;

  // get immediate analog pin value
  int value  = (pin.inverted) ? (analogRead(pin.pin) - pin.midpoint)*-1 : analogRead(pin.pin) - pin.midpoint;
  // compare the immediate value with the last known value and the buffer delta
  if(abs(value - pin.value) > pin.buffer){
    pin.value = value;
    return true;
  }
  return false;
}

bool processThreshold(PinData &pin, bool multistateDisabled){

  // if multistate is disabled, then only process low thresholds
  if(!multistateDisabled){

    // PROCESS HIGH THRESHOLD EVALUATION
    if(pin.threshold.high > 0 && pin.value > pin.threshold.high){
      if(pin.state != JOYSTICK_AXIS_HIGH){
        pin.state = JOYSTICK_AXIS_HIGH;
        return true;
      }
      return false;
    }
    if(pin.threshold.high > 0 && pin.value < -pin.threshold.high){
      if(pin.state != -JOYSTICK_AXIS_HIGH){
        pin.state = -JOYSTICK_AXIS_HIGH;
        return true;
      }
      return false;
    }

    // PROCESS MED THRESHOLD EVALUATION
    if(pin.threshold.med > 0 && pin.value > pin.threshold.med){
      if(pin.state != JOYSTICK_AXIS_MED){
        pin.state = JOYSTICK_AXIS_MED;
        return true;
      }
      return false;
    }
    if(pin.threshold.med > 0 && pin.value < -pin.threshold.med){
      if(pin.state != -JOYSTICK_AXIS_MED){
        pin.state = -JOYSTICK_AXIS_MED;
        return true;
      }
      return false;
    }
  }

  // PROCESS LOW THRESHOLD EVALUATION
  if(pin.threshold.low > 0 && pin.value > pin.threshold.low){
    if(pin.state != JOYSTICK_AXIS_LOW){
      pin.state = JOYSTICK_AXIS_LOW;
      return true;
    }
    return false;
  }
  if(pin.threshold.low > 0 && pin.value < -pin.threshold.low){
    if(pin.state != -JOYSTICK_AXIS_LOW){
      pin.state = -JOYSTICK_AXIS_LOW;
      return true;
    }
    return false;
  }

  // SET OFF STATE
  if(pin.state != JOYSTICK_AXIS_OFF){
    pin.state = JOYSTICK_AXIS_OFF;
    return true;
  }
  return false;
}

/**
 * Constructor
 *
 */
MonoclePTZJoystick::MonoclePTZJoystick() {
  // initialize callbacks
  ptzCallback = NULL;
  buttonCallback = NULL;
}

void MonoclePTZJoystick::setupPan(const int analogInputPin, const int resolutionBits) {
  pan.pin = analogInputPin;
  pan.resolution = resolutionBits;
  pan.range = pow(2, resolutionBits);
  pan.midpoint = pan.range/2;
}
void MonoclePTZJoystick::setupTilt(const int analogInputPin, const int resolutionBits) {
  tilt.pin = analogInputPin;
  tilt.resolution = resolutionBits;
  tilt.range = pow(2, resolutionBits);
  tilt.midpoint = tilt.range/2;
}
void MonoclePTZJoystick::setupZoom(const int analogInputPin, const int resolutionBits) {
  zoom.pin = analogInputPin;
  zoom.resolution = resolutionBits;
  zoom.range = pow(2, resolutionBits);
  zoom.midpoint = zoom.range/2;
}

void MonoclePTZJoystick::setupButton(const int digitalPin, const int debounceInterval) {
  // configure the 'select' pin for DEBOUNCE
  // @see: https://www.arduino.cc/en/Tutorial/Debounce
  // @see: https://github.com/thomasfredericks/Bounce2
  debouncer.attach(digitalPin);
  debouncer.interval(debounceInterval);   // interval in milliseconds
}

void MonoclePTZJoystick::setPanThresholdLow(int threshsold){
  pan.threshold.low = abs(threshsold);
}
void MonoclePTZJoystick::setPanThresholdMed(int threshsold){
  pan.threshold.med = abs(threshsold);
}
void MonoclePTZJoystick::setPanThresholdHigh(int threshsold){
  pan.threshold.high = abs(threshsold);
}
void MonoclePTZJoystick::setPanThresholds(int low, int med, int high){
  pan.threshold.low = abs(low);
  pan.threshold.med = abs(med);
  pan.threshold.high = abs(high);
}

void MonoclePTZJoystick::setTiltThresholdLow(int threshsold){
  tilt.threshold.low = abs(threshsold);
}
void MonoclePTZJoystick::setTiltThresholdMed(int threshsold){
  tilt.threshold.med = abs(threshsold);
}
void MonoclePTZJoystick::setTiltThresholdHigh(int threshsold){
  tilt.threshold.high = abs(threshsold);
}
void MonoclePTZJoystick::setTiltThresholds(int low, int med, int high){
  tilt.threshold.low = abs(low);
  tilt.threshold.med = abs(med);
  tilt.threshold.high = abs(high);
}

void MonoclePTZJoystick::setZoomThresholdLow(int threshsold){
  zoom.threshold.low = abs(threshsold);
}
void MonoclePTZJoystick::setZoomThresholdMed(int threshsold){
  zoom.threshold.med = abs(threshsold);
}
void MonoclePTZJoystick::setZoomThresholdHigh(int threshsold){
  zoom.threshold.high = abs(threshsold);
}
void MonoclePTZJoystick::setZoomThresholds(int low, int med, int high){
  zoom.threshold.low = abs(low);
  zoom.threshold.med = abs(med);
  zoom.threshold.high = abs(high);
}

void MonoclePTZJoystick::setAllThresholdLow(int threshsold){
  setPanThresholdLow(threshsold);
  setTiltThresholdLow(threshsold);
  setZoomThresholdLow(threshsold);
}
void MonoclePTZJoystick::setAllThresholdMed(int threshsold){
  setPanThresholdMed(threshsold);
  setTiltThresholdMed(threshsold);
  setZoomThresholdMed(threshsold);
}
void MonoclePTZJoystick::setAllThresholdHigh(int threshsold){
  setPanThresholdHigh(threshsold);
  setTiltThresholdHigh(threshsold);
  setZoomThresholdHigh(threshsold);
}
void MonoclePTZJoystick::setAllThresholds(int low, int med, int high){
  setPanThresholds(low, med, high);
  setTiltThresholds(low, med, high);
  setZoomThresholds(low, med, high);
}

void MonoclePTZJoystick::setPanBuffer(int buffer){
  pan.buffer = buffer;
}
void MonoclePTZJoystick::setTiltBuffer(int buffer){
  tilt.buffer = buffer;
}
void MonoclePTZJoystick::setZoomBuffer(int buffer){
  zoom.buffer = buffer;
}


void MonoclePTZJoystick::invertPanAxis(bool invert){
  pan.inverted = invert;
}
void MonoclePTZJoystick::invertTiltAxis(bool invert){
  tilt.inverted = invert;
}
void MonoclePTZJoystick::invertZoomAxis(bool invert){
  zoom.inverted = invert;
}

int MonoclePTZJoystick::panValue(){
  return pan.value;
}
int MonoclePTZJoystick::tiltValue(){
  return tilt.value;
}
int MonoclePTZJoystick::zoomValue(){
  return zoom.value;
}

int MonoclePTZJoystick::panState(){
  return pan.state;
}
int MonoclePTZJoystick::tiltState(){
  return tilt.state;
}
int MonoclePTZJoystick::zoomState(){
  return zoom.state;
}

void MonoclePTZJoystick::setPTZEventDelay(unsigned int milliseconds){
  ptzEventDelay = milliseconds;
}

void MonoclePTZJoystick::disableMultistate(bool disabled){
  multistateDisabled = disabled;
}

void MonoclePTZJoystick::onPTZ(void (*ptzCallback)(int, int, int)) {
    this->ptzCallback = ptzCallback;
}

void MonoclePTZJoystick::onButtonPress(void (*buttonCallback)(void)){
  this->buttonCallback = buttonCallback;
}


void MonoclePTZJoystick::loop() {
  bool panChanged = false;
  bool tiltChanged = false;
  bool zoomChanged = false;

  // read analog pin values and if a change is detected, then process the updated pin value against its threshold
  if(processRead(pan))  panChanged = processThreshold(pan, multistateDisabled);
  if(processRead(tilt)) tiltChanged = processThreshold(tilt, multistateDisabled);
  if(processRead(zoom)) zoomChanged = processThreshold(zoom, multistateDisabled);

  // detemine if a state has changed and we need to event the PTZ change via callback
  if(panChanged || tiltChanged || zoomChanged) {
    if (ptzCallback != NULL) {
      if(ptzEventDelay > 0)
        ptzEventTime = millis(); // set a timer for a buffer time between PTZ events
      else
        ptzCallback(pan.state, tilt.state, zoom.state);
    }
  }

  // if there is a pending callback waiting, then send it after the elaspsed timer
  if(ptzEventTime > 0 && millis() - ptzEventTime > ptzEventDelay){
    if (ptzCallback != NULL) ptzCallback(pan.state, tilt.state, zoom.state);
    ptzEventTime = 0; // reset timer
  }

  // update the bounce instance for the joystick button
  debouncer.update();

  // determine if the button was pressed
  if(debouncer.fell()){
    if (buttonCallback != NULL) buttonCallback();
  }
}
