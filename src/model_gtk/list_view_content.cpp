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

ListViewContent::ListViewContent(GtkWidget *_parent, string _path) : parent(_parent), path(_path)
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
    list_view = gtk_list_view_new(GTK_SELECTION_MODEL(selection), factory);
}

ListViewContent::~ListViewContent()
{
    g_print("ListViewContent ctor ~ \n");
}

GtkWidget *ListViewContent::get_list_view()
{
    return list_view;
}

GtkWidget *ListViewContent::get_parent() { return parent; }

GtkSingleSelection *ListViewContent::get_single_selection()
{
    return GTK_SINGLE_SELECTION(gtk_list_view_get_model(GTK_LIST_VIEW(list_view)));
}
