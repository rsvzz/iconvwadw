#include "../../inc/gtk/dark_mode.hpp"

DarkMode::DarkMode(Gtk::Widget *widget)
{
    auto settings = Gtk::Settings::get_default();
    bool isDark = false;
    isDark = settings->property_gtk_application_prefer_dark_theme().get_value();
    if (isDark)
    {
        Glib::ustring data = ".box_content {background-color:rgb(85, 83, 83);}";
        auto provider = Gtk::CssProvider::create();
        provider->load_from_data(data);

        auto widcss = widget->get_style_context();
        widcss->add_class("box_content");
        widcss->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

DarkMode::~DarkMode()
{

}