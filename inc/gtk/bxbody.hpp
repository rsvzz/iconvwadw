#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "dark_mode.hpp"
#include <iostream>

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