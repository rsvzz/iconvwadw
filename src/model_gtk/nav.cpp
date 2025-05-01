#include "../../inc/gtk/nav.hpp"

Nav::Nav()
{
    // Constructor implementation
    stack = Gtk::make_managed<Gtk::Stack>();
    this->set_stack(*stack);
}
Nav::~Nav()
{
    // Destructor implementation
    delete stack;
}

void Nav::add_item(Gtk::Widget *widget, const std::string &name, const std::string &title)
{
    // Add a new stack to the sidebar with a widget
    stack->add(*widget, name, title);
}