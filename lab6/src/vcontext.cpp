#include "vcontext.h"
#include "gcontext.h"
#include "matrix.h"

#include "cmath"
#define USE_MATH_DEFINES



ViewContext::ViewContext(GraphicsContext *gc) : gc(gc), m(4, 4), mInv(4, 4)
{
    double x = 3.2;


    matrix thing(4, 3, {3.0, 4.0, 1, x, x, x, 4, 5, 3});
}

ViewContext::ViewContext(const ViewContext &other)
    : transformations(other.transformations), gc(other.gc), m(other.m),
      mInv(other.mInv)
{
}

ViewContext::~ViewContext()
{
}

void ViewContext::addRotation(double angle)
{
}

void ViewContext::addTranslation(double x, double y)
{
}

void ViewContext::addScaling(double s)
{
}

void ViewContext::undoTransformation()
{
}

matrix ViewContext::modelToDevice(const matrix &coordinates)
{
    return m * coordinates;
}

matrix ViewContext::deviceToModel(const matrix &coordinates)
{
    return mInv * coordinates;
}
