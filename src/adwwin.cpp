#include "../inc/adwwin.hpp"
#include "../inc/gtk/navbox.hpp"
#include "../inc/gtk/file_item.hpp"
#include <iostream>
#include <filesystem>
#include <thread>

extern "C"
{
#include <glib-2.0/glib.h>
}
/// @brief gtk4 no working in c++
/// @param app
/// @param user_data
void activate(GtkApplication *app, gpointer user_data)
{
    auto win = static_cast<AdwWin *>(user_data);
    GtkWidget *window = win->get_window();
    if (window != nullptr)
    {
        gtk_window_present(GTK_WINDOW(window));
        return;
    }
    window = adw_application_window_new(app);
    auto split_view = win->get_split_view();
    split_view = std::make_shared<NavSplitView>("", "Icon Browser Adw");
    gtk_window_set_default_size(GTK_WINDOW(window), 850, 720);

    // GtkWidget *toolbar_view = adw_toolbar_view_new();
    // GtkWidget *header = adw_header_bar_new();
    /*
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Icon Browser Adw"));
    GtkWidget *menu_button = gtk_menu_button_new();
    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(menu_button), "open-menu-symbolic");
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), menu_button);
    */
    // adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);
    // gtk_window_set_default_size(GTK_WINDOW(window), 850, 720);
    // adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), GTK_WIDGET(toolbar_view)); // Content window

    // auto nav = std::make_shared<NavBox>();
    // auto files = std::make_unique<FileItem>(nav.get(), GTK_WINDOW(window));

    std::filesystem::path exe_path = std::filesystem::read_symlink("/proc/self/exe");
    std::filesystem::path app_root, path_end;
    gchar *temp_path = nullptr;
    if (g_getenv("SNAP") != NULL)
    {
        app_root = exe_path.parent_path();
        temp_path = g_build_filename(app_root.string().c_str(), "../usr/share/icons/Adwaita/symbolic", nullptr);
        path_end = std::filesystem::path(temp_path);
    }
    else
    {
        app_root = exe_path.root_directory();
        // g_print("parent path: %s \n", app_root.string().c_str());
        temp_path = g_build_filename(app_root.string().c_str(), "../usr/share/icons/Adwaita/symbolic", nullptr);
        // g_print("join: %s \n", temp_path);
        if (std::filesystem::is_directory(temp_path) == 1)
        {
            path_end = g_build_filename(app_root.string().c_str(), "/usr/share/icons/Adwaita/symbolic", nullptr);
        }
        else
        {
            path_end = std::filesystem::path(temp_path);
        }
    }

    g_free(temp_path);

    // std::thread t1(std::bind(&FileItem::dir_show, *files, path_end.string()));
    // t1.join();
    win->set_siderbar_view(window, path_end.string());
    split_view->set_siderbar_view(win->get_siderbar_view()->get_list_view());

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), split_view->get_nav_split_view());
    // adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), nav->get_box());
    gtk_window_present(GTK_WINDOW(window));
}

AdwWin::AdwWin(const char *appId, GApplicationFlags flags)
{
    window = NULL;
    app = adw_application_new(appId, flags);
    g_signal_connect(app, "activate", G_CALLBACK(activate), static_cast<gpointer>(this));
}

AdwWin::~AdwWin()
{
}

int AdwWin::Run(int argc, char **argv)
{
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

GtkWidget *AdwWin::get_window()
{
    return window;
}

std::shared_ptr<NavSplitView> AdwWin::get_split_view()
{
    return split_view;
}

std::shared_ptr<ListViewContent> AdwWin::get_siderbar_view()
{
    return siderbar_view;
}

void AdwWin::set_siderbar_view(GtkWidget *_parent, string path)
{
    siderbar_view = std::make_shared<ListViewContent>(_parent, path);
}