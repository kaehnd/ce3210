/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-03-30 01:28:20
 * @ Description: Implementation of graphics context destructor, and
        default drawLine, drawCircle, and endLoop
 */

/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#include "gcontext.h"
#include <cmath> // for trig functions
#include <limits>

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
    // nothing to do
    // here to insure subclasses handle destruction properly
}

/* Implements Bresenham's line algorithm
 *
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 *
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    float slope =
        dx == 0 ? std::numeric_limits<float>::quiet_NaN() : ((float)dy) / dx;

    if ((dx < 0 && dy < 0) || (dx < 0 && dy > 0 && slope < -1) ||
        (dx > 0 && dy < 0 && slope >= -1))
    {
        drawLine(x1, y1, x0, y0); // swap 0 coord with 1 coord
        return;
    }

    bool decrement = (dx < 0 || dy < 0); // whether to move from right to left
    bool swapItVar = slope < -1 || slope > 1 ||
                     std::isnan(slope); // whether to iterate along y

    int toIncrement = decrement ? -1 : 1;
    int dItVar = swapItVar ? dy : dx;
    int dFuncVar = swapItVar ? dx : dy;

    if (decrement)
    {
        dItVar = -dItVar;
    }

    int x = x0;
    int y = y0;

    // set up reference variables to x and y to abstract the iteration
    int &itVar = swapItVar ? y : x;
    int &funcVar = swapItVar ? x : y;
    int itVarBound = swapItVar ? y1 : x1;

    int di = 2 * dFuncVar - dItVar;

    for (; (decrement && itVar > itVarBound) ||
           (!decrement && itVar < itVarBound);
         itVar += toIncrement)
    {
        funcVar = di < 0 ? funcVar : funcVar + 1;
        setPixel(x, y);
        di = di >= 0 ? di + 2 * (dFuncVar - dItVar) : di + 2 * dFuncVar;
    }
}

/* Implements Midpoint circle algorithm
 *
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 *
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	if (radius <= 0) return;
    int p = 1 - radius;
    int y = radius;

    for (int x = 0; y > x; x++)
    {
        y = p < 0 ? y : y - 1;
        setPixel(x0 + x, y0 + y);
        setPixel(x0 + x, y0 - y);
        setPixel(x0 - x, y0 + y);
        setPixel(x0 - x, y0 - y);
        setPixel(x0 + y, y0 + x);
        setPixel(x0 - y, y0 + x);
        setPixel(x0 + y, y0 - x);
        setPixel(x0 - y, y0 - x);
        p = p < 0 ? p + 2 * x + 1 : p + 2 * (x - y) + 1;
    }
}

void GraphicsContext::endLoop() { run = false; }
