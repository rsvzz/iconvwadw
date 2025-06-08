#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gdkmm.h>

extern "C"{
    #include "opt-c/svg_draw.h"
}

class SvgCv
{
private:
    /* data */
    int width, height;
    SvgDraw *svg;
public:
    /// @brief Get Texture
    /// @param  Width
    /// @param  Height
    SvgCv(int, int);
    ~SvgCv();

    Glib::RefPtr<Gdk::Texture> get_texture(const std::string);
    int get_width();
    int get_height();
};

