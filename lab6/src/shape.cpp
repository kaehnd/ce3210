/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-28 12:10:53
 * @ Description: Implementation of shape class
 */

#include "shape.h"
#include "vcontext.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor
shape::shape(unsigned int color, unsigned int numVertices)
    : baseCoordinates(4, numVertices), transformedCoordinates(4, numVertices),
      color(color), vertices(numVertices)
{
    for (unsigned int i = 0; i < numVertices; i++)
    {
        baseCoordinates[3][i] = 1; // set bottom row to 1
    }
}

// Copy constructor
shape::shape(const shape &other)
    : baseCoordinates(other.baseCoordinates),
      transformedCoordinates(other.transformedCoordinates), color(other.color),
      vertices(other.vertices)
{
}

// Destructor
shape::~shape()
{
}

// Draw the shape, base class just sets the color and applies transformation
void shape::draw(GraphicsContext *gc, ViewContext *vc)
{
    gc->setColor(color);
    transformedCoordinates = vc->modelToDevice(baseCoordinates);
    // cout<<"Coords to draw: "<<endl<<transformedCoordinates<<endl;
}

// Output all coordinates as an STL facet
void shape::out(ostream &outstr) const
{
    cout<<"Saving this: "<<endl<<baseCoordinates<<endl;
    outstr << "  facet normal 0 0 0" << endl << "    outer loop" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        outstr << "      vertex   " << baseCoordinates[0][i] << " "
               << baseCoordinates[1][i] << " " << baseCoordinates[2][i] << endl;
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
                stream >> baseCoordinates[0][i] >> baseCoordinates[1][i] >>
                    baseCoordinates[2][i];
            }
            else
            {
                moreFacets = false;
            }
        }
        getline(instr, lineBuffer); // endfacet
    }
    cout<<"Loaded this: "<<endl<<baseCoordinates<<endl;

}

// Assigns base class properties
shape &shape::operator=(shape &other)
{
    baseCoordinates = other.baseCoordinates;
    color = other.color;
    vertices = other.vertices;
    return *this;
}

// gets immutable reference to transformed coordinates
const matrix &shape::getCoordinates() const
{
    return transformedCoordinates;
}

// gets mutable reference to coordinates
matrix &shape::getBaseCoordinates()
{
    return baseCoordinates;
}

// gets immutable reference to coordinates
const matrix &shape::getBaseCoordinates() const
{
    return baseCoordinates;
}
