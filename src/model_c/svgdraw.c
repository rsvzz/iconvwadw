#include "../../inc/gtk/opt-c/svg_draw.h"
#include <librsvg-2.0/librsvg/rsvg.h> //here .c in .h
#include <cairo/cairo.h>              //here .c

//^ .h no se incluye las lib porque .o sera enlazado si se agregan .h las lib no las encuentra en C++

/// @brief Draw .Svg GObject
struct _SvgDraw
{
    /* data */
    GObject parent_instance;
    int w, h;
    GdkTexture *texture;
};

G_DEFINE_TYPE(SvgDraw, svg_draw, G_TYPE_OBJECT);

cairo_surface_t *create_surface_for_file_svg(const char *path, int width, int height);
GdkTexture *create_texture_from_surface(cairo_surface_t *);

static void svg_draw_dispose(GObject *object)
{
    SvgDraw *self = SVG_DRAW(object);
    /*
    if (self->box != NULL)
    {
        g_object_unref(self->box);
        self->box = NULL;
    }

    if (self->siderbar != NULL)
    {
        g_object_unref(self->siderbar);
        self->siderbar = NULL;
    }

    if (self->stack != NULL)
    {
        g_object_unref(self->stack);
        self->stack = NULL;
    }
        */

    G_OBJECT_CLASS(svg_draw_parent_class)->dispose(object);
    g_print("svg_dra item dispose\n");
}

static void svg_draw_finalize(GObject *object)
{
    G_OBJECT_CLASS(svg_draw_parent_class)->finalize(object);
}

static void svg_draw_class_init(SvgDrawClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = svg_draw_dispose;

    // Asignar la función de finalización
    object_class->finalize = svg_draw_finalize;
};

static void svg_draw_init(SvgDraw *self)
{
    self->h = 32;
    self->w = 32;
    self->texture = NULL;
};

SvgDraw *svg_draw_new(void)
{
    return g_object_new(SVG_DRAW_TYPE, NULL);
}

void svg_draw_set_draw_width_and_height(SvgDraw *self, int w, int h)
{
    self->h = h;
    self->w = w;
}

GdkTexture *svg_draw_get_file_svg_to_draw(SvgDraw *self, const char *path)
{
    cairo_surface_t *surface = create_surface_for_file_svg(path, self->w, self->h);
    /*
    if(self->texture != NULL){
        g_object_unref(self->texture);
        self->texture = NULL;
    }

    */
    self->texture = create_texture_from_surface(surface);
    // g_object_unref(surface);
    // surface = NULL;

    return self->texture;
}

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

    GdkTexture *texture = gdk_memory_texture_new(width, height, GDK_MEMORY_DEFAULT, g_bytes_new(data, stride * height), stride);

    free(data);
    data = NULL;

    return texture;
}

cairo_surface_t *create_surface_for_file_svg(const char *path, int width, int height)
{
    GError *error = NULL;
    RsvgHandle *handle = rsvg_handle_new_from_file(path, &error);
    if (error)
    {
        g_error_free(error);
        return NULL;
    }

    RsvgRectangle viewport = {.x = 0.0, .y = 0.0, .width = width, .height = height};

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create(surface);
    // cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    // cairo_paint(cr);

    rsvg_handle_render_document(handle, cr, &viewport, &error);
    g_object_unref(handle);
    handle = NULL;

    if (error)
    {
        g_error_free(error);
        return NULL;
    }

    cairo_destroy(cr);
    return surface;
}

int svg_drag_get_width(SvgDraw *self)
{
    return self->w;
}

int svg_drag_get_height(SvgDraw *self){
    return self->h;
}
