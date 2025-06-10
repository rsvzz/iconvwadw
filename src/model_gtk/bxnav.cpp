#include "../../inc/gtk/bxnav.hpp"
#include "../../inc/gtk/bxbody.hpp"
#include <iostream>

BxNav::BxNav() : Gtk::Box(Gtk::Orientation::HORIZONTAL, 0)
{
    // Constructor implementation
    sidebar = Gtk::make_managed<Gtk::StackSidebar>();
    stack = Gtk::make_managed<Gtk::Stack>();
    sidebar->set_stack(*stack);
    stack->property_visible_child().signal_changed().connect(sigc::mem_fun(*this, &BxNav::on_stack_changed));
    this->append(*sidebar);
    this->append(*stack);
}

BxNav::~BxNav()
{
    // Destructor implementation
}

void BxNav::add_item(Gtk::Widget *widget, const std::string &name, const std::string &title)
{
    // Add a new stack to the sidebar with a widget
    stack->add(*widget, name, title);
}

void BxNav::on_stack_changed()
{
    auto visible_child = stack->get_visible_child();
    BxBody* box = dynamic_cast<BxBody*>(visible_child);
    box->create_grid();
}