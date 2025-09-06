#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include "gtk/nav_split_view.hpp"
#include "gtk/list_view_content.hpp"

#include <iostream>
#include <memory>

class AdwWin
{
private:
    /* data */
    AdwApplication *app;
    GtkWidget *window;
    std::shared_ptr<NavSplitView> split_view;
    std::shared_ptr<ListViewContent> siderbar_view;
public:
    AdwWin(const char*, GApplicationFlags);
    ~AdwWin();

    int Run(int, char**);
    GtkWidget* get_window();
    std::shared_ptr<NavSplitView> get_split_view();
    void set_siderbar_view(GtkWidget*, std::string);
    std::shared_ptr<ListViewContent> get_siderbar_view();
};

