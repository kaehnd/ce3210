/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-12 11:03:04
 * @ Description: Implementation of line class
 */

#include "line.h"
#include "matrix.h"
#include "shape.h"

// Constructs line from coordinates and color
line::line(unsigned int color, double x0, double y0, double x1, double y1)
    : shape(color, 2)
{
    getCoordinates()[0][0] = x0;
    getCoordinates()[1][0] = y0;
    getCoordinates()[0][1] = x1;
    getCoordinates()[1][1] = y1;
}

// Copy constructor
line::line(const line &other) : shape(other)
{
}

// Assignment operator
line &line::operator=(line &other)
{
    shape::operator=(other);
    return *this;
}

// Draws this in the provided context
void line::draw(GraphicsContext *context) const
{
    shape::draw(context);
    context->drawLine(getCoordinates()[0][0], getCoordinates()[1][0],
                      getCoordinates()[0][1], getCoordinates()[1][1]);
}

// not supported
void line::out(std::ostream &outstr) const
{
    throw unsupportedShapeOperationException("line::out not supported");
}

// not supported
void line::in(const std::istream &instr)
{
    throw unsupportedShapeOperationException("line::in not supported");
}

// Copy this to a new line
line *line::clone() const
{
    return new line(*this);
}
