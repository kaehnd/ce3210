#include "gcontext.h"
#include "matrix.h"
#include <iostream>
class shape
{
  public:
    shape(unsigned int coordRows = 4, unsigned int coordCols = 1);
    shape(shape &other);
    ~shape();

    virtual void draw(GraphicsContext *context) const;
    virtual void out(std::ostream &outstr) const;
    virtual void in(const std::istream &instr);
    virtual shape &clone() const;

  protected:
    virtual shape &operator=(shape &other);
    matrix& getCoordinates();

  private:
    uint32_t color;
    matrix coordinates;
};
