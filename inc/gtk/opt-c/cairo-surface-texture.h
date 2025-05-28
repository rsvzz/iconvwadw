#pragma once
#include <gtk-4.0/gdk/gdk.h>
#include <cairo/cairo.h>

#ifdef __cplusplus
extern "C"
{
#endif

    GdkTexture *create_texture_from_surface(cairo_surface_t *);

#ifdef __cplusplus
}
#endif