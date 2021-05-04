/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 20:19:01
 * @ Description: Implementaiton of image class
 */
#include "image.h"
#include "shape.h"
#include "triangle.h"
using namespace std;

// Constructor
image::image()
{
}

// Copy constructor
image::image(image &other) : shapes(other.shapes.size())
{
    for (unsigned int i = 0; i < other.shapes.size(); i++)
    {
        shapes[i] = other.shapes[i]->clone();
    }
}

// Destructor
image::~image()
{
    erase();
}

// Deep assignment
image &image::operator=(image &other)
{
    if (&other != this)
    {
        if (shapes.size() > 0)
        {
            erase();
        }
        for (shape *otherShape : other.shapes)
        {
            shapes.push_back(otherShape->clone());
        }
    }
    return *this;
}

// Adds shape to collection
void image::add(shape *shape)
{
    this->shapes.push_back(shape);
}

// Draw all shapes
void image::draw(GraphicsContext *gc, ViewContext *vc)
{
    for (shape *curShape : shapes)
    {
        curShape->draw(gc, vc);
    }
}

void image::out(ostream &outstr) const
{
    outstr << "solid Default" << endl;

    for (shape *thisShape : shapes)
    {
        thisShape->out(outstr);
    }

    outstr << "endsolid Default" << endl;
}

// Extract shapes from STL file
void image::in(istream &instr, unsigned int color)
{
    string lineBuffer;
    getline(instr, lineBuffer);

    while (instr.peek() == ' ') // ASCII STL always uses spaces, not tabs
    {
        shapes.push_back(new triangle(color, instr));
    }
}

// Delete all shapes
void image::erase()
{
    for (shape *curShape : shapes)
    {
        delete curShape;
    }
    shapes.clear();
}
