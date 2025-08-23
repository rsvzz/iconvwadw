#include "../../inc/gtk/gdataview.hpp"
#include "../../inc/model/readfile.hpp"
#include "../../inc/gtk/svgconvert.hpp"
extern "C"
{
#include "../../inc/gtk/opt-c/svg_draw.h"
#include "../../inc/gtk/opt-c/grid_item.h"
}
#include "../../inc/gtk/imagegestore.hpp"
#include <gtk-4.0/gdk/gdk.h>
#include <filesystem>
#include <iostream>
using std::string;

static void setup_item(GtkListItemFactory *factory, GtkListItem *item, gpointer user_data)
{
    // g_print("setup item \n");
    GtkWidget *picture = gtk_image_new();
    gtk_list_item_set_child(item, picture);
}

static void bind_item(GtkListItemFactory *factory, GtkListItem *item, gpointer user_data)
{

    GridItem *item_g = (GridItem *)gtk_list_item_get_item(item);
    int width = 0, heigth = 0;
    width = grid_item_get_width(item_g);
    heigth = grid_item_get_heigth(item_g);

    GtkWidget *picture = gtk_list_item_get_child(item);
    gtk_widget_set_size_request(picture, width, heigth);

    auto svg_covert = std::make_shared<SvgConvert>(width, heigth);
    auto image = std::make_shared<ImageGestore>(picture, string(grid_item_get_path(item_g)), svg_covert, GTK_WINDOW(grid_item_get_parent(item_g)));

    //gtk_widget_set_hexpand(picture, TRUE);
    //gtk_widget_set_vexpand(picture, TRUE);

    // g_print("path : %s \n", grid_item_get_path(item_g));
    /*
    int width = svg_drag_get_width(svg);
    int heigth = svg_drag_get_height(svg);
    char *path = strdup(grid_item_get_path(item_g));
    //g_print("%s \n", path);
    gtk_widget_set_size_request(picture, width, heigth);
    GdkTexture *texture = svg_draw_get_file_svg_to_draw(svg, path);
    if(texture != nullptr){

    gtk_picture_set_paintable(GTK_PICTURE(picture), GDK_PAINTABLE(texture));
    }
    else{
        g_print("texture es null \n");
    }
   */
    // g_print("bind w= %d, h %d path: %s \n", width, heigth, path);
    //  gtk_widget_set_margin_start(picture, 10);
    //  gtk_widget_set_margin_top(picture, 10);
    //  gtk_widget_set_margin_end(picture, 10);
    //  gtk_widget_set_margin_bottom(picture, 10);
}

GridDataView::GridDataView(string _path, GtkWindow *_parent, int w, int h)
{
    path = _path;
    parent = _parent;
    width = w;
    heigth = h;
    GListStore *list_store = g_list_store_new(GRID_ITEM_TYPE);
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(setup_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_item), NULL);
    /*
    std::unique_ptr<ReadFile> readfile = std::make_unique<ReadFile>();
    std::queue<std::string> content = readfile->getFileList(this->path);
    SvgDraw *svg = svg_draw_new();
    svg_draw_set_draw_width_and_height(svg, 60, 60);

    while (!content.empty())
    {
        std::string file_name = content.front();
        std::filesystem::path filePath(file_name);
        // auto img = std::make_shared<ImageGestore>(filePath.string(), svg, parent);
        GridItem *item_obj = grid_item_new();
        grid_item_set_data(item_obj, GTK_WIDGET(parent), svg, filePath.string().c_str());
        g_list_store_append(list_store, item_obj);
        content.pop();
    }
     */
    grid = gtk_grid_view_new(GTK_SELECTION_MODEL(gtk_no_selection_new(G_LIST_MODEL(list_store))), factory);
    gtk_widget_set_vexpand(grid, TRUE);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_grid_view_set_min_columns(GTK_GRID_VIEW(grid), 4);
    gtk_grid_view_set_max_columns(GTK_GRID_VIEW(grid), 10);
}
GridDataView::~GridDataView()
{
}

void GridDataView::set_image_grid_for_data()
{

    std::unique_ptr<ReadFile> readfile = std::make_unique<ReadFile>();
    std::queue<std::string> content = readfile->getFileList(this->path);
    GtkSelectionModel *selection_model = gtk_grid_view_get_model(GTK_GRID_VIEW(grid));
    GListModel *model = gtk_no_selection_get_model(GTK_NO_SELECTION(selection_model));
    while (!content.empty())
    {
        std::string file_name = content.front();
        std::filesystem::path filePath(file_name);
        GridItem *item_obj = grid_item_new();
        grid_item_set_data(item_obj, GTK_WIDGET(parent), filePath.string().c_str(), width, heigth);
        g_list_store_append(G_LIST_STORE(model), item_obj);
        content.pop();
    }
}

GtkWidget *GridDataView::get_grid() { return grid; }