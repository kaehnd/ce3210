/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-03-30 01:24:37
 * @ Description: Test driver of basic graphics context functionality
 */

#include "x11context.h"
#include <cmath> // for trig functions
#include <iostream>
#include <unistd.h>
#define _USE_MATH_DEFINES // for M_PI

static void drawPointAngleLengthLine(GraphicsContext *gc, int x, int y,
                                     int length, int angleDegrees)
{
    gc->drawLine(x, y, x + cos(angleDegrees * M_PI / 180) * length,
                 y + sin(angleDegrees * M_PI / 180) * length);
}

int main(void)
{
    GraphicsContext *gc = new X11Context(800, 600, GraphicsContext::BLACK);

    // fully test methods

    gc->drawCircle(300, 300, 100);

    gc->drawLine(300, 300, 300, 400);
    gc->drawLine(300, 300, 350, 400);
    gc->drawLine(300, 300, 400, 400);
    gc->drawLine(300, 300, 400, 350);

    gc->drawLine(300, 300, 400, 300);
    gc->drawLine(300, 300, 400, 250);
    gc->drawLine(300, 300, 400, 200);
    gc->drawLine(300, 300, 350, 200);

    gc->drawLine(300, 300, 300, 200);
    gc->drawLine(300, 300, 250, 200);
    gc->drawLine(300, 300, 200, 200);
    gc->drawLine(300, 300, 200, 250);

    gc->drawLine(300, 300, 200, 300);
    gc->drawLine(300, 300, 200, 350);
    gc->drawLine(300, 300, 200, 400);
    gc->drawLine(300, 300, 250, 400);

    //test negative coordinates
	gc->drawLine(-200, -2, 50, 50);
	gc->drawCircle(-5, -5, 100);

    sleep(3);
    gc->clear();

    // loading...
    for (int j = 0; j < 2; j++)
    {
        gc->setColor(GraphicsContext::WHITE);
        for (int i = 0; i < 360; i++)
        {
            drawPointAngleLengthLine(gc, 300, 300, 100, i);
            usleep(2000);
        }
        usleep(100000);

        gc->setColor(GraphicsContext::BLACK);

        for (int i = 0; i < 360; i++)
        {
            drawPointAngleLengthLine(gc, 300, 300, 100, i);
            usleep(300);
        }

        usleep(100);
    }

    gc->clear();

    // draw something cool.. I suppose...
    gc->setColor(GraphicsContext::YELLOW);
    for (int i = 180; i >= 0; i--)
    {
        drawPointAngleLengthLine(gc, 300, 300, 100, i);
        drawPointAngleLengthLine(gc, 300, 300, 100, -i);
    }

    for (int j = 0; j < 20; j++)
    {
        gc->setColor(GraphicsContext::BLACK);

        for (int i = 0; i < 45; i++)
        {
            drawPointAngleLengthLine(gc, 300, 300, 100, i);
            drawPointAngleLengthLine(gc, 300, 300, 100, -i);
        }

        gc->setColor(GraphicsContext::YELLOW);

        for (int i = 44; i >= 0; i--)
        {
            drawPointAngleLengthLine(gc, 300, 300, 100, i);
            drawPointAngleLengthLine(gc, 300, 300, 100, -i);
        }
    }

    delete gc;
    return 0;
}
