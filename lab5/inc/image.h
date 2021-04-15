/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-12 19:15:04
 * @ Description: Implements functions for a collection of Shape objects
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "shape.h"
#include <iostream>
#include <vector>

class image
{
  public:
    /**
     * @brief  Construct an image
     */
    image();

    /**
     * @brief  Copy constructor for an image
     * @param  other: image to copy from
     */
    image(image &other);

    /**
     * @brief  Destructor for image, will destroy all contained shapes
     */
    ~image();

    /**
     * @brief  Deep assignment from another image
     * @param  other: image to assign from
     * @retval reference to this
     */
    image &operator=(image &other);

    /**
     * @brief  Adds a shape to the collection, OWNED BY THIS CLASS
     * @param  *shape:
     */
    void add(shape *shape);

    /**
     * @brief Draw all shapes in the given context
     * @param  *context:
     * @retval None
     */
    void draw(GraphicsContext *context) const;

    /**
     * @brief  Outputs all shapes as an STL file to the ostream
     * @param  outstr: Stream to insert into
     */
    void out(std::ostream &outstr) const;

    /**
     * @brief  Inputs shapes from an STL file in an istream
     * @note   This will give shapes a default blue color
     * @param  instr: istream to extract from
     */
    void in(std::istream &instr);

    /**
     * @brief  Remove and DELTE all shapes
     */
    void erase();

  private:
    std::vector<shape *> shapes;
};

#endif // __IMAGE_H__
