/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-05-05 22:36:17
 * @ Description: Implements ViewContext wrapper around matrix for view
 * @ Modified by: Daniel Kaehn
 */

#include "vcontext.h"
#include "gcontext.h"
#include "matrix.h"

#include <cmath>
#include <iostream>

#define USE_MATH_DEFINES

#define ROT_DEFAULT 0

using namespace std;

// Macros to simplify creation of transformation matrices
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

// Constructor
ViewContext::ViewContext(int windowHeight, int windowWidth)
    : windowHeight(windowHeight), windowWidth(windowWidth), m(4, 4), mInv(4, 4),
      transX(0), transY(0), transZ(0), scale(0), N(0, 0, 0), orbH(ROT_DEFAULT), orbV(ROT_DEFAULT), radius(10)
{
    resetTransformation();
}

// Copy contstructor
ViewContext::ViewContext(const ViewContext &other)
    : windowHeight(other.windowHeight), windowWidth(other.windowWidth),
      m(other.m), mInv(other.mInv), 
      transX(other.transX), transY(other.transY), transZ(other.transZ),
      N(other.N)
{
}

// Destructor - no dynamic memory
ViewContext::~ViewContext()
{
}

// Resets to base view transformation
void ViewContext::resetTransformation()
{
    orbH = ROT_DEFAULT;
    orbV = ROT_DEFAULT;

    transX = transY = transZ = 0;
    scale = 1;

    recalculateMatrices();
}

void ViewContext::addHorizontalOrb(double angle) 
{
    orbH+=angle;
    recalculateMatrices();
}

void ViewContext::addVerticalOrb(double angle) 
{
    orbV+=angle;
    recalculateMatrices();
}



// adds specified translation
void ViewContext::addTranslation(double x, double y)
{
    transX += x;
    transY += y;
    recalculateMatrices();
}

// Applies specified scalar
void ViewContext::applyScaling(double s)
{
    scale *= s;
    recalculateMatrices();
}

// convert model coordinates to device coordinates
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

// convert device coordinates to model coordinates
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

// Internal method to recalculate m and mInv
void ViewContext::recalculateMatrices()
{
    // Since we have predefined ways that the transformation will be applied
    // didn't bother with having any dynamic support for different orders of
    // different transofrmations... this is ugly, but it works

    N.x = radius * cos(orbH) * sin(orbV);
    N.y = radius * sin(orbH) * sin(orbV);
    N.z = radius * cos(orbV);

    cout << N;
    vector3d ref(0, 1, 0);
    vector3d n = N.normalize();

    vector3d u = ref.cross(n);
    vector3d v = n.cross(u);

    matrix rot = create3dRotationFromUnitVectors(u, v, n);
    matrix rotInv = create3dRotationFromUnitVectors(
        vector3d(1, 0, 0), vector3d(0, 1, 0), vector3d(0, 0, 1));

    m = translationMatrix(windowWidth / 2.0, windowHeight / 2.0, 0) *
        flipYMatrix() * 
        scalingMatrix(scale) *
        translationMatrix(transX, transY, transZ) *
 //       rotZMatrix(rotation) * 
        rot *
        translationMatrix(-N.x, -N.y, -N.z);

    mInv = translationMatrix(N.x, N.y, N.z) * 
        rotInv * 
//        rotZMatrix(-rotation) *
        translationMatrix(-transX, -transY, -transZ) *
        scalingMatrix(1 / scale) * 
        flipYMatrix() *
        translationMatrix(-windowWidth / 2.0, -windowHeight / 2.0, 0);
}

matrix ViewContext::create3dRotationFromUnitVectors(vector3d u, vector3d v,
                                                    vector3d n)
{
    return matrix(
        4, 4,
        {u.x, v.x, n.x, 0, u.y, v.y, n.y, 0, u.z, v.z, n.z, 0, 0, 0, 0, 1});
}
