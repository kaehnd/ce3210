/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-15 08:53:22
 * @ Description: Test driver of basic graphics context functionality
 */

#include "image.h"
#include "line.h"
#include "shape.h"
#include "triangle.h"
#include "x11context.h"
#include "eventDrawingInterface.h"
#include <cmath> // for trig functions
#include <fstream>
#include <iostream>
#include <ostream>
#include <unistd.h>

using namespace std;


int main(void)
{
    GraphicsContext *gc = new X11Context(800, 600, GraphicsContext::BLACK);

    eventDrawingInterface interface;
    gc->runLoop(&interface);

    delete gc;
    return 0;
}
