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

NavContent::NavContent(GtkWidget *_win, string _path) : parent(_win), path(_path)
{
    nav = std::make_shared<NavSplitView>("Icon Browser Adw", "");
    content = std::make_shared<ListViewContent>(parent, path);
    auto selection = content->get_single_selection();
    g_signal_connect(selection, "notify::selected", G_CALLBACK(&NavContent::on_selection_changed), static_cast<gpointer>(this));
}

NavContent::~NavContent()
{
    g_print("~NavContent \n");
}

std::shared_ptr<NavSplitView> NavContent::get_nav()
{
    return nav;
}

std::shared_ptr<ListViewContent> NavContent::get_list_view_content(){
    return content;
}

GtkWindow* NavContent::get_parent(){
    return GTK_WINDOW(parent);
}

void NavContent::load_siderbar(){
    nav->set_siderbar_view(content->get_list_view());
}

void NavContent::set_content(GtkWidget* widget){
    nav->set_content_view(widget);
}