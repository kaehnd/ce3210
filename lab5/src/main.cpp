/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-22 00:35:19
 * @ Description: Test driver of basic graphics context functionality
 */


#include "x11context.h"
#include "eventDrawingInterface.h"

using namespace std;

int main(void)
{
    GraphicsContext *gc = new X11Context(800, 600, GraphicsContext::BLACK);

    eventDrawingInterface interface;
    gc->runLoop(&interface);

    delete gc;
    return 0;
}
