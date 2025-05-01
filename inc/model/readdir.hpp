#pragma once
#include <iostream>
#include <queue>

class ReadDir
{
private:
    /* data */
    std::queue<std::string> dir_list;

public:
    ReadDir(std::string);
    ~ReadDir();
    std::queue<std::string> getDirList();
};