#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

class BxBody : public Gtk::Box
{
private:
    Gtk::ScrolledWindow *scrolled_window;
    std::string path;
public:     
    BxBody(const std::string&);
    ~BxBody();
    void create_grid();

};