/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *                    MONOCLE MENU MANAGER
 * -------------------------------------------------------------------
 *
 *  This library provides a menu implementation for displaying
 *  Monocle navigation menus on a 128x63 or 128x32 OLED dipslay.
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

#include <Arduino.h>

// Arduino-MenuSystem Library
// @see https://github.com/jonblack/arduino-menusystem
#include "MonocleMenu.h"

static bool active = false;
static int updateTimer = 0;
static bool deactivateCallbackPending = false;
static bool activateCallbackPending = false;
static bool homeCallbackPending = false;
static bool zoomCallbackPending = false;
static int presetCallbackPending = 0;

/**
 * Default Constructor
 */
MonocleMenu::MonocleMenu(MenuComponentRenderer const& renderer) :
    ms(renderer),
    miExit("[EXIT]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_exit_callback),
    miHome("Recall Home", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_home_callback),
    miZoom("Zoom", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_zoom_callback),
    mnuPresetsPage1("Recall Preset", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback),
    mnuPresetsPage2("[MORE] ...", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback),
    mnuPresetsPage3("[MORE] ...", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback),
    mnuPresetsPage4("[MORE] ...", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback),
    mnuPresetsPage5("[MORE] ...", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback),
    miPresetsBack1("[BACK]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback, &ms),
    miPresetsBack2("[BACK]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback, &ms),
    miPresetsBack3("[BACK]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback, &ms),
    miPresetsBack4("[BACK]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback, &ms),
    miPresetsBack5("[BACK]", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_callback, &ms),
    miPreset1("Preset 1", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset1_callback),
    miPreset2("Preset 2", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset2_callback),
    miPreset3("Preset 3", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset3_callback),
    miPreset4("Preset 4", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset4_callback),
    miPreset5("Preset 5", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset5_callback),
    miPreset6("Preset 6", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset6_callback),
    miPreset7("Preset 7", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset7_callback),
    miPreset8("Preset 8", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset8_callback),
    miPreset9("Preset 9", (SelectFnPtr)&MonocleMenu::internal_monocle_menu_preset9_callback)
{
  // initialize callbacks
  this->activateCallback = NULL;
  this->deactivateCallback = NULL;
  this->homeCallback = NULL;
  this->zoomCallback = NULL;
  this->presetCallback = NULL;

  // build main menu
  ms.get_root_menu().add_item(&miExit);
  ms.get_root_menu().add_item(&miHome);
  ms.get_root_menu().add_menu(&mnuPresetsPage1);

  // build presets submenu (page 1)
  mnuPresetsPage1.add_item(&miPresetsBack1);
  mnuPresetsPage1.add_item(&miPreset1);
  mnuPresetsPage1.add_item(&miPreset2);
  mnuPresetsPage1.add_menu(&mnuPresetsPage2);

  // build presets submenu (page 2)
  mnuPresetsPage2.add_item(&miPresetsBack2);
  mnuPresetsPage2.add_item(&miPreset3);
  mnuPresetsPage2.add_item(&miPreset4);
  mnuPresetsPage2.add_menu(&mnuPresetsPage3);

  // build presets submenu (page 3)
  mnuPresetsPage3.add_item(&miPresetsBack3);
  mnuPresetsPage3.add_item(&miPreset5);
  mnuPresetsPage3.add_item(&miPreset6);
  mnuPresetsPage3.add_menu(&mnuPresetsPage4);

  // build presets submenu (page 4)
  mnuPresetsPage4.add_item(&miPresetsBack4);
  mnuPresetsPage4.add_item(&miPreset6);
  mnuPresetsPage4.add_item(&miPreset7);
  mnuPresetsPage4.add_menu(&mnuPresetsPage5);

  // build presets submenu (page 5)
  mnuPresetsPage5.add_item(&miPresetsBack5);
  mnuPresetsPage5.add_item(&miPreset8);
  mnuPresetsPage5.add_item(&miPreset9);
}

// INTERNAL CALLBACK HANDLERS
void MonocleMenu::internal_monocle_menu_callback(MenuComponent* p_menu_component){
  updateTimer = millis();
}
void MonocleMenu::internal_monocle_menu_exit_callback(MenuComponent* p_menu_component){
  deactivate();
}
void MonocleMenu::internal_monocle_menu_home_callback(MenuComponent* p_menu_component){
  homeCallbackPending = true;
  deactivate();
}
void MonocleMenu::internal_monocle_menu_zoom_callback(MenuComponent* p_menu_component){
  zoomCallbackPending = true;
  deactivate();
}
void MonocleMenu::internal_monocle_menu_preset1_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 1);
}
void MonocleMenu::internal_monocle_menu_preset2_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 2);
}
void MonocleMenu::internal_monocle_menu_preset3_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 3);
}
void MonocleMenu::internal_monocle_menu_preset4_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 4);
}
void MonocleMenu::internal_monocle_menu_preset5_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 5);
}
void MonocleMenu::internal_monocle_menu_preset6_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 6);
}
void MonocleMenu::internal_monocle_menu_preset7_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 7);
}
void MonocleMenu::internal_monocle_menu_preset8_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 8);
}
void MonocleMenu::internal_monocle_menu_preset9_callback(MenuComponent* p_menu_component){
  internal_monocle_menu_preset_callback(p_menu_component, 9);
}
void MonocleMenu::internal_monocle_menu_preset_callback(MenuComponent* p_menu_component, const int preset){
  presetCallbackPending = preset;
  deactivate();
}

