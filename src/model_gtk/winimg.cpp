#include "../../inc/gtk/win/winimg.hpp"
#include "../../inc/gtk/opt-c/cairo-surface-texture.h"
#include "../../inc/gtk/opt-c/rsvg-path.h"
#include <filesystem>

WinImg::WinImg(std::string path)
{
    // Constructor implementation
    set_title("Image View for Name");
    set_default_size(300, 300);
    set_resizable(true);
    set_modal(true);

    

    Gtk::Box* box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);

    int width = 100, height = 100;
    cairo_surface_t* surface = create_surface_for_file_svg(path.c_str(), width, height);
    GdkTexture *texture = create_texture_from_surface(surface);
    auto cpptexture = Glib::wrap(texture, true);

    auto image = Gtk::make_managed<Gtk::Image>(cpptexture);
    image->set_margin(7);
    image->set_size_request(width, height);
    box->append(*image);
    std::filesystem::path filePath(path);
    this->file_name = filePath.stem().string().c_str();
    auto label = Gtk::make_managed<Gtk::Label>(this->file_name);
    box->append(*label);
    auto btn_copy = Gtk::make_managed<Gtk::Button>();
    btn_copy->set_icon_name("edit-copy-symbolic");
    btn_copy->signal_clicked().connect(sigc::mem_fun(*this, &WinImg::on_copy_clicked));
    box->append(*btn_copy);
    set_child(*box);
}
WinImg::~WinImg()
{
    // Destructor implementation
}

void WinImg::on_copy_clicked()
{
    // Copy button clicked implementation
    auto display = Gdk::Display::get_default();
    auto clipboard = display->get_clipboard();
    clipboard->set_text(this->file_name);
    this->close();
}