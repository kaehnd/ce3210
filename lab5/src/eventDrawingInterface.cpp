/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-22 00:25:34
 * @ Description: Implementation of event handling
 */

#include "eventDrawingInterface.h"
#include "line.h"
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

#define KEY_CTRL 65507
#define KEY_ESC 65307

using namespace std;

// Constructor
eventDrawingInterface::eventDrawingInterface()
    : points(2, 3), curNumPoints(0), numPointsToGet(3), // default to triangle
      curColor(GraphicsContext::CYAN)
{
}

// Destructor
eventDrawingInterface::~eventDrawingInterface()
{
}

// Re-draws current image
void eventDrawingInterface::paint(GraphicsContext *gc)
{
    im.draw(gc);
}

// Called on keypress, implements actions
void eventDrawingInterface::keyDown(GraphicsContext *gc, unsigned int keycode)
{
    pressedKeys.insert(keycode);
    switch (keycode)
    {
    case 'l':
        cout << "draw liness" << endl;
        numPointsToGet = 2;
        break;
    case 't':
        cout << "draw triangless" << endl;
        numPointsToGet = 3;
        break;
    case KEY_ESC:
        abandonDrawing(gc);
        break;
    case 's':
        if (isKeyPressed(KEY_CTRL))
        {
            saveImage();
        }
        break;
    case 'o':
        if (isKeyPressed(KEY_CTRL))
        {
            loadImage(gc);
        }
        break;
    case 'n':
        if (isKeyPressed(KEY_CTRL))
        {
            gc->clear();
            im.erase();
        }
        break;
    case '1':
        curColor = GraphicsContext::WHITE;
        break;
    case '2':
        curColor = GraphicsContext::BLUE;
        break;
    case '3':
        curColor = GraphicsContext::CYAN;
        break;
    case '4':
        curColor = GraphicsContext::GRAY;
        break;
    case '5':
        curColor = GraphicsContext::GREEN;
        break;
    case '6':
        curColor = GraphicsContext::MAGENTA;
        break;
    case '7':
        curColor = GraphicsContext::RED;
        break;
    case '8':
        curColor = GraphicsContext::YELLOW;
        break;
    case '9':
        curColor = GraphicsContext::BLACK;
        break;
    }
}

// Called on keyup
void eventDrawingInterface::keyUp(GraphicsContext *gc, unsigned int keycode)
{
    pressedKeys.erase(keycode);
}

// called on mouse click
void eventDrawingInterface::mouseButtonDown(GraphicsContext *gc,
                                            unsigned int button, int x, int y)
{
}

// called on mouse unclick
void eventDrawingInterface::mouseButtonUp(GraphicsContext *gc,
                                          unsigned int button, int x, int y)
{
    if (curNumPoints > 0)
    {
        points[0][curNumPoints] = x;
        points[1][curNumPoints] = y;

        if (curNumPoints + 1 == numPointsToGet)
        {
            switch (numPointsToGet)
            {
            case 2:
                im.add(new line(curColor, points));
                break;
            case 3:
                im.add(new triangle(curColor, points));
                break;
            }

            curNumPoints = 0;
            gc->setMode(GraphicsContext::MODE_NORMAL);
        }
        else
        {
            progressivelyDrawLinearShape(gc);
            curNumPoints++;
            points[0][curNumPoints] = x;
            points[1][curNumPoints] = y;
        }
    }
    else
    {
        points[0][curNumPoints] = points[0][curNumPoints + 1] = x;
        points[1][curNumPoints] = points[1][curNumPoints + 1] = y;
        gc->setMode(GraphicsContext::MODE_XOR);
        curNumPoints = 1;
    }
}

// called on mouse move, implements rubberbanding
void eventDrawingInterface::mouseMove(GraphicsContext *gc, int x, int y)
{
    if (curNumPoints > 0)
    {
        progressivelyDrawLinearShape(gc);
        points[0][curNumPoints] = x;
        points[1][curNumPoints] = y;
        progressivelyDrawLinearShape(gc);
    }
}

// undraws/draws lines between most recent point, second-most recent point, and
// beginning point
void eventDrawingInterface::progressivelyDrawLinearShape(GraphicsContext *gc)
{
    gc->setColor(curColor);
    gc->drawLine(points[0][curNumPoints - 1], points[1][curNumPoints - 1],
                 points[0][curNumPoints], points[1][curNumPoints]);

    if (curNumPoints > 1)
    {
        gc->drawLine(points[0][0], points[1][0], points[0][curNumPoints],
                     points[1][curNumPoints]);
    }
}

// stops drawing, called when ESC is pressed
void eventDrawingInterface::abandonDrawing(GraphicsContext *gc)
{
    while (curNumPoints > 0)
    {
        progressivelyDrawLinearShape(gc);
        curNumPoints--;
        gc->setPixel(points[0][curNumPoints], points[1][curNumPoints]);
    }
    gc->setMode(GraphicsContext::MODE_NORMAL);
}

// Saves to hard-coded file
void eventDrawingInterface::saveImage()
{
    cout << "Saving.." << endl;

    try
    {
        ofstream file(".svproj.stl");
        im.out(file);
        file.close();
    }
    catch (unsupportedShapeOperationException &ex)
    {
        cout << "SAVE FAILED: Cannot save drawings with this kind of shape"
             << endl;
    }
    cout << "Save successful!" << endl;
}

// Loads from hard-coded file
void eventDrawingInterface::loadImage(GraphicsContext *gc)
{
    cout << "Loading.." << endl;
    fstream file(".svproj.stl");

    im.erase();
    im.in(file, curColor);
    file.close();
    gc->clear();
    im.draw(gc);
    cout << "Load successful!" << endl;
}

// Gets if specified key is currently held down
bool eventDrawingInterface::isKeyPressed(unsigned int keycode)
{
    return pressedKeys.find(keycode) != pressedKeys.end();
}
