#include "../../inc/gtk/imagegestore.hpp"
#include "../../inc/gtk/svgconvert.hpp"
#include "../../inc/gtk/win/win_image_view.hpp"
struct ItemParent 
{
    /* data */
    GtkWindow* parent;
    string path;
};

ImageGestore::ImageGestore(GtkWidget *picture, const std::string _path, std::shared_ptr<SvgConvert> svg, GtkWindow* _parent) : parent(_parent)
{
    path = _path;
    image = picture;
    gtk_widget_set_size_request(image, svg->get_width(), svg->get_height());
    //g_print("w %d h %d path : %s \n", svg->get_width(), svg->get_height(), path.c_str());
    if(GTK_IS_IMAGE(image)){
        GdkTexture *texture = svg->get_texture(path);
        if(texture != nullptr)
            gtk_image_set_from_paintable(GTK_IMAGE(image), GDK_PAINTABLE(texture));
        else{
            g_print("Texture null \n");
        }
    }

    //gtk_widget_set_margin_start(image, 10);
    gtk_widget_set_margin_top(image, 10);
    gtk_widget_set_margin_end(image, 10);
    //gtk_widget_set_margin_bottom(image, 10);

    GtkGesture *gesture = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), GDK_BUTTON_PRIMARY);
    auto item = new ItemParent;
    item->parent = parent;
    item->path = path;
    g_signal_connect(gesture, "pressed", G_CALLBACK(&ImageGestore::on_click_gestore),(gpointer) item);
    gtk_widget_add_controller(image, GTK_EVENT_CONTROLLER(gesture));
}

ImageGestore::~ImageGestore()
{
}

GtkWidget* ImageGestore::get_image(){ return image;}

void ImageGestore::on_click_gestore(GtkGestureClick*,int, double x, double y, gpointer data){

    ItemParent *item = (ItemParent*) data;
    //g_print("path win %s \n", path.c_str());
    auto win = std::make_shared<WinImageView>(item->path, item->parent);
    win->show();

}