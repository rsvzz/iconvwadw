#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>

class ToolView
{
private:
    GtkWidget *header, *view, *lbl_title;
public:
    /// @brief ctor
    /// @param  char* title for header bar
    ToolView(const char*);
    ~ToolView();
    GtkWidget* get_view();
    void set_view_content(GtkWidget*);
    GtkWidget* get_header();
};
