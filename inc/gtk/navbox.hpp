#pragma once

#include "incgtk.hpp"

#include <iostream>
using std::string;

class NavBox
{
private:
    /* data */
    GtkWidget *sbar, *stack, *box;
public:
    NavBox(/* args */);
    ~NavBox();
    /// @brief add item stack
    /// @param  widget
    /// @param  name
    /// @param  title
    void add(GtkWidget*, string, string);
    /// @brief get box
    /// @return Widget box
    GtkWidget* get_box();
};