#ifndef MTL_H
#define MTL_H

#include <string>
#include <vector>

class MTL{
    public:
        MTL(std::string filename);
    private:
        std::vector<std::string> texture_files;
};

#endif