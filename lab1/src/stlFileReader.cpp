/**
 * CS 3210 011
 * Daniel Kaehn
 * Lab 1: C++ Console Program
 * 03/14/2021
 *
 * stlFileReader.cpp: class definition for stlFileReader component
 * Used to allow greater function extraction without creating global variables
 * when reading from STL file
 */

#include "stlFileReader.h"
#include <cfloat>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/**
 * Constructs object, opens reader to provided file
 * params: string filename; path to the STL file to read
 */
stlFileReader::stlFileReader(string filename)
    : maxX(-DBL_MAX), maxY(-DBL_MAX), maxZ(-DBL_MAX), minX(DBL_MAX),
      minY(DBL_MAX), minZ(DBL_MAX), numFacets(0), filename(filename),
      lineBuffer(""), filein(filename.c_str())
{
}

/**
 *  @brief Reads the entire STL file, prints each facet to stdout,
 *  and stores min and max x, y, and z coordinate values
 */
void stlFileReader::processFile()
{
    cout << "Processing " << filename << "..." << endl;

    getline(filein, lineBuffer);

    while (filein)
    {
        processFacet();
    }
}

/**
 * @brief prints summary of read STL file (called after processFile);
 * including numFacets and min and max coodinates
 */
void stlFileReader::printSummary()
{
    cout << "=======================" << endl
         << "========SUMMARY========" << endl
         << "=======================" << endl;

    cout << "In " << numFacets << " facets:" << endl;
    cout << "Max x coordinate was " << maxX << endl;
    cout << "Max y coordinate was " << maxY << endl;
    cout << "Max z coordinate was " << maxZ << endl;

    cout << "Min x coordinate was " << minX << endl;
    cout << "Min y coordinate was " << minY << endl;
    cout << "Min z coordinate was " << minZ << endl;
}

/**
 *  @brief Reads a single facet, prints its contents to stdout
 */
void stlFileReader::processFacet()
{
    getline(filein, lineBuffer);

    if (lineBuffer.find("endsolid") == string::npos &&
        lineBuffer.find_first_not_of(" \t\n\v\f\r") != string::npos)
    {
        getline(filein, lineBuffer);

        numFacets++;
        cout << "Facet " << numFacets << endl;
        for (int i = 0; i < 3; i++)
        {
            processVertex(i);
        }
        getline(filein, lineBuffer);
        getline(filein, lineBuffer);
        cout << endl;
    }
}

/**
 *  @brief Reads a single vertex, prints its contents to stdout,
 * stores min/max coordinate values
 */
void stlFileReader::processVertex(int vertexNum)
{
    string vertex;
    double x, y, z;
    getline(filein, lineBuffer);
    stringstream(lineBuffer) >> vertex >> x >> y >> z;

    cout << "Vertex " << vertexNum << ": (" << x << ", " << y << ", " << z
         << ")" << endl;

    maxX = max(x, maxX);
    maxY = max(y, maxY);
    maxZ = max(z, maxZ);

    minX = min(x, minX);
    minY = min(y, minY);
    minZ = min(z, minZ);
}

stlFileReader::~stlFileReader() { filein.close(); }
