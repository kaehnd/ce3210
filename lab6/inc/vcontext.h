#ifndef __VCONTEXT_H__
#define __VCONTEXT_H__

/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 20:17:33
 * @ Description:
 */

#include "matrix.h"
#include "gcontext.h"
#include <vector>


class ViewContext
{
  public:
    ViewContext(int windowHeight, int windowWidth);
    ViewContext(const ViewContext &other);

    virtual ~ViewContext();


    virtual void resetTransformation();

    virtual void addRotation(double angle);
    virtual void addTranslation(double x, double y);
    virtual void addScaling(double s);
 

    virtual matrix modelToDevice(const matrix & coordinates);
    virtual matrix deviceToModel(const matrix & coordinates);


  private:

    int windowHeight;
    int windowWidth;

    matrix m;
    matrix mInv;

    double rotation;
    double transX, transY, transZ;
    double scale;

    void recalculateMatrices();
    void postAddTransformation(const matrix & tran, const matrix & invTran);
    void preAddTransformation(const matrix & tran, const matrix & invTran);
};
#endif // __VCONTEXT_H__