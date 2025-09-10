#include "../../inc/gtk/list_view_content.hpp"
#include "../../inc/model/readdir.hpp"
#include "../../inc/model/readfile.hpp"
#include "../../inc/gtk/gdataview.hpp"
extern "C"
{
#include "../../inc/gtk/opt-c/list_item.h"
}

#include <filesystem>

static gint compare_list_item(gconstpointer a, gconstpointer b, gpointer user_data)
{
    GObject *obj_a = G_OBJECT(a);
    GObject *obj_b = G_OBJECT(b);

    const gchar *name_a = NULL;
    const gchar *name_b = NULL;

    g_object_get(obj_a, "name", &name_a, NULL);
    g_object_get(obj_b, "name", &name_b, NULL);

    gint result = g_strcmp0(name_a, name_b);

    g_free((gchar *)name_a);
    g_free((gchar *)name_b);

    return result;
}

void ListViewContent::on_selection_changed(GObject *object, GParamSpec *pspec, gpointer user_data)
{
    GtkSingleSelection *selection = GTK_SINGLE_SELECTION(object);
    // guint selected = gtk_single_selection_get_selected(selection);
    ListItem *item = (ListItem *)gtk_single_selection_get_selected_item(selection);
    auto content = static_cast<ListViewContent *>(user_data);
    if (content != nullptr)
    {
        auto grid = std::make_shared<GridDataView>(list_item_get_path(item), GTK_WINDOW(content->get_parent()), 60, 60);
        grid->set_image_grid_for_data();
        ToolView *c_view =  content->get_nav()->get_content_view();

        if( c_view !=  nullptr) //g_print("c_view is not null \n");
             c_view->set_view_content(grid->get_grid());
        //else
            
        /*
        GtkSelectionModel *model = gtk_grid_view_get_model(GTK_GRID_VIEW(gcontent));
        GListModel *mlist = gtk_no_selection_get_model(GTK_NO_SELECTION(model));
        g_print("count : %d \n", g_list_model_get_n_items(mlist));
        */
        // content->get_nav()->set_content_view(grid->get_grid());
        // g_print("Item seleccionado: %u %s \n", selected, list_item_get_path(item));
    }
}

static void setup_item(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *image = gtk_image_new_from_icon_name("go-next-symbolic");
    GtkWidget *label = gtk_label_new(NULL);

    gtk_widget_set_margin_top(box, 10);
    gtk_widget_set_margin_bottom(box, 10);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);

    gtk_widget_set_margin_start(label, 20);
    gtk_widget_set_margin_end(image, 5);

    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), spacer);
    gtk_box_append(GTK_BOX(box), image);
    gtk_list_item_set_child(list_item, box);
}

static void bind_item(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *box = gtk_list_item_get_child(list_item);
    ListItem *my_item = LIST_ITEM(gtk_list_item_get_item(list_item));
    GtkWidget *label = gtk_widget_get_first_child(box);
    // GtkWidget *image = gtk_widget_get_next_sibling(label);
    gtk_label_set_text(GTK_LABEL(label), list_item_get_name(my_item));
}

ListViewContent::ListViewContent(GtkWidget *_parent, string _path, NavSplitView *_nav) : parent(_parent), path(_path), nav(_nav)
{
    file_item = std::make_shared<FileItem>(GTK_WINDOW(_parent));
    GListStore *list_store = g_list_store_new(LIST_ITEM_TYPE);

    std::unique_ptr<ReadDir> dir = std::make_unique<ReadDir>(_path);
    std::queue<string> qdir = dir->getDirList();

    while (!qdir.empty())
    {
        string dir_name = qdir.front();
        std::filesystem::path dirPath(dir_name);
        ListItem *item = list_item_new();
        list_item_set_data(item, dirPath.c_str(), dirPath.filename().c_str(), parent);
        g_list_store_append(list_store, item);

        qdir.pop();
    }

    g_list_store_sort(list_store, compare_list_item, NULL);

    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(setup_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_item), NULL);

    GtkSingleSelection *selection = gtk_single_selection_new(G_LIST_MODEL(list_store));
    g_signal_connect(selection, "notify::selected", G_CALLBACK(&ListViewContent::on_selection_changed), static_cast<gpointer>(this));

    list_view = gtk_list_view_new(GTK_SELECTION_MODEL(selection), factory);
    
    gtk_single_selection_set_selected(selection, 1);
   
}

ListViewContent::~ListViewContent()
{
    g_print("ListViewContent ctor ~ \n");
}

GtkWidget *ListViewContent::get_list_view()
{
    return list_view;
}

NavSplitView *ListViewContent::get_nav()
{
    return nav;
}

GtkWidget *ListViewContent::get_parent() { return parent; }
