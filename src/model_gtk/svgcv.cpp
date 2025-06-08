#include "../../inc/gtk/svgcv.hpp"
#include <gtkmm-4.0/gdkmm.h>
#include <gtkmm-4.0/gdkmm/texture.h>

SvgCv::SvgCv(int width, int height){
    this->width = width;
    this->height = height;
    this->svg = svg_draw_new();
    svg_draw_set_draw_width_and_height(this->svg , this->width, this->height);
}

SvgCv::~SvgCv(){
    //default 32 x 32
    this->svg = svg_draw_new();
}

Glib::RefPtr<Gdk::Texture> SvgCv::get_texture(const std::string path){
    
    GdkTexture *texture = svg_draw_get_file_svg_to_draw(this->svg, path.c_str());
    return Glib::wrap(texture, true);
}

int SvgCv::get_width(){ return this->width;}
int SvgCv::get_height(){ return this->height;}