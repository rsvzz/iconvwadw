#include "../incgtk.hpp"
#include <iostream>

class WinImageView
{
private:
    /* data */
    std::string file_name;
    static void on_copy_clicked(GtkWidget*, gpointer);

    GtkWidget *win, *box;
    GtkWindow* parent;
public:
    /// @brief 
    /// @param  path
    /// @param  Window main
    WinImageView(const std::string, GtkWindow*);
    ~WinImageView();

    GtkWidget *get_window();
    void show();

    std::string get_file_name();
};