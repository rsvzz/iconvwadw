#include "../../inc/gtk/svgcv.hpp"
#include <gtkmm-4.0/gdkmm.h>
#include <gtkmm-4.0/gdkmm/texture.h>

SvgCv::SvgCv(int width, int height){
    this->width = width;
    this->height = height;
}

SvgCv::~SvgCv(){

}

Glib::RefPtr<Gdk::Texture> SvgCv::get_texture(const std::string path){
    cairo_surface_t *surface = create_surface_for_file_svg(path.c_str(), this->width, this->height);
    GdkTexture *texture = create_texture_from_surface(surface);
    return Glib::wrap(texture, true);
}

int SvgCv::get_width(){ return this->width;}
int SvgCv::get_height(){ return this->height;}