/**
 * FORCE A REFRESH OF THE MENU
 */
void MonocleMenu::refresh() {
  ms.display();
}

/**
 * THIS FUNTION MUST BE CALLED IN THE PROGRAM 
 * MAIN LOOP TO SERVICE THE MENU SYSTEM AND EVENTS
 */
void MonocleMenu::loop() {
  // if the menu is active and we have reached out update timer, then refresh the display on the menu
  if(active && updateTimer > 0 && millis() - updateTimer > MONOCLE_MENU_DISPLAY_INTERVAL) {
    ms.display();
    updateTimer = 0;
  }

  if(activateCallbackPending){
    if (activateCallback != NULL) activateCallback();
    activateCallbackPending = false;
  }
  if(homeCallbackPending){
    if (homeCallback != NULL) homeCallback();
    homeCallbackPending = false;
  }
  if(presetCallbackPending > 0){
    if (presetCallback != NULL) presetCallback(presetCallbackPending);
    presetCallbackPending = 0;
  }
  if(deactivateCallbackPending){
    if (deactivateCallback != NULL) deactivateCallback();
    deactivateCallbackPending = false;
  }
  if(zoomCallbackPending){
    if (zoomCallback != NULL) zoomCallback();
    zoomCallbackPending = false;
  }
}

/**
 * ACTIVATE THE MENU SYSTEM
 */
void MonocleMenu::activate(){
  active = true;  // update active state flag
  ms.reset();     // reset the menu system
  updateTimer = millis(); // set a timer to update the display
  activateCallbackPending = true;
}

/**
 * DEACTIVATE THE MENU SYSTEM
 */
void MonocleMenu::deactivate(){
  active = false;  // update active state flag
  updateTimer = 0;
  deactivateCallbackPending = true;
}

/**
 * RETURNS TRUE OF THE MENU SYSTEM IS ACTIVE
 */
bool MonocleMenu::isActive(){
  return active;
}

/**
 * SELECT THE CURRENT FOCUSED MENU ITEM
 */
void MonocleMenu::select(){
  ms.select();
  updateTimer = millis();
}

/**
 * RESET THE MENU SYSTEM AND ALL MENU ITEMS
 */
void MonocleMenu::reset(){
  ms.reset();
  updateTimer = millis();
}

/**
 * MOVE CURSOR TO THE NEXT MENU ITEM IN THE LIST
 */
bool MonocleMenu::next(){
  updateTimer = millis();
  return ms.next();
}

/**
 * MOVE CURSOR TO THE PREVIOUS MENU ITEM IN THE LIST
 */
bool MonocleMenu::prev(){
  updateTimer = millis();
  return ms.prev();
}

/**
 * MOVE CURSOR BACK TO THE PARENT MENU OF THE CURRENT SUB-MENU
 */
bool MonocleMenu::back(){
  updateTimer = millis();
  return ms.back();
}

/**
 * ADD THE ZOOM MENU ITEM FOR CUSTOM ZOOM 
 * INTEGRATION WHEN NO THIRD AXIS IS AVAILABLE
 */
void MonocleMenu::addZoomMenu(){
  ms.get_root_menu().add_item(&miZoom);
}

/**
 * REGISTER CALLBACK FUNCTION POINTER FOR 
 * NOTIFICATION CALLBACKS WHEN THE MENU SYSTEM
 * BECOMES ACTIVE
 */
void MonocleMenu::onActivate(void (*callback)(void)) {
    this->activateCallback = callback;
}

/**
 * REGISTER CALLBACK FUNCTION POINTER FOR 
 * NOTIFICATION CALLBACKS WHEN THE MENU SYSTEM
 * BECOMES INACTIVE
 */
void MonocleMenu::onDeactivate(void (*callback)(void)) {
    deactivateCallback = callback;
}

/**
 * REGISTER CALLBACK FUNCTION POINTER FOR 
 * NOTIFICATION CALLBACKS WHEN THE 'HOME'
 * MENU ITEM IS SELECTED
 */
void MonocleMenu::onHome(void (*callback)(void)) {
    this->homeCallback = callback;
}

/**
 * REGISTER CALLBACK FUNCTION POINTER FOR 
 * NOTIFICATION CALLBACKS WHEN THE 'ZOOM'
 * MENU ITEM IS SELECTED
 */
void MonocleMenu::onZoom(void (*callback)(void)) {
    this->zoomCallback = callback;
}

/**
 * REGISTER CALLBACK FUNCTION POINTER FOR 
 * NOTIFICATION CALLBACKS WHEN ON OF THE 'PRESET'
 * MENU ITEMS IS SELECTED
 */
void MonocleMenu::onPreset(void (*callback)(const int)) {
    this->presetCallback = callback;
}
