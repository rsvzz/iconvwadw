#include "../../inc/gtk/gdataview.hpp"
#include "../../inc/model/readfile.hpp"
#include "../../inc/gtk/svgconvert.hpp"
#include "../../inc/gtk/imagegestore.hpp"
#include <filesystem>
#include <iostream>
using std::string;

GridDataView::GridDataView(string _path, GtkWindow* _parent)
{
    path = _path;
    parent = _parent;

    grid = gtk_grid_new();
}

GridDataView::~GridDataView()
{
}

void GridDataView::set_image_grid_for_data(){
   
    std::unique_ptr<ReadFile> readfile = std::make_unique<ReadFile>();
    std::queue<std::string> content = readfile->getFileList(this->path);
    int i = 0, j = 0, width = 60, height = 60;
    auto svg = std::make_shared<SvgConvert>(width, height);
    while (!content.empty())
    {
        std::string file_name = content.front();
        std::filesystem::path filePath(file_name);
        auto img = std::make_shared<ImageGestore>(filePath.string(), svg, parent);
        gtk_grid_attach(GTK_GRID(grid), img->get_image(), j, i, 1, 1);
        content.pop();
        if (j < 8)
        {
            j++;
        }
        else
        {
            j = 0;
            i++;
        }   
    }
}

GtkWidget* GridDataView::get_grid(){ return grid;}