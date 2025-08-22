#include "../../inc/gtk/svgconvert.hpp"

SvgConvert::SvgConvert(int width, int height){
    this->width = width;
    this->height = height;
    this->svg = svg_draw_new();
    svg_draw_set_draw_width_and_height(this->svg , this->width, this->height);
}

SvgConvert::~SvgConvert(){
    //default 32 x 32
    this->svg = svg_draw_new();
}

GdkTexture *SvgConvert::get_texture(const std::string path){
    GdkTexture *texture = svg_draw_get_file_svg_to_draw(this->svg, path.c_str());
    return texture;
}

int SvgConvert::get_width(){ return this->width;}
int SvgConvert::get_height(){ return this->height;}