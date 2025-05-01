#include "../../inc/gtk/imgevt.hpp"
#include <gtkmm-4.0/gdkmm.h>
#include <gtkmm-4.0/gdkmm/pixbuf.h>
#include "../../inc/gtk/win/winimg.hpp"

ImgEvt::ImgEvt(std::string path)
{
    // Constructor implementation
    auto pixbuf = Gdk::Pixbuf::create_from_file(path, 60, 60);
    this->path = path;
    auto gesture = Gtk::GestureClick::create();
    gesture->signal_pressed().connect(sigc::mem_fun(*this, &ImgEvt::on_click_gestore));
    gesture->set_button(GDK_BUTTON_PRIMARY);
    this->add_controller(gesture);
    this->set(pixbuf);
    this->set_margin(10);
    this->set_size_request(60, 60);
    this->set(pixbuf);
}

ImgEvt::~ImgEvt()
{
    // Destructor implementation
}

void ImgEvt::on_click_gestore(int n_press, double x, double y)
{
    // Handle click event
    auto win = Gtk::make_managed<WinImg>(this->path);
    win->show();
}