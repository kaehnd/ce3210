/**
 * CS 3210 011
 * Daniel Kaehn
 * Lab 1: C++ Console Program
 * 03/14/2021
 *
 * stlFileReader.H: class declaration for stlFileReader component
 * Used to allow greater function extraction without creating global variables
 * when reading from STL file
 */

#ifndef STLFILEREADER
#define STLFILEREADER

#include <fstream>
#include <string>

using namespace std;

/**
 * stlFileReader class
 * Reads from provided STL file
 */
class stlFileReader
{
  public:
    /**
     * Constructs object, opens reader to provided file
     * params: string filename; path to the STL file to read
     */
    stlFileReader(string filename);

    /**
     *  @brief Reads the entire STL file, prints each facet to stdout,
     *  and stores min and max x, y, and z coordinate values
     */
    void processFile();

    /**
     * @brief prints summary of read STL file (called after processFile);
     * including numFacets and min and max coodinates
     */
    void printSummary();

    ~stlFileReader();

  private:
    double maxX, maxY, maxZ;
    double minX, minY, minZ;
    int numFacets;

    string filename;
    string lineBuffer;

    ifstream filein;

    /**
     *  @brief Reads a single facet, prints its contents to stdout
     */
    void processFacet();

    /**
     *  @brief Reads a single vertex, prints its contents to stdout,
     * stores min/max coordinate values
     */
    void processVertex(int vertexNum);
};

#endif
