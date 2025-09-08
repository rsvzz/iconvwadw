#include "../../inc/gtk/opt-c/list_item.h"

struct _ListItem
{
    /* data */
    GObject parent_instance;
    char *path, *name;
    GtkWidget *parent;
};

enum
{
    PROP_0,
    PROP_NAME,
    N_PROPERTIES
};

G_DEFINE_TYPE(ListItem, list_item, G_TYPE_OBJECT);

static GParamSpec *list_item_properties[N_PROPERTIES];

static void list_item_set_property(GObject *object, guint property_id,
                                const GValue *value, GParamSpec *pspec)
{
    ListItem *self = (ListItem *)object;

    switch (property_id)
    {
    case PROP_NAME:
        g_free(self->name);
        self->name = g_value_dup_string(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}


static void list_item_get_property(GObject *object, guint property_id,
                                GValue *value, GParamSpec *pspec)
{
  ListItem *self = (ListItem *)object;

  switch (property_id)
  {
  case PROP_NAME:
    g_value_set_string(value, self->name);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
  }
}

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
     object_class->set_property = list_item_set_property;
    object_class->get_property = list_item_get_property;

    // Asignar la función de destrucción
    object_class->dispose = list_item_dispose;

    // Asignar la función de finalización
    object_class->finalize = list_item_finalize;

    list_item_properties[PROP_NAME] = g_param_spec_string(
      "name", "Name", "First name of the List Item",
      NULL, G_PARAM_READWRITE);
  g_object_class_install_properties(object_class, N_PROPERTIES, list_item_properties);

};

static void list_item_init(ListItem *self) {
};

ListItem *list_item_new(void)
{
    return g_object_new(LIST_ITEM_TYPE, NULL);
}

void list_item_set_data(ListItem *self, const char *path, const char *name, GtkWidget *parent)
{
    self->name = g_strdup(name);
    self->path = g_strdup(path);
    self->parent = parent;
}

const char *list_item_get_name(ListItem *self)
{
    return self->name;
}

const char *list_item_get_path(ListItem *self)
{
    return self->path;
}

GtkWidget *list_item_get_parent(ListItem *self)
{
    return self->parent;
}