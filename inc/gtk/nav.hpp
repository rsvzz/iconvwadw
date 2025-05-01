#pragma once
#include <iostream>
#include <gtkmm-4.0/gtkmm/stack.h>
#include <gtkmm-4.0/gtkmm/stacksidebar.h>
#include <gtkmm-4.0/gtkmm/widget.h>

class Nav : public Gtk::StackSidebar
{
private:
    /* data */
    Gtk::Stack *stack;
public:
    Nav();
    ~Nav();
    /// @brief add item stack
    /// @param widget
    /// @param  name id
    /// @param  title slidebar name
    /// @return void
    /// @note  add_item(Gtk::Widget *widget, const std::string &name, const std::string &title);
    void add_item(Gtk::Widget *widget, const std::string &, const std::string &);
};
