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
    /// @brief 
    /// @param GtkWidget picture 
    /// @param  Path
    /// @param  SvgConvert
    /// @param  GtkWindow parent for create new window
    ImageGestore(GtkWidget *, const std::string, std::shared_ptr<SvgConvert>, GtkWindow*);
    ~ImageGestore();

    GtkWidget *get_image();
};