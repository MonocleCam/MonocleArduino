/*
 **********************************************************************
 *             __  __  ___  _  _  ___   ___ _    ___
 *            |  \/  |/ _ \| \| |/ _ \ / __| |  | __|
 *            | |\/| | (_) | .` | (_) | (__| |__| _|
 *            |_|  |_|\___/|_|\_|\___/ \___|____|___|
 *
 * -------------------------------------------------------------------
 *                  MONOCLE OLED MENU RENDERER
 * -------------------------------------------------------------------
 *
 *  This library provides a n OLED renderer implementation for the 
 *  Monocle menu system libary. 
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
#ifndef MONOCLE_OLED_MENU_RENDERER_H
#define MONOCLE_OLED_MENU_RENDERER_H

// Arduino-MenuSystem Library
// @see https://github.com/jonblack/arduino-menusystem
#include <MenuSystem.h>

// Monocle Libraries
#include "MonocleOLED.h"
#include "MonocleMenu.h"

class MonocleOLEDMenuRenderer : public MenuComponentRenderer {

  private:
    MonocleOLED* display;
  
  public:

    /*
     * Default Constructor
     */
    MonocleOLEDMenuRenderer(MonocleOLED* display){
      this->display = display;
    }

    /**
     * This method is invoked whenever we need to render the 
     * current menu to the OLED display
     */
    void render(Menu const& menu) const {

        // clear the display first
        display->clearText(false);

        // next, iterate the available menu items
        for (int i = 0; i < menu.get_num_components(); ++i) {
            // get the menu item instance by index
            MenuComponent const* cp_m_comp = menu.get_menu_component(i);

            // build a string to diplay the menu item name; 
            // prefix with a '>' indicator character if this 
            // is the current selected menu item.
            String name = "  ";
            if (cp_m_comp->is_current())
                name  = "> ";
                
            // append the menu item name
            name += cp_m_comp->get_name();

            // print the menu item string to the OLED display
            display->printLine(i, name, false);            
        }

        // force the display to redraw now
        display->display();                
    }

    // the remainder of the interface are no-impl stubs.
    void render_menu_item(MenuItem const& menu_item) const { }
    void render_back_menu_item(BackMenuItem const& menu_item) const { }
    void render_numeric_menu_item(NumericMenuItem const& menu_item) const { }
    void render_menu(Menu const& menu) const { }
};

#endif //MONOCLE_OLED_MENU_RENDERER_H

