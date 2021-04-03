#include "shape.h"
#include "matrix.h"

class line : public shape
{
    public:
        line(int x0, int y0);
        line(line &other);

        virtual line& operator=(line& other);

        virtual void draw(GraphicsContext *context) const;
        virtual void out(std::ostream &outstr) const;
        virtual void in(const std::istream &instr);
        virtual line &clone() const;   

    private:
        matrix coordinates;
};
