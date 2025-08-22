#include "../../inc/gtk/opt-c/grid_item.h"
#include <stdlib.h>
struct _GridItem
{
    /* data */
    GObject parent_instance;
    char *path;
    GtkWidget *image, *parent;
    SvgDraw *draw;
};

G_DEFINE_TYPE (GridItem, grid_item, G_TYPE_OBJECT);

static void grid_item_dispose(GObject *object)
{
    GridItem *self = GRID_ITEM(object);

    if (self->path != NULL)
    {
        g_free(self->path);
        self->path = NULL;
    }

    G_OBJECT_CLASS(grid_item_parent_class)->dispose(object);
    g_print("dispose grid_item \n");
}

static void grid_item_finalize(GObject *object)
{
    G_OBJECT_CLASS(grid_item_parent_class)->finalize(object);
}

static void grid_item_class_init(GridItemClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = grid_item_dispose;

    // Asignar la función de finalización
    object_class->finalize = grid_item_finalize;
};

static void grid_item_init(GridItem *self)
{
    
};

GridItem* grid_item_new(void){
    return g_object_new(GRID_ITEM_TYPE, NULL);
}

void grid_item_set_data(GridItem *self,GtkWidget* _parent, SvgDraw *_draw, const char* _path){
    self->path = g_strdup(_path); //free dispose
    //strcpy(self->path, _path);
    self->parent = _parent;
    self->draw = _draw;
    self->image = gtk_image_new();
}

GtkWidget *grid_item_get_item(GridItem *self){return self->image;}

GtkWidget *grid_item_get_parent(GridItem *self){
   return self->parent;
}

SvgDraw *grid_item_get_obj_draw(GridItem *self){
    return self->draw;
}

char *grid_item_get_path(GridItem *self){
    //g_print("item path -> %s \n", self->path);
    return self->path;
}

