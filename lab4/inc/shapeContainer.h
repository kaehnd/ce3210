#include "shape.h"
#include <vector>
#include <iostream>

class shapeContainer
{
    public:
        shapeContainer();
        shapeContainer(shapeContainer& other);
        ~shapeContainer();

        shapeContainer& operator=(shapeContainer& other);
        void add(shape* shape);
        void draw(GraphicsContext* context);
        void out(std::ostream & outstr);
        void in(std::istream & instr);
        void erase();
};