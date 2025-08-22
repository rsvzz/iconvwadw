#pragma once
#include <glib-2.0/glib-object.h>
#include <gtk-4.0/gtk/gtk.h>
#include <gtk-4.0/gdk/gdk.h>

#define SVG_DRAW_TYPE svg_draw_get_type()

G_DECLARE_FINAL_TYPE (SvgDraw, svg_draw, SVG, DRAW, GObject);

SvgDraw *svg_draw_new(void);
/// @brief set width and height for drawing
/// @param self 
/// @param w 
/// @param h 
void svg_draw_set_draw_width_and_height(SvgDraw *self, int w, int h);
/// @brief get it svg draw witd cairo
/// @param self 
/// @param  path
/// @return GdkTexture texture draw
GdkTexture *svg_draw_get_file_svg_to_draw(SvgDraw *self, const char*);
int svg_drag_get_width(SvgDraw* self);
int svg_drag_get_height(SvgDraw* self);