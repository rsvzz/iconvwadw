#include "../../inc/model/readdir.hpp"
#include <filesystem>
#include <iostream>
ReadDir::ReadDir(std::string path)
{
    if (std::filesystem::is_directory(path))
    {
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_directory())
            {

                dir_list.push(entry.path().string());
            }
        }
    }
    else
    {
        std::cerr << "Error: " << path << " is not a directory." << std::endl;
    }
}

std::queue<std::string> ReadDir::getDirList()
{
    return dir_list;
}

ReadDir::~ReadDir()
{
}