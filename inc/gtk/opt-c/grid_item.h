#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>
#include "svg_draw.h"

#define GRID_ITEM_TYPE grid_item_get_type()

G_DECLARE_FINAL_TYPE (GridItem, grid_item, GRID, ITEM, GObject);

GridItem *grid_item_new(void);

/// @brief Set data for item
/// @param self 
/// @param GtkWidget* parent for GtkWindow main
/// @param Char* Path
/// @param int width
/// @param int height
void grid_item_set_data(GridItem*, GtkWidget*, const char*, int, int);
/// @brief GtkWidget parent
/// @param  self
/// @return GtkWidget
GtkWidget *grid_item_get_parent(GridItem *);
/// @brief Path item
/// @param  self
/// @return Path const char*
const char *grid_item_get_path(GridItem *);

int grid_item_get_width(GridItem*);
int grid_item_get_heigth(GridItem*);

