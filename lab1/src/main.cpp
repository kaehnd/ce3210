/**
 * CS 3210 011
 * Daniel Kaehn
 * Lab 1: C++ Console Program
 * 03/14/2021
 *
 * main.cpp: implements program reading and printing contents of an STL file
 */

#include "stlFileReader.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief uses stlFileReader class to read in
 * and print contents and summary of an STL file
 */
void processStlFile(string filename)
{
    stlFileReader fileReader(filename);
    fileReader.processFile();
    fileReader.printSummary();
}

/**
 * @brief main entry to program,
 * takes one command line argument of the STL file filename
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "include file name on command line" << endl;
    }
    else
    {
        char *filename = argv[1];
        processStlFile(filename);
    }
    return 0;
}
