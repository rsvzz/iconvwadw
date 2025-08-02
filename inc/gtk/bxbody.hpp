#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "dark_mode.hpp"
#include <iostream>
extern "C"{
    #include <gtk-4.0/gtk/gtk.h>
}
using std::string;

class BxBody : public Gtk::Box, public DarkMode
{
private:
    Gtk::ScrolledWindow *scrolled_window;
    std::string path;
public:     
    BxBody(const std::string&);
    ~BxBody();
    void create_grid();

};
