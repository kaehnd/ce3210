#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std; // for iostream, string

void processStlFile(string filename)
{
    int facetNum = 0;

    double maxX = 0, maxY = 0, maxZ = 0;
    double minX = 0, minY = 0, minZ = 0;

    cout << "Processing " << filename << "..." << endl;



    cout << "=======================" << endl
         << "========SUMMARY========" << endl
         << "=======================" << endl;

    cout << "In " << facetNum << " facets:" << endl;
    cout << "Max x coordinate was " << maxX << endl;
    cout << "Max y coordinate was " << maxY << endl;
    cout << "Max z coordinate was " << maxZ << endl;

    cout << "Min x coordinate was " << minX << endl;
    cout << "Min y coordinate was " << minY << endl;
    cout << "Min z coordinate was " << minZ << endl;

}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "include file name on command line" << endl;
    }
    else
    {
        processStlFile(argv[1]);
    }
    return 0;
}