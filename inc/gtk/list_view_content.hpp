#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <iostream>
#include <stack>
#include <memory>
#include "file_item.hpp"
#include "nav_split_view.hpp"

class ListViewContent
{
private:
    /* data */
    GtkWidget* parent, *list_view;
    std::shared_ptr<FileItem> file_item;
    std::string path;
    NavSplitView *nav;
    static void on_selection_changed(GObject *object, GParamSpec *pspec, gpointer user_data);
public:
    ListViewContent(GtkWidget*, string, NavSplitView*);
    ~ListViewContent();
    GtkWidget* get_list_view();
    NavSplitView* get_nav();
    GtkWidget* get_parent();
};

