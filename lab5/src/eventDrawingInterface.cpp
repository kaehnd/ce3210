#include "eventDrawingInterface.h"
#include <iostream>

using namespace std;

eventDrawingInterface::~eventDrawingInterface() 
{
    
}

void eventDrawingInterface::paint(GraphicsContext* gc) 
{
    
}

void eventDrawingInterface::keyDown(GraphicsContext* gc, unsigned int keycode) 
{
    cout<<"Key Press detected: "<<keycode<<endl;
}

void eventDrawingInterface::keyUp(GraphicsContext* gc, unsigned int keycode) 
{
    
    cout<<"Key Release detected: "<<keycode<<endl;

}

void eventDrawingInterface::mouseButtonDown(GraphicsContext* gc, 
                                unsigned int button, int x, int y) 
{

    cout<<"Mouse Press detected: ("<<x<<", "<<y<<")"<<endl;
   
}

void eventDrawingInterface::mouseButtonUp(GraphicsContext* gc,
                                unsigned int button, int x, int y) 
{
    cout<<"Mouse Release detected: ("<<x<<", "<<y<<")"<<endl;

    if (isDrawing)
    {
        isDrawing = false;

    } 
    else 
    {
        isDrawing = true;
        
    }
    
}

void eventDrawingInterface::mouseMove(GraphicsContext* gc, int x, int y) 
{
    cout<<"Mouse Move detected: ("<<x<<", "<<y<<")"<<endl;

}
