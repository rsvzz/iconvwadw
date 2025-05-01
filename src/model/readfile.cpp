#include "../../inc/model/readfile.hpp"
#include <filesystem>

std::queue<std::string> ReadFile::getFileList(std::string path)
{
    std::queue<std::string> file_list;
    for (const auto &file : std::filesystem::recursive_directory_iterator(path))
    {
        file_list.push(file.path());
    }
    return file_list;
}
ReadFile::ReadFile(){}

ReadFile::~ReadFile()
{
}