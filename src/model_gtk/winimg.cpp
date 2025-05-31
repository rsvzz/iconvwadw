#include "../../inc/gtk/win/winimg.hpp"
#include "../../inc/gtk/svgcv.hpp"
#include <filesystem>

WinImg::WinImg(const std::string path)
{
    // Constructor implementation
    set_title("Icon Name");
    set_default_size(300, 300);
    set_resizable(true);
    set_modal(true);

    Gtk::Box *box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    int width = 180, height = 180;
    auto svg = std::make_unique<SvgCv>(width, height);
    auto image = Gtk::make_managed<Gtk::Image>();
    image->set(svg->get_texture(path));
    image->set_margin(7);
    image->set_size_request(width, height);
    box->append(*image);

    std::filesystem::path filePath(path.c_str());
    this->file_name = filePath.stem().string().c_str();

    auto label = Gtk::make_managed<Gtk::Label>(this->file_name);
    auto btn_copy = Gtk::make_managed<Gtk::Button>();
    btn_copy->set_icon_name("edit-copy-symbolic");
    btn_copy->signal_clicked().connect(sigc::mem_fun(*this, &WinImg::on_copy_clicked));

    Gtk::Box *box_icon_name = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    box_icon_name->set_halign(Gtk::Align::CENTER);
    box_icon_name->append(*label);
    box_icon_name->append(*btn_copy);

    box->append(*box_icon_name);
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