#pragma once
#include "incgtk.hpp"

#include <iostream>

using std::string;

/// @brief used to gtk4
class GridDataView
{
private:
    /* data */
    GtkWidget *grid;
    string path;
    GtkWindow *parent;
public:
    GridDataView(string path, GtkWindow*);
    ~GridDataView();
    /// @brief read files, added GtkPicture
    void set_image_grid_for_data();
    GtkWidget* get_grid();
};