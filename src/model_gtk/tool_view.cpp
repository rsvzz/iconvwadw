#include "../../inc/gtk/tool_view.hpp"

ToolView::ToolView(const char* title){
    header = adw_header_bar_new();
    lbl_title = gtk_label_new(title);

    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), lbl_title);
    view = adw_toolbar_view_new();
    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(view), header);
}
ToolView::~ToolView(){
    //gtk_widget_unparent(lbl_title);
    //gtk_widget_unparent(header);
    //gtk_widget_unparent(view);
}

GtkWidget* ToolView::get_view(){
    return view;
}

GtkWidget *ToolView::get_header(){
    return header;
}

void ToolView::set_view_content(GtkWidget* content){
    adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(view), content);
}