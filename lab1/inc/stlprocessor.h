#pragma once

#include <string>

using namespace std;

class stlprocessor
{
private:
    double maxX, maxY, maxZ;
    double minX, minY, minZ;
    string filename;
    int facetNum;


    void processFacet(ifstream filein);
public:
    stlprocessor(string filename);

    void processFile();
    ~stlprocessor();
};


