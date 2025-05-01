#include <iostream>
#include <gtkmm-4.0/gtkmm.h>
#include "../inc/gtk/app.hpp"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("io.github.rsvzz.icviewadw");
  return app->make_window_and_run<App>(argc, argv);
}


