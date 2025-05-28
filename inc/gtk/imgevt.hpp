#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
class ImgEvt : public Gtk::Image
    // Gtk::EventController interface
{
private:
    /* data */
    void on_click_gestore(int, double, double);
    std::string path;
public:
    ImgEvt(const std::string);
    ~ImgEvt();
};

