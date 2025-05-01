#include "../../inc/gtk/win/winimg.hpp"
#include <filesystem>

WinImg::WinImg(std::string path)
{
    // Constructor implementation
    set_title("Image Window");
    set_default_size(300, 300);
    set_resizable(true);
    set_modal(true);

    std::filesystem::path filePath(path);

    Gtk::Box* box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    auto pixbuf = Gdk::Pixbuf::create_from_file(path, 100, 100);
    auto image = Gtk::make_managed<Gtk::Image>(pixbuf);
    image->set_margin(7);
    image->set_size_request(100, 100);
    box->append(*image);
    this->file_name = filePath.stem().string().c_str();
    auto label = Gtk::make_managed<Gtk::Label>(file_name);
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