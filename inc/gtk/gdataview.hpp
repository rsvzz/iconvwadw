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
    int width, heigth;
public:
    /// @brief create gridview
    /// @param path 
    /// @param GtkWindow parent
    /// @param int width 
    /// @param int heigth
    GridDataView(string path, GtkWindow*, int, int);
    ~GridDataView();
    /// @brief read files, added GtkPicture
    void set_image_grid_for_data();
    GtkWidget* get_grid();
};