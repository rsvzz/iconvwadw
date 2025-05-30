#pragma once
#include <cairo/cairo.h>
/// @brief Write svg in surfece cairo
/// @param  Path file
/// @param  int Width
/// @param  int Height
/// @return cairo_surface_t* map svg
cairo_surface_t *create_surface_for_file_svg(const char *, int, int);
