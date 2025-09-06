#pragma once
#include <glib-2.0/glib-object.h>
#include <gtk-4.0/gtk/gtk.h>

#define LIST_ITEM_TYPE list_item_get_type()

G_DECLARE_FINAL_TYPE (ListItem, list_item, LIST, ITEM, GObject);

ListItem *list_item_new(void);
/// @brief Set info
/// @param  ListItem
/// @param  char* path
/// @param  char* name
/// @param  GtkWidget* parent
void list_item_set_data(ListItem *, const char*, const char*, GtkWidget*);

const char* list_item_get_name(ListItem *);
const char* list_item_get_path(ListItem *);
GtkWidget* list_item_get_parent(ListItem *);