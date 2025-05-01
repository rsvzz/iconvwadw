#include "../../inc/gtk/itemfiles.hpp"
#include "../../inc/gtk/bxbody.hpp"
#include "../../inc/model/readdir.hpp"
#include <filesystem>
#include <iostream>

ItemFiles::ItemFiles(BxNav *_nav) : nav(_nav)
{
    // Constructor implementation
}

ItemFiles::~ItemFiles()
{
    // Destructor implementation
}

void ItemFiles::dir_show(std::string path)
{
    // Implementation of dir_show
    std::unique_ptr<ReadDir> dir = std::make_unique<ReadDir>(path);
    std::queue<std::string> qdir = dir->getDirList();
    while (!qdir.empty())
    {
        std::string dir_name = qdir.front();
        BxBody *body = Gtk::make_managed<BxBody>(dir_name);
        std::filesystem::path dirPath(dir_name);
        //body->create_grid(dir_name);
        nav->add_item(body, dirPath.filename().string(), dirPath.filename().string());
        qdir.pop();
    }
}
