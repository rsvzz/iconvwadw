#include "../../inc/gtk/opt-c/rsvg-path.h"
#include <librsvg-2.0/librsvg/rsvg.h>

cairo_surface_t* create_surface_for_file_svg(const char* path, int width, int height){
    GError *error = NULL;
    RsvgHandle *handle = rsvg_handle_new_from_file(path, &error);
  
   RsvgRectangle viewport = { .x = 0.0, .y = 0.0, .width = width, .height = height };
   cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
   cairo_t *cr = cairo_create(surface);

   rsvg_handle_render_document(handle, cr, &viewport, &error);
   return surface;
}