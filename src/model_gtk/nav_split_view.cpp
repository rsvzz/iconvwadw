#include "../../inc/gtk/nav_split_view.hpp"
#include <thread>

void NavSplitView::on_button_menu(GtkWidget *btn, gpointer user_data)
{
    auto nav_view = static_cast<NavSplitView *>(user_data);
    gtk_widget_set_visible(nav_view->get_popover(), TRUE);
}

NavSplitView::NavSplitView(const char* s_title, const char* c_title, GtkWidget* _parent) : win_parent(_parent)
{
    s_view = std::make_shared<ToolView>(s_title);
    c_view = std::make_shared<ToolView>(c_title);

    GtkWidget* header_sider = s_view->get_header();
    menu_button = gtk_button_new_from_icon_name("open-menu-symbolic");

    g_signal_connect(menu_button, "clicked", G_CALLBACK(&NavSplitView::on_button_menu), static_cast<gpointer>(this));
    GMenu *menu = g_menu_new();
    GMenuItem *m_about = g_menu_item_new("About", "app.about");
    g_menu_append_item(menu, m_about);

    GSimpleAction *action = g_simple_action_new("about", NULL);
    g_signal_connect(action, "activate", G_CALLBACK(&NavSplitView::on_about_activate), static_cast<gpointer>(this));
    g_action_map_add_action(G_ACTION_MAP(gtk_window_get_application(GTK_WINDOW(win_parent))), G_ACTION(action));


    popover = gtk_popover_menu_new_from_model(G_MENU_MODEL(menu));
    g_signal_connect(popover, "closed", G_CALLBACK(&NavSplitView::on_popover_closed), NULL);
    gtk_widget_set_parent(popover, menu_button);
    gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
    gtk_popover_set_autohide(GTK_POPOVER(popover), TRUE);
    gtk_widget_set_visible(popover, FALSE);

    adw_header_bar_pack_end(ADW_HEADER_BAR(header_sider), menu_button);

    sidebar_page = adw_navigation_page_new(s_view->get_view(), "");
    content_page = adw_navigation_page_new(c_view->get_view(), "");

    nav_slip = adw_navigation_split_view_new();
    adw_navigation_split_view_set_sidebar(ADW_NAVIGATION_SPLIT_VIEW(nav_slip), sidebar_page);
    adw_navigation_split_view_set_content(ADW_NAVIGATION_SPLIT_VIEW(nav_slip), content_page);
}

void NavSplitView::on_popover_closed(GtkPopover *popover, gpointer user_data)
{
    gtk_widget_set_visible(GTK_WIDGET(popover), FALSE);
}

NavSplitView::~NavSplitView()
{
    //g_print("NavSplitView ~ctor \n");
}

void show_about (GtkApplication *app)
{
  const char *developers[] = {
    "rsvzz",
    NULL
  };

  const char *designers[] = {
    "Free Software Contributor",
    NULL
  };

  adw_show_about_dialog (GTK_WIDGET (gtk_application_get_active_window (app)),
                         "application-name", ("Icon Browser Adw"),
                         "application-icon", "io.github.rsvzz.iconvwadw",
                         "version", "0.1.17",
                         "copyright", "© 2025 rsvzz",
                         "issue-url", "https://github.com/rsvzz/iconvwadw/issues",
                         "license-type", GTK_LICENSE_GPL_3_0,
                         "developers", developers,
                         "designers", designers,
                         "translator-credits", ("translator-credits"),
                         NULL);
}

void NavSplitView::on_about_activate(GSimpleAction *action, GVariant *parameter, gpointer user_data){
    auto nav_view = static_cast<NavSplitView*>(user_data);

     gtk_widget_set_visible(nav_view->get_popover(), FALSE);

     show_about(gtk_window_get_application(GTK_WINDOW(nav_view->get_parent())));
}

GtkWidget* NavSplitView::get_nav_split_view(){ return nav_slip;}

void NavSplitView::set_siderbar_view(GtkWidget* content){
    std::thread thr1(&ToolView::set_view_content, s_view, content);
    thr1.detach();
    //s_view->set_view_content(content);
}

void NavSplitView::set_content_view(GtkWidget* content){
    std::thread thr1(&ToolView::set_view_content, c_view, content);
    thr1.join();
    //c_view->set_view_content(content);
}

std::shared_ptr<ToolView> NavSplitView::get_content_view(){ return c_view;}

GtkWidget* NavSplitView::get_popover(){ return popover;}

GtkWidget* NavSplitView::get_parent(){ return win_parent;}