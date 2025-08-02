#include "../inc/adwwin.hpp"
#include "../inc/gtk/navbox.hpp"
#include "../inc/gtk/file_item.hpp"
#include <iostream>
#include <filesystem>
#include <thread>
#include <functional>

extern "C"
{
#include <glib-2.0/glib.h>
}
/// @brief gtk4 no working in c++
/// @param app
/// @param user_data
void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = (GtkWidget *)user_data;
    if (window != NULL)
    {
        gtk_window_present(GTK_WINDOW(window));
        return;
    }
    window = adw_application_window_new(app);

    GtkWidget *toolbar_view = adw_toolbar_view_new();
    GtkWidget *header = adw_header_bar_new();
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Icon Browser Adw"));
    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);
    gtk_window_set_default_size(GTK_WINDOW(window), 850, 720);
    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), GTK_WIDGET(toolbar_view)); // Content window

    auto nav = std::make_shared<NavBox>();
    auto files = std::make_unique<FileItem>(nav.get(), GTK_WINDOW(window));

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

    std::thread t1(std::bind(&FileItem::dir_show, *files, path_end.string()));
    t1.join();
    adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), nav->get_box());

    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(window));
}

AdwWin::AdwWin(const char *appId, GApplicationFlags flags)
{
    window = NULL;
    app = adw_application_new(appId, flags);
    g_signal_connect(app, "activate", G_CALLBACK(activate), window);
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