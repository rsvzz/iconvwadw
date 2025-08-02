#pragma once
#include "incgtk.hpp"

#include <iostream>

using std::string;

class BoxBody
{
private:
    /* data */
    GtkWidget *box, *scrollw;
    string path;
    GtkWindow *parent;
public:
    BoxBody(const string&, GtkWindow*);
    ~BoxBody();
    void create_grid();

    GtkWidget* get_box();
};