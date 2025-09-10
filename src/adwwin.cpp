#include "../inc/adwwin.hpp"
#include "../inc/gtk/navbox.hpp"
#include "../inc/gtk/file_item.hpp"

#include <filesystem>
#include <thread>
#include <memory>

extern "C"
{
#include <glib-2.0/glib.h>
}
/// @brief gtk4 no working in c++
/// @param app
/// @param user_data
void AdwWin::activate(GtkApplication *app, gpointer user_data)
{
    g_print("active run \n");
    auto win = static_cast<AdwWin *>(user_data);
    GtkWidget *window = win->get_window();
    if (window != nullptr)
    {
        gtk_window_present(GTK_WINDOW(window));
        return;
    }

    window = adw_application_window_new(app);
    
    auto split_view = win->get_split_view();
    
    gtk_window_set_default_size(GTK_WINDOW(window), 850, 720);

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
    
    split_view = new NavSplitView("Icon Browser Adw", "");
    win->set_siderbar_view(window, path_end.string(), split_view);
    split_view->set_siderbar_view(win->get_siderbar_view()->get_list_view());

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), split_view->get_nav_split_view());
    gtk_window_present(GTK_WINDOW(window));
}

AdwWin::AdwWin(const char *appId, GApplicationFlags flags)
{
    window = NULL;  
    app = adw_application_new(appId, flags);
    g_signal_connect(app, "activate", G_CALLBACK(&AdwWin::activate), static_cast<gpointer>(this));
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

NavSplitView* AdwWin::get_split_view()
{
    return split_view.get();
}

ListViewContent* AdwWin::get_siderbar_view()
{
    return siderbar_view.get();
}

void AdwWin::set_siderbar_view(GtkWidget *_parent, string path, NavSplitView * nsplit)
{
    siderbar_view = std::make_shared<ListViewContent>(_parent, path, nsplit);
}