#include "../../inc/gtk/gdview.hpp"
#include "../../inc/model/readfile.hpp"
#include "../../inc/gtk/imgevt.hpp"
#include "../../inc/gtk/svgcv.hpp"
#include <filesystem>
#include <iostream>

GdView::GdView(std::string path)
{
    // Constructor implementation
    
    this->path = path;
}

GdView::~GdView()
{
    // Destructor implementation
}

void GdView::set_image_grid_for_data(){
    std::unique_ptr<ReadFile> readfile = std::make_unique<ReadFile>();
    std::queue<std::string> content = readfile->getFileList(this->path);
    int i = 0, j = 0, width = 60, height = 60;
    auto svg = std::make_shared<SvgCv>(width, height);
    while (!content.empty())
    {
        std::string file_name = content.front();
        std::filesystem::path filePath(file_name);
        //std::make_shared breaking signal gtkmm
        auto image = Gtk::make_managed<ImgEvt>(filePath.string(), svg); 
        this->attach(*image, j, i, 1, 1);
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