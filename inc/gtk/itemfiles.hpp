#pragma once
#include "bxbody.hpp"
#include "bxnav.hpp"
#include <iostream>

class ItemFiles
{
private:
    /* data */
    BxNav *nav;

public:
    ItemFiles(BxNav *nav);
    ~ItemFiles();
    void dir_show(std::string path);
};
