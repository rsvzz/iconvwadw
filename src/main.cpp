#include <iostream>
#include "../inc/adwwin.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
  auto adw = std::make_shared<AdwWin>("io.github.rsvzz.iconvwadw", G_APPLICATION_DEFAULT_FLAGS);
  return adw->Run(argc, argv);
}


