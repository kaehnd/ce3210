#include "shape.h"

shape::shape(unsigned int coordRows = 4, unsigned int coordCols = 1):coordinates(coordRows, coordCols)
{

}

shape::shape(shape& other): color(other.color), coordinates(other.coordinates)
{

}

shape::~shape()
{

}

void shape::draw(GraphicsContext *context) const
{
    //todo
    context->setColor(context->BLACK);
}
void shape::out(std::ostream &outstr) const
{

}
void shape::in(const std::istream &instr)
{

}
shape &shape::clone() const
{

}
shape &shape::operator=(shape &other)
{

}

matrix& shape::getCoordinates()
{
    return coordinates;
}
