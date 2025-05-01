#include <gtkmm-4.0/gtkmm.h>

class WinImg : public Gtk::Window
{
private:
    /* data */
    std::string file_name;
    void on_copy_clicked();
public:
    WinImg(std::string);
    ~WinImg();
};
