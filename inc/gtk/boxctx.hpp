#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "nav.hpp"

class Boxctx : public Gtk::Box
{
private:
    /* data */
public:
    Boxctx(Nav*);
    ~Boxctx();
};

