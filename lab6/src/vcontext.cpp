/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-29 08:56:02
 * @ Description: Implements ViewContext wrapper around matrix for view
 * transformations
 */

#include "vcontext.h"
#include "gcontext.h"
#include "matrix.h"

#include <cmath>
#include <iostream>

#define USE_MATH_DEFINES

using namespace std;

#define identityMatrix()                                                       \
    matrix(4, 4, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
#define translationMatrix(x, y, z)                                             \
    matrix(4, 4, {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1})
#define scalingMatrix(s)                                                       \
    matrix(4, 4, {s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1})
#define flipXMatrix()                                                          \
    matrix(4, 4, {-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
#define flipYMatrix()                                                          \
    matrix(4, 4, {1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
#define rotZMatrix(theta)                                                      \
    matrix(4, 4,                                                               \
           {cos(theta), -sin(theta), 0, 0, sin(theta), cos(theta), 0, 0, 0, 0, \
            1, 0, 0, 0, 0, 1})

ViewContext::ViewContext(int windowHeight, int windowWidth)
    : windowHeight(windowHeight), windowWidth(windowWidth),
      m(4, 4), mInv(4, 4), rotation(0), transX(0), transY(0), transZ(0),
      scale(0)
{
    resetTransformation();
}

ViewContext::ViewContext(const ViewContext &other)
    : windowHeight(other.windowHeight), windowWidth(other.windowWidth),
      m(other.m), mInv(other.mInv), rotation(other.rotation),
      transX(other.transX), transY(other.transY), transZ(other.transZ)
{
}

ViewContext::~ViewContext()
{
}

void ViewContext::resetTransformation()
{
    rotation = 0;
    transX = transY = transZ = 0;
    scale = 1;

    recalculateMatrices();
}

void ViewContext::addRotation(double angle)
{
    rotation += angle;
    recalculateMatrices();
}

void ViewContext::addTranslation(double x, double y)
{
    transX += x;
    transY += y;
    recalculateMatrices();
}

void ViewContext::addScaling(double s)
{
    scale *= s;
    recalculateMatrices();
}

matrix ViewContext::modelToDevice(const matrix &coordinates)
{
    cout << "modelToDevice" << endl;
    cout << "Before matrix: " << endl << coordinates << endl;
    cout << "Transformation matrix: " << endl << m << endl;

    matrix toReturn = m * coordinates;
    cout << "After matrix: " << endl << toReturn << endl;

    return toReturn;
}

matrix ViewContext::deviceToModel(const matrix &coordinates)
{
    cout << "devicetoModel" << endl;
    cout << "Before matrix: " << endl << coordinates << endl;
    cout << "Transformation matrix: " << endl << mInv << endl;

    matrix toReturn = mInv * coordinates;
    cout << "After matrix: " << endl << toReturn << endl;

    return toReturn;
}

void ViewContext::recalculateMatrices()
{
    m = translationMatrix(windowWidth / 2.0, windowHeight / 2.0, 0) *
        flipYMatrix() * scalingMatrix(scale) *
        translationMatrix(transX, transY, transZ) * rotZMatrix(rotation);

    mInv = rotZMatrix(-rotation) *
           translationMatrix(-transX, -transY, -transZ) *
           scalingMatrix(1 / scale) * flipYMatrix() *
           translationMatrix(-windowWidth / 2.0, -windowHeight / 2.0, 0);
}
