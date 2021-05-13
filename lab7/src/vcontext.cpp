/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-05-12 20:44:27
 * @ Description: Implements ViewContext wrapper around matrix for view
 * @ Modified by: Daniel Kaehn
 */

#include "vcontext.h"
#include "gcontext.h"
#include "matrix.h"

#include <cmath>
#include <iostream>

#define USE_MATH_DEFINES

#define ROT_DEFAULT M_PI_4
#define FOV_DEFAULT 300

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
#define projectionMatrix(zf)                                                   \
    matrix(4, 4, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1.0 / zf, 1})
// Constructor
ViewContext::ViewContext(int windowHeight, int windowWidth)
    : windowHeight(windowHeight), windowWidth(windowWidth), m(4, 4), mInv(4, 4),
      transX(0), transY(0), transZ(0), scale(0), N(0, 0, 0), orbH(ROT_DEFAULT),
      orbV(ROT_DEFAULT), radius(10), fovDistance(FOV_DEFAULT)
{
    resetTransformation();
}

// Copy contstructor
ViewContext::ViewContext(const ViewContext &other)
    : windowHeight(other.windowHeight), windowWidth(other.windowWidth),
      m(other.m), mInv(other.mInv), transX(other.transX), transY(other.transY),
      transZ(other.transZ), N(other.N), fovDistance(other.fovDistance)
{
}
void ViewContext::setCenter(int windowHeight, int windowWidth)
{
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    recalculateMatrices();
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
    fovDistance = FOV_DEFAULT;

    recalculateMatrices();
}

void ViewContext::addHorizontalOrb(double angle)
{
    orbH += angle;
    orbH = fmod(2 * M_PI + fmod(orbH, 2 * M_PI), 2 * M_PI);
    recalculateMatrices();
}

void ViewContext::addVerticalOrb(double angle)
{
    orbV += angle;
    orbV = fmod(2 * M_PI + fmod(orbV, 2 * M_PI), 2 * M_PI);
    recalculateMatrices();
}
void ViewContext::addFov(double amount)
{
    fovDistance += amount;
    cout << fovDistance;
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
    // cout<<toReturn<<endl;
    toReturn = toReturn.divColByRow(3);
    // cout<<toReturn<<endl;

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

    N.x = radius * sin(orbH) * cos(orbV);
    N.y = radius * sin(orbV);
    N.z = radius * cos(orbH) * cos(orbV);

    // cout<<orbH<<endl;
    // cout << orbV << endl;

    // cout << N;
    vector3d n = N.normalize();

    // double divPi = orbV / M_PI * 2;
    // double mod = fmod(divPi, 2);
    // double absolute = abs(mod);
    // double minus1 = absolute - 1;
    // bool isIllegalView = minus1 < 0.05 && minus1 > -0.05;

    vector3d u, v, ref;

    // cout<<"divPi: " <<divPi<<endl;
    // cout<< "minus1: " << minus1 << endl;
    // cout<<"is illegal: " << isIllegalView<< endl;
    // if (!isIllegalView)
    // {
    //     vector3d ref = vector3d(0, 1, 0);
    //     u = ref.cross(n).normalize();
    //     v = n.cross(u);
    // }
    // else {

    if (orbV > M_PI_2 && orbV < 3 * M_PI_2)
    {
        ref = vector3d(0, -1, 0);
    }
    else
    {
        ref = vector3d(0, 1, 0);
    }
    u = ref.cross(n).normalize();
    v = n.cross(u);
    // }

    // cout << "N: " << N << endl
    //      << "u: " << u << endl
    //      << "v: " << v << endl
    //      << "n: " << n << endl;

    matrix rot = create3dRotationFromUnitVectors(u, v, n);
    matrix rotInv = create3dRotationFromUnitVectors(
        vector3d(1, 0, 0), vector3d(0, 1, 0), vector3d(0, 0, 1));

    m = translationMatrix(windowWidth / 2.0, windowHeight / 2.0, 0) *
        flipYMatrix() * scalingMatrix(scale) *
        translationMatrix(transX, transY, transZ) *
        projectionMatrix(fovDistance) * rot *
        translationMatrix(-N.x, -N.y, -N.z);
}

matrix ViewContext::create3dRotationFromUnitVectors(vector3d u, vector3d v,
                                                    vector3d n)
{
    return matrix(
        4, 4,
        //       {u.x, v.x, n.x, 0, u.y, v.y, n.y, 0, u.z, v.z, n.z, 0, 0, 0, 0,
        //       1});
        {u.x, u.y, u.z, 0, v.x, v.y, v.z, 0, n.x, n.y, n.z, 0, 0, 0, 0, 1});
}
