#include "../../inc/gtk/navbox.hpp"


NavBox::NavBox(/* args */)
{

    sbar = gtk_stack_sidebar_new();
    stack =  gtk_stack_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sbar), GTK_STACK(stack));

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_box_append(GTK_BOX(box), sbar);
    gtk_box_append(GTK_BOX(box), stack);

}

NavBox::~NavBox()
{
}

void NavBox::add(GtkWidget *item, string name, string title){
    gtk_stack_add_titled(GTK_STACK(stack), item, name.c_str(), title.c_str());
}

GtkWidget* NavBox::get_box(){
    return box;
}