#include "../../inc/gtk/gdview.hpp"
#include "../../inc/model/readfile.hpp"
#include "../../inc/gtk/imgevt.hpp"
#include <filesystem>

GdView::GdView(std::string path)
{
    // Constructor implementation
    std::unique_ptr<ReadFile> readfile = std::make_unique<ReadFile>();
    std::queue<std::string> content = readfile->getFileList(path);
    int i = 0, j = 0;
    while (!content.empty())
    {
        std::string file_name = content.front();
        std::filesystem::path filePath(file_name);
        ImgEvt* image = new ImgEvt(filePath.string());
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

GdView::~GdView()
{
    // Destructor implementation
}

