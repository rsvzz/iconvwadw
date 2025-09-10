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
    GtkWidget *nav_slip, *content, *sider;
    std::shared_ptr<ToolView> s_view, c_view;
    AdwNavigationPage *sidebar_page, *content_page;
public:
    /// @brief ctor
    /// @param  char* siderbar tittle
    /// @param  char* content title 
    NavSplitView(const char*, const char*);
    ~NavSplitView();

    /// @brief adw_navigation_split_view
    /// @return GtkWidget* 
    GtkWidget* get_nav_split_view();
    void set_siderbar_view(GtkWidget*);
    void set_content_view(GtkWidget*);

    ToolView* get_content_view();
};