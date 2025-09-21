#include "../../inc/gtk/nav_content.hpp"
#include "../../inc/gtk/gdataview.hpp"

extern "C"
{
#include "../../inc/gtk/opt-c/list_item.h"
}

void NavContent::on_selection_changed(GObject *object, GParamSpec *pspec, gpointer user_data)
{
    GtkSingleSelection *selection = GTK_SINGLE_SELECTION(object);
    // guint selected = gtk_single_selection_get_selected(selection);
    ListItem *item = (ListItem *)gtk_single_selection_get_selected_item(selection);
    auto content = static_cast<NavContent *>(user_data);
    if (content != nullptr)
    {
        auto grid = std::make_shared<GridDataView>(list_item_get_path(item), content->get_parent(), 60, 60);
        grid->set_image_grid_for_data();
        if (grid != nullptr)
        {
            content->set_content(grid->get_grid());          
        }
    }
}

NavContent::NavContent(GtkWidget *_win, string& _path) :
    NavSplitView("Icon Browser Adw", "", _win), ListViewContent(_win, _path), parent(_win), path(_path)
{   
    auto selection = get_single_selection();
    g_signal_connect(selection, "notify::selected", G_CALLBACK(&NavContent::on_selection_changed), static_cast<gpointer>(this));
    gtk_single_selection_set_selected(selection, 1);
}

NavContent::~NavContent()
{
    //g_print("~NavContent \n");
}


GtkWindow* NavContent::get_parent(){
    return GTK_WINDOW(parent);
}

void NavContent::load_siderbar(){
    set_siderbar_view(get_list_view());
}

void NavContent::set_content(GtkWidget* widget){
    set_content_view(widget);
}