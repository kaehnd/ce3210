/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-05-12 12:31:44
 * @ Description: Implementation of triangle class
 */

#include "triangle.h"

// Constructor
triangle::triangle(unsigned int color, double x0, double y0, double z0, double x1,
                   double y1, double z1, double x2, double y2, double z2)
    : shape(color, 3)
{
    setCoordinates(x0, y0, z0, x1, y1, z1, x2, y2, z2);
}

// Constructor
triangle::triangle(unsigned int color, const matrix &values) : shape(color, 3)
{
    setCoordinates(values[0][0], values[1][0], values[2][0], values[0][1], values[1][1], values [2][1],
                   values[0][2], values[1][2], values[2][2]);
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
void triangle::draw(GraphicsContext *gc, ViewContext *vc)
{
    shape::draw(gc, vc);

    gc->drawLine(getCoordinates()[0][0], getCoordinates()[1][0],
                 getCoordinates()[0][1], getCoordinates()[1][1]);
    gc->drawLine(getCoordinates()[0][1], getCoordinates()[1][1],
                 getCoordinates()[0][2], getCoordinates()[1][2]);
    gc->drawLine(getCoordinates()[0][0], getCoordinates()[1][0],
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

void triangle::setCoordinates(double x0, double y0, double z0, double x1, double y1, double z1,
                              double x2, double y2, double z2)
{
    getBaseCoordinates()[0][0] = x0;
    getBaseCoordinates()[1][0] = y0;
    getBaseCoordinates()[2][0] = z0;
    getBaseCoordinates()[0][1] = x1;
    getBaseCoordinates()[1][1] = y1;
    getBaseCoordinates()[2][1] = z1;
    getBaseCoordinates()[0][2] = x2;
    getBaseCoordinates()[1][2] = y2;
    getBaseCoordinates()[2][2] = z2;

}
