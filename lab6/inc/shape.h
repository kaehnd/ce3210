/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 20:08:57
 * @ Description:
 */

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "gcontext.h"
#include "matrix.h"
#include "vcontext.h"
#include <iostream>

// Class used to denote methods in inheriting shapes as unsupported
// Typically a bad polymorphic design since calling classes can no
// longer trust this interface, but this is a temporary implementation
class unsupportedShapeOperationException : public std::runtime_error
{
  public:
    unsupportedShapeOperationException(std::string message)
        : std::runtime_error(
              (std::string("Matrix Exception: ") + message).c_str())
    {
    }
};

class shape
{
  public:
    /**
     * @brief  Constructs a shape with a color and a number of columns
     * @param  color: 24-bit RGB representation of color
     * @param  numVertices: number of columns to allocate in the coordinate
     * matrix for this shape (will always have 4 rows: x, y, z, dummy for
     * transformations)
     */
    shape(unsigned int color, unsigned int numVertices = 1);

    /**
     * @brief  Copy constructor for shape
     * @param  other: shape to copy
     */
    shape(const shape &other);

    /**
     * @brief  Destructs a shape
     */
    virtual ~shape();

    /**
     * @brief  Draw this shape using the given GraphicsContext
     * @note   The base draw functionality should be called in each subclass, as
     * it handles the color of the shape
     * @param  context: GraphicsContext to draw on
     */
    virtual void draw(GraphicsContext *gc, ViewContext * vc);

    /**
     * @brief  Inserts this shape into the ostream as text in the STL format as
     * a single facet
     * @note   Only implemented for triangle
     * @param  outstr: stream to insert into
     */
    virtual void out(std::ostream &outstr) const;

    /**
     * @brief  Sets the coordinates of this shape from a facet in the STL format
     * from the passed istream
     * @note   Only implemented for triangle
     * @param  instr: stream to pull from
     */
    virtual void in(std::istream &instr);

    /**
     * @brief  Copy this object to a new shape, 'virtual constructor'
     * @retval Copy of this, preserving the object type
     */
    virtual shape *clone() const = 0;

  protected:
    /**
     * @brief  Assigns all shape-level properties from other to this
     * @param  other: shape to copy from
     * @retval this
     */
    virtual shape &operator=(shape &other);

    /**
     * @brief  Gets the coordinates matrix
     * @retval matrix object of shape's coordinates
     */
    const matrix &getCoordinates() const;

    matrix &getBaseCoordinates();
    const matrix & getBaseCoordinates() const;

  private:
    // coordinates matrix stores all coordinates of the shape in (x, y, z, 0)
    // format
    matrix baseCoordinates;

    matrix transformedCoordinates;
    
    // 24-bit RDB color
    unsigned int color;
    // number of vertices of this shape (also # columns of coordinate matrix)
    unsigned int vertices;
};

#endif // __SHAPE_H__
