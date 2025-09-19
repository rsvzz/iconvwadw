#pragma once
#include "nav_split_view.hpp"
#include "list_view_content.hpp"
#include <iostream>
#include <memory>

class NavContent
{
private:
    string path;
    GtkWidget *parent;
    std::shared_ptr<NavSplitView> nav;
    std::shared_ptr<ListViewContent> content;
    static void on_selection_changed(GObject *object, GParamSpec *pspec, gpointer user_data);
public:
    NavContent(GtkWidget*, string);
    ~NavContent();

    GtkWindow* get_parent();

    std::shared_ptr<NavSplitView> get_nav();
    std::shared_ptr<ListViewContent> get_list_view_content();
    void load_siderbar();
    void set_content(GtkWidget* widget);
};


