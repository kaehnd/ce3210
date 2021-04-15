#ifndef __EVENTDRAWINGINTERFACE_H__
#define __EVENTDRAWINGINTERFACE_H__

#include "drawbase.h"

// forward reference
class GraphicsContext;

class eventDrawingInterface : public DrawingBase
{
	public:
		// prevent warnings
		virtual ~eventDrawingInterface();
		virtual void paint(GraphicsContext* gc);
		virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
		virtual void keyUp(GraphicsContext* gc, unsigned int keycode);
		virtual void mouseButtonDown(GraphicsContext* gc, 
								unsigned int button, int x, int y);
		virtual void mouseButtonUp(GraphicsContext* gc,
								unsigned int button, int x, int y);
		virtual void mouseMove(GraphicsContext* gc, int x, int y);

    private:
        bool isDrawing;
};

#endif // __EVENTDRAWINGINTERFACE_H__