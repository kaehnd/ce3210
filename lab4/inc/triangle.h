#include "shape.h"

class triangle : public shape
{
    public:
        triangle();
        triangle(triangle& other);
        ~triangle();
        virtual triangle& operator=(triangle& other);
        virtual void draw(GraphicsContext *context) const;
        virtual void out(std::ostream &outstr) const;
        virtual void in(const std::istream &instr);
        virtual triangle &clone() const;
};
