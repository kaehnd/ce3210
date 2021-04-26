#ifndef __VCONTEXT_H__
#define __VCONTEXT_H__

/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 20:17:33
 * @ Description:
 */

#include "matrix.h"
#include "gcontext.h"
#include <vector>


class ViewContext
{
  public:
    ViewContext(GraphicsContext * gc);
    ViewContext(const ViewContext &other);

    virtual ~ViewContext();

    virtual void addRotation(double angle);
    virtual void addTranslation(double x, double y);
    virtual void addScaling(double s);
    virtual void undoTransformation();

    virtual matrix modelToDevice(const matrix & coordinates);
    virtual matrix deviceToModel(const matrix & coordinates);


  private:

    std::vector<matrix> transformations;
    GraphicsContext * gc;

    matrix m;
    matrix mInv;
};
#endif // __VCONTEXT_H__