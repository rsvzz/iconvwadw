#include "../../inc/gtk/boxctx.hpp"
#include "../../inc/gtk/nav.hpp"

Boxctx::Boxctx(Nav *nav) : Gtk::Box(Gtk::Orientation::HORIZONTAL, 5)
{
    // Constructor implementation
    this->append(*nav);
    this->append(*nav->get_stack());
}

Boxctx::~Boxctx()
{
    // Destructor implementation
}
