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
    FileItem(GtkWindow*);
    ~FileItem();
    void dir_show(string path);
    void dir_show_list_view(string path);
};