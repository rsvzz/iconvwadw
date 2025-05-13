#include "../../inc/gtk/app.hpp"
#include "../../inc/gtk/bxnav.hpp"
#include "../../inc/gtk/itemfiles.hpp"
#include <glibmm-2.68/glibmm.h>
#include <filesystem>
#include <thread>

App::App(){
  Gtk::HeaderBar *header = Gtk::make_managed<Gtk::HeaderBar>();
  Gtk::Label *lbl_title = Gtk::make_managed<Gtk::Label>("Icon Browser Adw");
  header->set_title_widget(*lbl_title);
  this->set_titlebar(*header);
  this->set_default_size(850, 720);

  BxNav *nav = Gtk::make_managed<BxNav>();
  auto files = std::make_unique<ItemFiles>(nav);

  std::filesystem::path exe_path = std::filesystem::read_symlink("/proc/self/exe");
  std::filesystem::path app_root, path_end;
  if(Glib::getenv("SNAP") != "")
  {
    app_root = exe_path.parent_path();
    path_end = Glib::build_filename(G_DIR_SEPARATOR_S, app_root,"../usr/share/icons/Adwaita/symbolic");
  }
  else
  {
    app_root = exe_path.root_directory();
    path_end = Glib::build_filename(G_DIR_SEPARATOR_S, app_root,"/usr/share/icons/Adwaita/symbolic");
  }
  std::thread t1(std::bind(&ItemFiles::dir_show, *files, path_end.string()));
  t1.detach();
  this->set_child(*nav);
};
