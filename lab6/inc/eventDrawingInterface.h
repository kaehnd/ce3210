/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-22 00:25:42
 * @ Description:
 */

#ifndef __EVENTDRAWINGINTERFACE_H__
#define __EVENTDRAWINGINTERFACE_H__

#include "drawbase.h"
#include "image.h"
#include <unordered_set>

// forward reference
class GraphicsContext;

class eventDrawingInterface : public DrawingBase
{

  public:
    /**
     * @brief  Constructs the object
     */
    eventDrawingInterface();

    /**
     * @brief Destructor
     */
    virtual ~eventDrawingInterface();

    /**
     * @brief  Re-draws the current image
     * @param  gc: current GraphicsContext
     */
    virtual void paint(GraphicsContext *gc);

    /**
     * @brief  Called on keypress, implements actions
     * @param  gc: current GraphicsContext
     * @param  keycode: key that was pressed
     */
    virtual void keyDown(GraphicsContext *gc, unsigned int keycode);

    /**
     * @brief  Called on keyup
     * @param  gc: current GraphicsContext
     * @param  keycode:
     */
    virtual void keyUp(GraphicsContext *gc, unsigned int keycode);

    /**
     * @brief  Called on mouse click
     * @param  gc: current GraphicsContext
     * @param  button: button clicked
     * @param  x: x position of mouse
     * @param  y: y position of mouse
     */
    virtual void mouseButtonDown(GraphicsContext *gc, unsigned int button,
                                 int x, int y);

    /**
     * @brief  Called on mouse unclick, implements drawing
     * @param  gc: current GraphicsContext
     * @param  button: button clicked
     * @param  x: x position of mouse
     * @param  y: y position of mouse
     */
    virtual void mouseButtonUp(GraphicsContext *gc, unsigned int button, int x,
                               int y);

    /**
     * @brief  Called on mouse move, implements rubberbanding
     * @param  gc: current GraphicsContext
     * @param  x: x position of mouse
     * @param  y: y position of mouse
     */
    virtual void mouseMove(GraphicsContext *gc, int x, int y);

  private:
    image im;

    // thought about using polymorphism for this...
    // started to use polymorphism for this...
    // ended up having to hard code most of the cases anyways..
    // went back to doing it this way :()
    matrix points;
    int curNumPoints;
    int numPointsToGet;

    unsigned int curColor;
    std::unordered_set<unsigned int> pressedKeys;

    // undraws/draws lines between most recent point, second-most recent point,
    // and beginning point
    void progressivelyDrawLinearShape(GraphicsContext *gc);

    // stops drawing, called when ESC is pressed
    void abandonDrawing(GraphicsContext *gc);

    // Saves to hard-coded file
    void saveImage();

    // Loads from hard-coded file
    void loadImage(GraphicsContext *gc);

    // Gets if specified key is currently held down
    bool isKeyPressed(unsigned int keycode);
};

#endif // __EVENTDRAWINGINTERFACE_H__