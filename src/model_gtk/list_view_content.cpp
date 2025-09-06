#include "../../inc/gtk/list_view_content.hpp"
#include "../../inc/model/readdir.hpp"
#include "../../inc/model/readfile.hpp"

extern "C"
{
    #include "../../inc/gtk/opt-c/list_view.h"
}

#include <filesystem>

static void setup_item(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *label = gtk_label_new(NULL);
    gtk_list_item_set_child(list_item, label);
}

static void bind_item(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *label = gtk_list_item_get_child(list_item);
    ListItem *my_item = LIST_ITEM(gtk_list_item_get_item(list_item));
    gtk_label_set_text(GTK_LABEL(label), list_item_get_name(my_item));
}

ListViewContent::ListViewContent(GtkWidget *_parent, string _path) : parent(_parent), path(_path)
{
    file_item = std::make_shared<FileItem>(GTK_WINDOW(_parent));
    GListStore *list_store = g_list_store_new(LIST_ITEM_TYPE);

    std::unique_ptr<ReadDir> dir = std::make_unique<ReadDir>(_path);
    std::queue<string> qdir = dir->getDirList();
    g_print("llega1 \n");
    while (!qdir.empty())
    {
        string dir_name = qdir.front();
        std::filesystem::path dirPath(dir_name);
        ListItem *item = list_item_new();
        list_item_set_data(item, dirPath.filename().c_str(), dirPath.filename().c_str(), parent);
        g_list_store_append(list_store, item);
        qdir.pop();
    }
    g_print("pasa \n");

    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    g_signal_connect(factory, "setup", G_CALLBACK(setup_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_item), NULL);

    list_view = gtk_list_view_new(GTK_SELECTION_MODEL(gtk_single_selection_new(G_LIST_MODEL(list_store))), factory);
}

ListViewContent::~ListViewContent()
{
}

GtkWidget *ListViewContent::get_list_view()
{
    return list_view;
}
