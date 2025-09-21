#pragma once
#include "nav_split_view.hpp"
#include "list_view_content.hpp"
#include <iostream>
#include <memory>

class NavContent : public NavSplitView, public ListViewContent
{
private:
    string path;
    GtkWidget *parent;
    static void on_selection_changed(GObject *object, GParamSpec *pspec, gpointer user_data);
public:
    NavContent(GtkWidget*, string&);
    ~NavContent();
    GtkWindow* get_parent();
    void load_siderbar();
    void set_content(GtkWidget* widget);
};


