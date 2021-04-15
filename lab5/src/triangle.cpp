/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-12 11:02:44
 * @ Description: Implementation of triangle class
 */

#include "triangle.h"

// Constructor
triangle::triangle(unsigned int color, double x0, double y0, double x1,
                   double y1, double x2, double y2)
    : shape(color, 3)
{
    getCoordinates()[0][0] = x0;
    getCoordinates()[1][0] = y0;
    getCoordinates()[0][1] = x1;
    getCoordinates()[1][1] = y1;
    getCoordinates()[0][2] = x2;
    getCoordinates()[1][2] = y2;
}

// Copy constructor
triangle::triangle(const triangle &other) : shape(other)
{
}

// Constructor from STL stream
triangle::triangle(unsigned int color, std::istream &instr) : shape(color, 3)
{
    in(instr);
}

// Destructor
triangle::~triangle()
{
}

// Assignment
triangle &triangle::operator=(triangle &other)
{
    shape::operator=(other);
    return *this;
}

// Draw this triangle
void triangle::draw(GraphicsContext *context) const
{
    shape::draw(context);

    context->drawLine(getCoordinates()[0][0], getCoordinates()[1][0],
                      getCoordinates()[0][1], getCoordinates()[1][1]);
    context->drawLine(getCoordinates()[0][1], getCoordinates()[1][1],
                      getCoordinates()[0][2], getCoordinates()[1][2]);
    context->drawLine(getCoordinates()[0][0], getCoordinates()[1][0],
                      getCoordinates()[0][2], getCoordinates()[1][2]);
}

// Outputs to STL
void triangle::out(std::ostream &outstr) const
{
    shape::out(outstr);
}

// Inputs from STL
void triangle::in(std::istream &instr)
{
    shape::in(instr);
}

// Clone triangle
triangle *triangle::clone() const
{
    return new triangle(*this);
}
