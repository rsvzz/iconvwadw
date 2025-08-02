#include "../../inc/gtk/file_item.hpp"
#include "../../inc/gtk/boxbody.hpp"
#include "../../inc/model/readdir.hpp"
#include <iostream>
#include <filesystem>
#include <memory>

using std::string;

FileItem::FileItem(NavBox *_nav, GtkWindow* _parent) : nav(_nav), parent(_parent)
{
    // Constructor implementation
}

FileItem::~FileItem()
{
    // Destructor implementation
}

void FileItem::dir_show(string path)
{
    // Implementation of dir_show
    std::unique_ptr<ReadDir> dir = std::make_unique<ReadDir>(path);
    std::queue<string> qdir = dir->getDirList();
    while (!qdir.empty())
    {
        string dir_name = qdir.front();
        auto body = std::make_shared<BoxBody>(dir_name, parent);
        std::filesystem::path dirPath(dir_name);
        body->create_grid();
        nav->add(body->get_box(), dirPath.filename().string(), dirPath.filename().string());
        qdir.pop();
    }
}