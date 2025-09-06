#include "../../inc/gtk/opt-c/list_view.h"


struct _ListItem
{
    /* data */
    GObject parent_instance;
    char *path, *name;
    GtkWidget *parent;
};

G_DEFINE_TYPE (ListItem, list_item, G_TYPE_OBJECT);

static void list_item_dispose(GObject *object)
{
    ListItem *self = LIST_ITEM(object);

    if (self->path != NULL)
    {
        g_free(self->path);
        self->path = NULL;
    }
    if (self->name != NULL)
    {
        g_free(self->name);
        self->path = NULL;
    }

    G_OBJECT_CLASS(list_item_parent_class)->dispose(object);
}

static void list_item_finalize(GObject *object)
{
    G_OBJECT_CLASS(list_item_parent_class)->finalize(object);
}

static void list_item_class_init(ListItemClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = list_item_dispose;

    // Asignar la función de finalización
    object_class->finalize = list_item_finalize;
};

static void list_item_init(ListItem *self)
{
    
};

ListItem* list_item_new(void){
    return g_object_new(LIST_ITEM_TYPE, NULL);
}

void list_item_set_data(ListItem *self, const char* path, const char* name, GtkWidget* parent){
    self->name = g_strdup(name);
    self->path = g_strdup(path);
    self->parent = parent;
}

const char* list_item_get_name(ListItem * self){
    return self->name;
}

const char* list_item_get_path(ListItem * self){
    return self->path;
}

GtkWidget* list_item_get_parent(ListItem *self){
    return self->parent;
}