#include "../../inc/gtk/bxbody.hpp"
#include "../../inc/gtk/gdview.hpp"
#include <thread>
#include <memory>

BxBody::BxBody(const std::string &_path) : Gtk::Box(Gtk::Orientation::VERTICAL, 0), DarkMode(this)
{
    // Constructor implementation
    scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolled_window->set_expand(true);
    this->path = _path;
    this->append(*scrolled_window);
}
BxBody::~BxBody()
{
    // Destructor implementation
}
void BxBody::create_grid()
{
    // Implementation of create_grid
    if (scrolled_window->get_child() == nullptr)
    {
        GdView *grid = Gtk::make_managed<GdView>(this->path);
        grid->set_halign(Gtk::Align::CENTER);
        std::thread t1(&GdView::set_image_grid_for_data, grid);
        t1.join();
        scrolled_window->set_child(*grid);
    }
}
