#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>
#include "svg_draw.h"

#define GRID_ITEM_TYPE grid_item_get_type()

G_DECLARE_FINAL_TYPE (GridItem, grid_item, GRID, ITEM, GObject);

GridItem *grid_item_new(void);

/// @brief set data
/// @param  self 
/// @param  GtkWidget* parent
/// @param  SvgDraw gobject
/// @param  Path const char*
void grid_item_set_data(GridItem*, GtkWidget*, SvgDraw*, const char*);
/// @brief widget GtkPinture
/// @param  self
/// @return GtkWidget
GtkWidget *grid_item_get_item(GridItem *);
GtkWidget *grid_item_get_parent(GridItem *);
SvgDraw *grid_item_get_obj_draw(GridItem*);
char *grid_item_get_path(GridItem *);

