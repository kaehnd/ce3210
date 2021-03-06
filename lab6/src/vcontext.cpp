/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-29 12:14:30
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

//Macros to simplify creation of transformation matrices
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

//Constructor
ViewContext::ViewContext(int windowHeight, int windowWidth)
    : windowHeight(windowHeight), windowWidth(windowWidth), m(4, 4), mInv(4, 4),
      rotation(0), transX(0), transY(0), transZ(0), scale(0)
{
    resetTransformation();
}

//Copy contstructor
ViewContext::ViewContext(const ViewContext &other)
    : windowHeight(other.windowHeight), windowWidth(other.windowWidth),
      m(other.m), mInv(other.mInv), rotation(other.rotation),
      transX(other.transX), transY(other.transY), transZ(other.transZ)
{
}

//Destructor - no dynamic memory
ViewContext::~ViewContext()
{
}


//Resets to base view transformation
void ViewContext::resetTransformation()
{
    rotation = 0;
    transX = transY = transZ = 0;
    scale = 1;

    recalculateMatrices();
}

//adds specified rotation
void ViewContext::addRotation(double angle)
{
    rotation += angle;
    recalculateMatrices();
}

//adds specified translation
void ViewContext::addTranslation(double x, double y)
{
    transX += x;
    transY += y;
    recalculateMatrices();
}

//Applies specified scalar
void ViewContext::applyScaling(double s)
{
    scale *= s;
    recalculateMatrices();
}

//convert model coordinates to device coordinates
matrix ViewContext::modelToDevice(const matrix &coordinates)
{
#ifdef DEBUG_TRANSFORMATIONS
    cout << "modelToDevice" << endl;
    cout << "Before matrix: " << endl << coordinates << endl;
    cout << "Transformation matrix: " << endl << m << endl;
#endif

    matrix toReturn = m * coordinates;

#ifdef DEBUG_TRANSFORMATIONS
    cout << "After matrix: " << endl << toReturn << endl;
#endif

    return toReturn;
}

//convert device coordinates to model coordinates
matrix ViewContext::deviceToModel(const matrix &coordinates)
{
#ifdef DEBUG_TRANSFORMATIONS
    cout << "devicetoModel" << endl;
    cout << "Before matrix: " << endl << coordinates << endl;
    cout << "Transformation matrix: " << endl << mInv << endl;
#endif

    matrix toReturn = mInv * coordinates;

#ifdef DEBUG_TRANSFORMATIONS
    cout << "After matrix: " << endl << toReturn << endl;
#endif

    return toReturn;
}

//Internal method to recalculate m and mInv
void ViewContext::recalculateMatrices()
{
    //Since we have predefined ways that the transformation will be applied
    //didn't bother with having any dynamic support for different orders of
    // different transofrmations... this is ugly, but it works
    m = translationMatrix(windowWidth / 2.0, windowHeight / 2.0, 0) *
        flipYMatrix() * scalingMatrix(scale) * 
        translationMatrix(transX, transY, transZ) * rotZMatrix(rotation);

    mInv = rotZMatrix(-rotation) * translationMatrix(-transX, -transY, -transZ) *
            scalingMatrix(1 / scale) * flipYMatrix() *
           translationMatrix(-windowWidth / 2.0, -windowHeight / 2.0, 0);
}
