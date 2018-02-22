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

 #ifndef MONOCLE_MENU_H
#define MONOCLE_MENU_H

#define MONOCLE_MENU_DISPLAY_INTERVAL 50 // milliseconds

// Arduino-MenuSystem Library
// @see https://github.com/jonblack/arduino-menusystem
#include <MenuSystem.h>

class MonocleMenu
{
   private:
      /* INTERNAL DATA ITEMS FOR MENU SYSTEM */
      MenuSystem ms;
      MenuItem miExit;
      MenuItem miHome;
      MenuItem miZoom;
      Menu mnuPresetsPage1;
      Menu mnuPresetsPage2;
      Menu mnuPresetsPage3;
      Menu mnuPresetsPage4;
      Menu mnuPresetsPage5;
      BackMenuItem miPresetsBack1;
      BackMenuItem miPresetsBack2;
      BackMenuItem miPresetsBack3;
      BackMenuItem miPresetsBack4;
      BackMenuItem miPresetsBack5;
      MenuItem miPreset1;
      MenuItem miPreset2;
      MenuItem miPreset3;
      MenuItem miPreset4;
      MenuItem miPreset5;
      MenuItem miPreset6;
      MenuItem miPreset7;
      MenuItem miPreset8;
      MenuItem miPreset9;

      /* INTERNAL CALLBACKS */
      void internal_monocle_menu_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_exit_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_home_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_zoom_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset1_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset2_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset3_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset4_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset5_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset6_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset7_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset8_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset9_callback(MenuComponent* p_menu_component);
      void internal_monocle_menu_preset_callback(MenuComponent* p_menu_component, const int preset);

      /* USER CALLBACKS */
      void (*activateCallback)(void);
      void (*deactivateCallback)(void);
      void (*homeCallback)(void);
      void (*zoomCallback)(void);
      void (*presetCallback)(const int preset);

   public:
    /**
     * Default Constructor
     */
     MonocleMenu(MenuComponentRenderer const& renderer);

     /**
      * FORCE A REFRESH OF THE MENU
      */
     void refresh();

     /**
      * THIS FUNTION MUST BE CALLED IN THE PROGRAM 
      * MAIN LOOP TO SERVICE THE MENU SYSTEM AND EVENTS
      */
     void loop();

     /**
      * ACTIVATE THE MENU SYSTEM
      */
     void activate();

     /**
      * DEACTIVATE THE MENU SYSTEM
      */
     void deactivate();

     /**
      * RETURNS TRUE OF THE MENU SYSTEM IS ACTIVE
      */
     bool isActive();

     /**
      * SELECT THE CURRENT FOCUSED MENU ITEM
      */
     void select();

     /**
      * RESET THE MENU SYSTEM AND ALL MENU ITEMS
      */
     void reset();

     /**
      * MOVE CURSOR TO THE NEXT MENU ITEM IN THE LIST
      */
     bool next();

     /**
      * MOVE CURSOR TO THE PREVIOUS MENU ITEM IN THE LIST
      */
     bool prev();

     /**
      * MOVE CURSOR BACK TO THE PARENT MENU OF THE CURRENT SUB-MENU
      */
     bool back();

     /**
      * ADD THE ZOOM MENU ITEM FOR CUSTOM ZOOM 
      * INTEGRATION WHEN NO THIRD AXIS IS AVAILABLE
      */
     void addZoomMenu();

     /**
      * REGISTER CALLBACK FUNCTION POINTER FOR 
      * NOTIFICATION CALLBACKS WHEN THE MENU SYSTEM
      * BECOMES ACTIVE
      */
     void onActivate(void (*activateCallback)(void));

     /**
      * REGISTER CALLBACK FUNCTION POINTER FOR 
      * NOTIFICATION CALLBACKS WHEN THE MENU SYSTEM
      * BECOMES INACTIVE
      */
     void onDeactivate(void (*deactivateCallback)(void));

     /**
      * REGISTER CALLBACK FUNCTION POINTER FOR 
      * NOTIFICATION CALLBACKS WHEN THE 'HOME'
      * MENU ITEM IS SELECTED
      */
     void onHome(void (*homeCallback)(void));

     /**
      * REGISTER CALLBACK FUNCTION POINTER FOR 
      * NOTIFICATION CALLBACKS WHEN THE 'ZOOM'
      * MENU ITEM IS SELECTED
      */
     void onZoom(void (*zoomCallback)(void));

     /**
      * REGISTER CALLBACK FUNCTION POINTER FOR 
      * NOTIFICATION CALLBACKS WHEN ON OF THE 'PRESET'
      * MENU ITEMS IS SELECTED
      */
     void onPreset(void (*presetCallback)(const int));

     // using for casting internally
     using SelectFnPtr = void (*)(MenuComponent* menu_component);
};

#endif //MONOCLE_MENU_H
