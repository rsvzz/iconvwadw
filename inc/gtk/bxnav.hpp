#pragma once
#include <gtkmm-4.0/gtkmm.h>
/// @brief Box main Sidebar
class BxNav : public Gtk::Box
{
private:
    /* data */
    Gtk::StackSidebar *sidebar;
    Gtk::Stack *stack;
    void on_stack_changed();
public : 
    BxNav();
    ~BxNav();
    /// @brief Add item stack
    /// @param  widget
    /// @param  id name
    /// @param  seccion name
    /// @return void
    void add_item(Gtk::Widget *, const std::string &, const std::string &);
};