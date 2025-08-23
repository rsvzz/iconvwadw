#include "../../inc/gtk/boxbody.hpp"
#include "../../inc/gtk/gdataview.hpp"
#include <thread>
#include <memory>

BoxBody::BoxBody(const string & _path, GtkWindow* _parent) : path(_path), parent(_parent)
{
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    scrollw = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(scrollw, TRUE);
    gtk_widget_set_vexpand(scrollw, TRUE);
    gtk_box_append(GTK_BOX(box), scrollw);
}

BoxBody::~BoxBody()
{
}

void BoxBody::create_grid(){

    if (gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrollw)) == NULL)
    {
        auto grid = std::make_shared<GridDataView>(this->path, parent, 60, 60);
        //grid->set_image_grid_for_data();
        
        //gtk_widget_set_halign(grid->get_grid(), GTK_ALIGN_CENTER);

        std::thread t1(&GridDataView::set_image_grid_for_data, grid);
        t1.join();

        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollw), grid->get_grid());
    }
}

GtkWidget *BoxBody::get_box(){return box;}