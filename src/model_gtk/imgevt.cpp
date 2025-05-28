#include "../../inc/gtk/imgevt.hpp"
#include <gtkmm-4.0/gdkmm.h>
#include <gtkmm-4.0/gdkmm/texture.h>
#include "../../inc/gtk/win/winimg.hpp"
#include "../../inc/gtk/opt-c/cairo-surface-texture.h"
#include "../../inc/gtk/opt-c/rsvg-path.h"

ImgEvt::ImgEvt(const std::string path)
{
    // Constructor implementation
    this->path = path;
    this->set_size_request(60, 60);
    cairo_surface_t* surface = create_surface_for_file_svg(path.c_str(), 60, 60);
    GdkTexture *texture = create_texture_from_surface(surface);
    auto cpptexture = Glib::wrap(texture, true);

    auto gesture = Gtk::GestureClick::create();
    gesture->signal_pressed().connect(sigc::mem_fun(*this, &ImgEvt::on_click_gestore));
    gesture->set_button(GDK_BUTTON_PRIMARY);
    this->add_controller(gesture);
    this->set(cpptexture);
    this->set_margin(10);
    this->set_size_request(60, 60);
    //this->set(pixbuf);
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