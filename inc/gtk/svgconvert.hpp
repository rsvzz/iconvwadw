#pragma once
#include "incgtk.hpp"
#include <iostream>

extern "C"{
    #include "opt-c/svg_draw.h"
}

using std::string;

class SvgConvert
{
private:
    /* data */
    int width, height;
    SvgDraw *svg;
public:
    /// @brief Get Texture
    /// @param  Width
    /// @param  Height
    SvgConvert(int, int);
    ~SvgConvert();

    GdkTexture *get_texture(const std::string);
    int get_width();
    int get_height();
};