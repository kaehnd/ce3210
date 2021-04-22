/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-21 22:08:46
 * @ Description: Implements functionality of line class
 */

#ifndef __LINE_H__
#define __LINE_H__

#include "matrix.h"
#include "shape.h"

class line : public shape
{
  public:
    /**
     * @brief  Constructs a line from all coordinates
     * @param  color: 24-bit  RGB color
     * @param  x0: x0 coordinate
     * @param  y0: y0 coordinate
     * @param  x1: x1 coordinate
     * @param  y1: y1 coordinate
     */
    line(unsigned int color, double x0, double y0, double x1, double y1);

    /**
     * @brief  Constructs a line from all coordinates
     * @param  color: 24-bit  RGB color
     * @param  values: matrix containing coordinates of both points of line
     */
    line(unsigned int color, const matrix &values);

    /**
     * @brief  Copy constructor for line class
     * @param  other: line to copy from
     */
    line(const line &other);

    /**
     * @brief  Assigns properties from the other line
     * @param  other: line to assign from
     * @retval reference to this
     */
    virtual line &operator=(line &other);

    /**
     * @brief  Draws this line using the given context
     * @param  context: GraphicsContext to draw in
     */
    virtual void draw(GraphicsContext *context) const;

    // NOT SUPPORTED, THROWS EXCEPTION
    virtual void out(std::ostream &outstr) const;

    // NOT SUPPORTED, THROWS EXCEPTION
    virtual void in(const std::istream &instr);

    /**
     * @brief  Copies this line to a new object
     * @retval a copy of this line
     */
    virtual line *clone() const;

  private:
    void setCoordinates(double x0, double y0, double x1, double y1);
};

#endif // __LINE_H__