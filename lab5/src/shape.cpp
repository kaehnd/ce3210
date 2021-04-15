/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-12 19:49:56
 * @ Description: Implementation of shape class
 */

#include "shape.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor
shape::shape(unsigned int color, unsigned int numVertices)
    : coordinates(4, numVertices), color(color), vertices(numVertices)
{
}

// Copy constructor
shape::shape(const shape &other)
    : coordinates(other.coordinates), color(other.color), vertices(other.vertices)
{
}

// Destructor
shape::~shape()
{
}

// Draw the shape, base class just sets the color
void shape::draw(GraphicsContext *context) const
{
    context->setColor(color);
}

// Output all coordinates as an STL facet
void shape::out(ostream &outstr) const
{
    outstr << "  facet normal 0 0 0" << endl << "    outer loop" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        outstr << "      vertex   " << coordinates[0][i] << " "
               << coordinates[1][i] << " " << coordinates[2][i] << endl;
    }
    outstr << "    endloop" << endl << "  endfacet" << endl;
}

// Set coordinates from an STL facet
void shape::in(istream &instr)
{
    string lineBuffer;

    getline(instr, lineBuffer);

    if (lineBuffer.find("endsolid") == string::npos &&
        lineBuffer.find_first_not_of(" \t\n\v\f\r") != string::npos)
    {
        getline(instr, lineBuffer);

        bool moreFacets = true;
        string vertex;

        for (int i = 0; moreFacets; i++)
        {
            getline(instr, lineBuffer);
            stringstream stream(lineBuffer);
            stream >> vertex;
            if (vertex == "vertex")
            {
                stream >> coordinates[0][i] >> coordinates[1][i] >>
                    coordinates[2][i];
            }
            else
            {
                moreFacets = false;
            }
        }
        getline(instr, lineBuffer); // endfacet
    }
}

// Assigns base class properties
shape &shape::operator=(shape &other)
{
    coordinates = other.coordinates;
    color = other.color;
    vertices = other.vertices;
    return *this;
}

// gets mutable reference to coordinates
matrix &shape::getCoordinates()
{
    return coordinates;
}

// gets immutable reference to coordinates
const matrix &shape::getCoordinates() const
{
    return coordinates;
}
