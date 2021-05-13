/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-05-12 20:33:56
 * @ Description: Implementation of event handling
 */

#include "eventDrawingInterface.h"
#include "triangle.h"
#include "vcontext.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

#define KEY_CTRL 65507
#define KEY_ESC 65307
#define KEY_SHIFT 65505

using namespace std;

// Constructor
eventDrawingInterface::eventDrawingInterface(GraphicsContext *gc)
    : points(4, 3), curNumPoints(0), numPointsToGet(3), // default to triangle
      curColor(GraphicsContext::CYAN), isMouseLeftClicked(false), isMouseMiddleClicked(false), isMouseRightClicked(false)
{
    vc = new ViewContext(gc->getWindowHeight(), gc->getWindowWidth());

    for (unsigned int i = 0; i < 3; i++)
    {
        points[3][i] = 1; // set bottom row to 1
    }
}

// Destructor
eventDrawingInterface::~eventDrawingInterface()
{
    delete vc;
}

// Re-draws current image
void eventDrawingInterface::paint(GraphicsContext *gc)
{
    gc->clear();
    triangle(gc->RED,0, 0, 0, 100, 0, 0, 0, 0, 0).draw(gc, vc);
    triangle(gc->BLUE,0, 0, 0, 0, 100, 0, 0, 0, 0).draw(gc, vc);
    triangle(gc->GREEN,0, 0, 0, 0, 0, 100, 0, 0, 0).draw(gc, vc);

    im.draw(gc, vc);
}

// Called on keypress, implements actions
void eventDrawingInterface::keyDown(GraphicsContext *gc, unsigned int keycode)
{
    pressedKeys.insert(keycode);
    //cout<<"keypress: "<<keycode<<endl;
    switch (keycode)
    {
    case KEY_ESC:
        break;
    case 's':
        if (isKeyPressed(KEY_CTRL))
        {
            saveImage();
        }
        else
        {
            vc->addTranslation(0, 4);
            paint(gc);
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
            im.erase();
            vc->resetTransformation();
            paint(gc);
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
    case 'w':
        vc->addTranslation(0, -4);
        paint(gc);
        break;
    case 'a':
        vc->addTranslation(4, 0);
        paint(gc);
        break;
    case 'd':
        vc->addTranslation(-4, 0);
        paint(gc);
        break;
    case '=':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->applyScaling(1.2);
            paint(gc);
        }
        break;
    case '-':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->applyScaling(.8);
            paint(gc);
        }
        break;

    case '.':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addHorizontalOrb(.1);
            paint(gc);
        }

        break;
    case ',':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addVerticalOrb(.1);
            paint(gc);
        }
        break;
    case '>':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addHorizontalOrb(-.1);
            paint(gc);
        }

        break;
    case '<':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addVerticalOrb(-.1);
            paint(gc);
        }
        break;
    case 'r':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->resetTransformation();
            paint(gc);
        }
        break;
    case ';':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addFov(1);
            paint(gc);
        }
        break;
    case '\'':
        if (isKeyPressed(KEY_CTRL))
        {
            vc->addFov(-1);
            paint(gc);
        }
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
    cout<<"Mouse down: "<<button<<endl;
    switch (button)
    {
        case 1:
            isMouseLeftClicked = true;
            break;
        case 2:
            isMouseMiddleClicked = true;
            break;
        case 3:
            isMouseRightClicked = true;
            break;
        case 4:
            if (isKeyPressed(KEY_CTRL))
            {
                vc->applyScaling(1.2);
                paint(gc);
            }
            break;
        case 5:
            if (isKeyPressed(KEY_CTRL))
            {
                vc->applyScaling(.8);
                paint(gc);
            }
            break;
    }
}

// called on mouse unclick
void eventDrawingInterface::mouseButtonUp(GraphicsContext *gc,
                                          unsigned int button, int x, int y)
{
    //cout<<"Mouse up: " << button<<endl;
    switch (button)
    {
        case 1:
            isMouseLeftClicked = false;
            break;
        case 2:
            isMouseMiddleClicked = false;
            break;
        case 3:
            isMouseRightClicked = false;
            break;
    }

}

// called on mouse move, implements rubberbanding
void eventDrawingInterface::mouseMove(GraphicsContext *gc, int x, int y)
{

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
    vc->resetTransformation();
    cout << "Loading.." << endl;
    fstream file(".svproj.stl");

    im.erase();
    im.in(file, curColor);
    file.close();
    paint(gc);
    cout << "Load successful!" << endl;
}

// Gets if specified key is currently held down
bool eventDrawingInterface::isKeyPressed(unsigned int keycode)
{
    return pressedKeys.find(keycode) != pressedKeys.end();
}
