#include "../../inc/gtk/app.hpp"
#include "../../inc/gtk/bxnav.hpp"
#include "../../inc/gtk/itemfiles.hpp"

App::App(){
  Gtk::HeaderBar *header = Gtk::make_managed<Gtk::HeaderBar>();
  Gtk::Label *lbl_title = Gtk::make_managed<Gtk::Label>("Icon Browser Adw");
  header->set_title_widget(*lbl_title);
  this->set_titlebar(*header);
  this->set_default_size(850, 720);

  BxNav *nav = Gtk::make_managed<BxNav>();
  auto files = std::make_unique<ItemFiles>(nav);
  files->dir_show("/usr/share/icons/Adwaita/symbolic");
  this->set_child(*nav);
};
