#include "vcontext.h"
#include "gcontext.h"
#include "matrix.h"

#include <cmath>
#include <iostream>

#define USE_MATH_DEFINES

using namespace std;

#define identityMatrix()           {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}
#define translationMatrix(x, y, z) { 1, 0, 0, x, 0,  1, 0, y, 0, 0, 1, z, 0, 0, 0, 1}
#define scalingMatrix(s)           { s, 0, 0, 0, 0,  s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1}
#define flipXMatrix()              {-1, 0, 0, 0, 0,  1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}
#define flipYMatrix()              { 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}
#define rotZMatrix(theta)          {cos(theta), -sin(theta), 0, 0, sin(theta), cos(theta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}



ViewContext::ViewContext(GraphicsContext *gc) : windowHeight(gc->getWindowHeight()), windowWidth(gc->getWindowWidth()), m(4, 4), mInv(4, 4)
{
    resetTransformation();
}

ViewContext::ViewContext(const ViewContext &other)
    : transformations(other.transformations), windowHeight(other.windowHeight), windowWidth(other.windowWidth), m(other.m),
      mInv(other.mInv)
{
}

ViewContext::~ViewContext()
{
}

void ViewContext::resetTransformation() 
{
    matrix flip(4, 4, flipYMatrix());
    m = flip;
    mInv = flip;


    double x = windowWidth/2.0;
    double y = windowHeight/2.0;

    postAddTransformation(matrix(4, 4, translationMatrix(x, y, 0)), matrix(4, 4, translationMatrix(-x, -y, 0)));

}

void ViewContext::addRotation(double angle)
{
    rotation = angle;
}

void ViewContext::addTranslation(double x, double y)
{
    transX+=x;
    transY+=y;
    recalculateMatrices();
}

void ViewContext::addScaling(double s)
{
    scale*=s;
    recalculateMatrices();
}


matrix ViewContext::modelToDevice(const matrix &coordinates)
{
    cout<<"modelToDevice"<<endl;
    cout<<"Before matrix: "<<endl<<coordinates<<endl;
    cout<<"Transformation matrix: "<<endl<<m<<endl;

    matrix toReturn = m * coordinates;
    cout<<"After matrix: "<<endl<<toReturn<<endl;

    return toReturn;
}

matrix ViewContext::deviceToModel(const matrix &coordinates)
{
    cout<<"devicetoModel"<<endl;
    cout<<"Before matrix: "<<endl<<coordinates<<endl;
    cout<<"Transformation matrix: "<<endl<<mInv<<endl;

    matrix toReturn = mInv * coordinates;
    cout<<"After matrix: "<<endl<<toReturn<<endl;

    return toReturn;
}

void ViewContext::postAddTransformation(const matrix & tran, const matrix & invTran) 
{
    m = tran * m;
    mInv = mInv * invTran;
}

void ViewContext::preAddTransformation(const matrix & tran, const matrix & invTran) 
{
    m = m * tran;
    mInv = invTran * mInv;
    transformations.insert()
}


