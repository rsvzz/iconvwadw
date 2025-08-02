#pragma once
#include <iostream>
#include "navbox.hpp"

using std::string;

class FileItem
{
private:
    /* data */
    NavBox *nav;
    GtkWindow *parent;

public:
    /// @brief 
    /// @param  NavBox
    /// @param  GtkWindow Parent
    FileItem(NavBox*, GtkWindow*);
    ~FileItem();
    void dir_show(string path);
};