#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
/// @brief Create grid for path data
/// @details This class is used to create a grid for displaying path data.
class GdView : public Gtk::Grid{
private:
public:
    /// @brief create grid for path data
    /// @param  path
    GdView(std::string);
    ~GdView();
};