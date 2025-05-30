#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

class WinImg : public Gtk::Window
{
private:
    /* data */
    std::string file_name;
    void on_copy_clicked();
public:
    WinImg(const std::string);
    ~WinImg();
};
