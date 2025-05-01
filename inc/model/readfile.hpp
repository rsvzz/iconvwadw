#pragma once
#include <iostream>
#include <queue>

class ReadFile
{
private:
    /* data */
public:
    ReadFile();
    ~ReadFile();
    std::queue<std::string> getFileList(std::string);
};