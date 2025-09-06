#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <iostream>
#include <stack>
#include <memory>
#include "file_item.hpp"

class ListViewContent
{
private:
    /* data */
    GtkWidget* parent, *list_view;
    std::shared_ptr<FileItem> file_item;
    std::string path;
public:
    ListViewContent(GtkWidget*, string);
    ~ListViewContent();
    GtkWidget* get_list_view();
};

