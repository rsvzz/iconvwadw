#include "../../inc/gtk/win/win_image_view.hpp"
#include "../../inc/gtk/svgconvert.hpp"
#include <iostream>
#include <filesystem>

extern "C"
{
#include <libadwaita-1/adwaita.h>
}

struct WinClose
{
    /* data */
    GtkWindow *window;
    string file;
};

WinImageView::WinImageView(const std::string path, GtkWindow *parent)
{

    win = adw_application_window_new(gtk_window_get_application(parent));
    gtk_window_set_modal(GTK_WINDOW(win), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(win), parent);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);



    GtkWidget *toolbar_view = adw_toolbar_view_new();
    GtkWidget *header = adw_header_bar_new();
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Icon Name"));
    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);
    gtk_window_set_default_size(GTK_WINDOW(win), 300, 300);
    adw_application_window_set_content(ADW_APPLICATION_WINDOW(win), GTK_WIDGET(toolbar_view)); // Content window


    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    int width = 180, height = 180;

    auto svg = std::make_shared<SvgConvert>(width, height);
    auto image = gtk_image_new();
    gtk_image_set_from_paintable(GTK_IMAGE(image), GDK_PAINTABLE(svg->get_texture(path)));
    gtk_widget_set_margin_start(image, 7);
    gtk_widget_set_margin_top(image, 7);
    gtk_widget_set_margin_end(image, 7);
    gtk_widget_set_margin_bottom(image, 7);

    gtk_widget_set_size_request(image, width, height);
    gtk_box_append(GTK_BOX(box), image);

    std::filesystem::path filePath(path.c_str());
    file_name = filePath.stem().string();

    auto label = gtk_label_new(file_name.c_str());
    auto btn_copy = gtk_button_new();
    gtk_button_set_icon_name(GTK_BUTTON(btn_copy), "edit-copy-symbolic");
    WinClose *obj = new WinClose{GTK_WINDOW(win), file_name};
    g_signal_connect(btn_copy, "clicked", G_CALLBACK(&WinImageView::on_copy_clicked), (gpointer)obj);

    GtkWidget *box_in = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_halign(box_in, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(box_in), label);
    gtk_box_append(GTK_BOX(box_in), btn_copy);

    gtk_box_append(GTK_BOX(box), box_in);

    adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), box);

}

WinImageView::~WinImageView()
{
    // Destructor implementation
}

void WinImageView::on_copy_clicked(GtkWidget *btn, gpointer data)
{
    // Copy button clicked implementation

    WinClose *win = (WinClose *)(data);
    auto display = gdk_display_get_default();
    auto clipboard = gdk_display_get_clipboard(display);
    gdk_clipboard_set_text(clipboard, win->file.c_str());
    gtk_window_close(win->window);
}

GtkWidget *WinImageView::get_window()
{
    return win;
}

void WinImageView::show()
{
    gtk_window_present(GTK_WINDOW(win));
}

string WinImageView::get_file_name()
{
    return file_name;
}