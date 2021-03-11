#include "stlprocessor.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

stlprocessor::stlprocessor(string filename) { this->filename = filename; }
void stlprocessor::processFile()
{

    // open file - constructor does not like string!!!
    ifstream filein(filename.c_str());
    string line;

    getline(filein, line);

    while (filein)
    {
        processFacet(filein);
    }
    filein.close();
}

void stlprocessor::processFacet(ifstream filein)
{
    string line;
    getline(filein, line);

    if (line.find("endsolid") == string::npos)
    {
        getline(filein, line);

        facetNum++;
        cout << "Facet " << facetNum << endl;
        for (int i = 0; i < 3; i++)
        {
            string vertex;
            double x, y, z;
            getline(filein, line);
            stringstream(line) >> vertex >> x >> y >> z;

            cout << "Vertex " << i << ": (" << x << ", " << y << ", " << z
                 << ")" << endl;

            maxX = max(x, maxX);
            maxY = max(y, maxY);
            maxZ = max(z, maxZ);

            minX = min(x, minX);
            minY = min(y, minY);
            minZ = min(z, minZ);
        }
        getline(filein, line);
        getline(filein, line);
        cout << endl;
    }
}

stlprocessor::~stlprocessor() {}