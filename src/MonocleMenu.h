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

      //bool active = false;
//      int updateTimer = 0;

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
    /*
     * Default Constructor
     */
     MonocleMenu(MenuComponentRenderer const& renderer);

     void refresh();
     void loop();
     void activate();
     void deactivate();
     bool isActive();
     void select();
     void reset();
     bool next();
     bool prev();
     bool back();
     void addZoomMenu();

     void onActivate(void (*activateCallback)(void));
     void onDeactivate(void (*deactivateCallback)(void));
     void onHome(void (*homeCallback)(void));
     void onZoom(void (*zoomCallback)(void));
     void onPreset(void (*presetCallback)(const int));

     using SelectFnPtr = void (*)(MenuComponent* menu_component);
};

#endif //MONOCLE_MENU_H
