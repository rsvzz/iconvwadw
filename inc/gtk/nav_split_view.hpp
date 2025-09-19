#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include "tool_view.hpp"
#include <iostream>
#include <memory>

/// @brief create adw_navigation_split_view_new
class NavSplitView
{
private:
    GtkWidget *nav_slip, *content, *sider, *popover, *win_parent, *menu_button;
    std::shared_ptr<ToolView> s_view, c_view;
    AdwNavigationPage *sidebar_page, *content_page;
    static void on_about_activate(GSimpleAction *action, GVariant *parameter, gpointer user_data);
    static void on_button_menu(GtkWidget*, gpointer);
    static void on_popover_closed(GtkPopover *, gpointer);
public:
    /// @brief ctor
    /// @param  char* siderbar tittle
    /// @param  char* content title 
    /// @param  GtkWidget* parent 
    NavSplitView(const char*, const char*, GtkWidget*);
    ~NavSplitView();

    /// @brief adw_navigation_split_view
    /// @return GtkWidget* 
    GtkWidget* get_nav_split_view();
    void set_siderbar_view(GtkWidget*);
    void set_content_view(GtkWidget*);

    std::shared_ptr<ToolView> get_content_view();

    GtkWidget* get_popover();
    GtkWidget* get_parent();

};