/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-12 10:41:08
 * @ Description: Triangle shape class
 */

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "shape.h"

class triangle : public shape
{
  public:
    /**
     * @brief  Constructs a  triangle from a color and all coordinates
     * @param  color: 24-bit RDB color
     * @param  x0: x0 coordinate
     * @param  y0: y0 coordinate
     * @param  x1: x1 coordinate
     * @param  y1: y1 coordinate
     * @param  x2: x2 coordinate
     * @param  y2: y2 coordinate
     */
    triangle(unsigned int color, double x0, double y0, double x1, double y1,
             double x2, double y2);

    /**
     * @brief  Copy constructor for triangle
     * @param  other: triangle to copy from
     */
    triangle(const triangle &other);

    /**
     * @brief  Construct a triangle from an STL facet in an istream and a color
     * @param  color: 24-bit RGB color
     * @param  instr: stream containing STL formatted text
     */
    triangle(unsigned int color, std::istream &instr);

    /**
     * @brief Destructs a triangle
     */
    ~triangle();

    /**
     * @brief  Deep copies all properties from other
     * @param  other: triangle to copy from 
     * @retval reference to this
     */
    virtual triangle &operator=(triangle &other);

    /**
     * @brief  Draw this shape in the provided context
     * @param  context: context to draw in
     */
    virtual void draw(GraphicsContext *context) const;

    /**
     * @brief  Inserts triangle into ostream in Text STL facet format
     * @param  outstr: stream to insert into
     */
    virtual void out(std::ostream &outstr) const;

    /**
     * @brief  Sets triangle properties from a STL facet in the istream
     * @param  instr: stream to extract from
     */
    virtual void in(std::istream &instr);

    /**
     * @brief  Copy this triangle to a new triangle
     * @retval Copy of this
     */
    virtual triangle *clone() const;
};

#endif // __TRIANGLE_H__
