#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>


class AdwWin
{
private:
    /* data */
    AdwApplication *app;
    GtkWidget *window;
public:
    AdwWin(const char*, GApplicationFlags);
    ~AdwWin();

    int Run(int, char**);
};

