#pragma once
#include "incgtk.hpp"
#include "svgconvert.hpp"
#include <iostream>
#include <memory>

using std::string;

class ImageGestore
{
private:
    /* data */

    std::string path;
    GtkWidget *image;
    static void on_click_gestore(GtkGestureClick*,int, double, double, gpointer);
    GtkWindow *parent;
public:
    ImageGestore(const std::string, std::shared_ptr<SvgConvert>, GtkWindow*);
    ~ImageGestore();

    GtkWidget *get_image();
};