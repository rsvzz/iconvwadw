#include "../../inc/gtk/opt-c/cairo-surface-texture.h"
/// @brief Create surface for cairo
/// @param surface 
/// @return GdkTexture
GdkTexture *create_texture_from_surface(cairo_surface_t *surface)
{
    int width = cairo_image_surface_get_width(surface);
    int height = cairo_image_surface_get_height(surface);
    cairo_format_t format = cairo_image_surface_get_format(surface);

    if (format != CAIRO_FORMAT_ARGB32 && format != CAIRO_FORMAT_RGB24)
    {
        g_printerr("Formato de superficie no compatible\n");
        return NULL;
    }

    int stride = cairo_format_stride_for_width(format, width);
    unsigned char *data = cairo_image_surface_get_data(surface);

    return gdk_memory_texture_new(width, height, GDK_MEMORY_DEFAULT, g_bytes_new(data, stride * height), stride);
}