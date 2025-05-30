#include "../../inc/gtk/imgevt.hpp"
#include <gtkmm-4.0/gdkmm.h>
#include <gtkmm-4.0/gdkmm/texture.h>
#include <gtkmm-4.0/gtkmm/gestureclick.h>
#include <sigc++-3.0/sigc++/sigc++.h>
#include "../../inc/gtk/win/winimg.hpp" //event click
#include "../../inc/gtk/svgcv.hpp"

ImgEvt::ImgEvt(const std::string path, std::shared_ptr<SvgCv> svg)
{
    // Constructor implementation
    this->path = path;
    this->set_size_request(svg->get_width(), svg->get_height());
    this->set(svg->get_texture(path));
    this->set_margin(10);

    auto gesture = Gtk::GestureClick::create();
    gesture->signal_pressed().connect(sigc::mem_fun(*this, &ImgEvt::on_click_gestore));
    gesture->set_button(GDK_BUTTON_PRIMARY);
    this->add_controller(gesture);

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