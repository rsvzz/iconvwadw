#include "../../inc/gtk/nav_split_view.hpp"

NavSplitView::NavSplitView(const char* s_title, const char* c_title)
{
    s_view = std::make_shared<ToolView>(s_title);
    c_view = std::make_shared<ToolView>(c_title);

    GtkWidget* header_sider = s_view->get_header();
    GtkWidget* menu_button = gtk_menu_button_new();
    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(menu_button), "open-menu-symbolic");
    adw_header_bar_pack_end(ADW_HEADER_BAR(header_sider), menu_button);

    nav_slip = adw_navigation_split_view_new();

    AdwNavigationPage *sidebar_page = adw_navigation_page_new(s_view->get_view(), "");
    AdwNavigationPage *content_page = adw_navigation_page_new(c_view->get_view(), "iconvwadw");

    adw_navigation_split_view_set_sidebar(ADW_NAVIGATION_SPLIT_VIEW(nav_slip), sidebar_page);
    adw_navigation_split_view_set_content(ADW_NAVIGATION_SPLIT_VIEW(nav_slip), content_page);

}

NavSplitView::~NavSplitView()
{
}

GtkWidget* NavSplitView::get_nav_split_view(){ return nav_slip;}

void NavSplitView::set_siderbar_view(GtkWidget* content){
    s_view->set_view_content(content);
}

void NavSplitView::set_content_view(GtkWidget* content){
    c_view->set_view_content(content);
}