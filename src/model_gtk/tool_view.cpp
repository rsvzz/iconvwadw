#include "../../inc/gtk/tool_view.hpp"

ToolView::ToolView(const char *title)
{

    header = adw_header_bar_new();
    g_print("Tool view \n");
    lbl_title = gtk_label_new(title);
    view = adw_toolbar_view_new();

    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), lbl_title);

    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(view), header);
}

ToolView::~ToolView()
{
    // gtk_widget_unparent(lbl_title);
    // gtk_widget_unparent(header);
    // gtk_widget_unparent(view);
}

GtkWidget *ToolView::get_view()
{
    return view;
}

GtkWidget *ToolView::get_header()
{
    return header;
}

void ToolView::set_view_content(GtkWidget *content)
{

    if (view != NULL)
    {
        GtkWidget *scroll = gtk_scrolled_window_new();
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), content);
        adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(view), scroll);
    }
}
