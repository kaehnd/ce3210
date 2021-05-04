#ifndef __VCONTEXT_H__
#define __VCONTEXT_H__

/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 20:17:33
 * @ Description: ViewContext class to represent transofrmations between device
 * and model coordinates
 */

#include "gcontext.h"
#include "matrix.h"
#include <vector>

class ViewContext
{
  public:
    /**
     * @brief  Constructs a ViewContext
     * @param  windowHeight: height in pixels of view
     * @param  windowWidth: width in pixels of view
     */
    ViewContext(int windowHeight, int windowWidth);

    /**
     * @brief  Copy constructor for ViewContext
     * @param  other: ViewContext to copy from
     */
    ViewContext(const ViewContext &other);

    /**
     * @brief  Destructs the ViewContext
     */
    virtual ~ViewContext();

    /**
     * @brief  Resets to base view transformation
     */
    virtual void resetTransformation();

    /**
     * @brief  Adds the specified rotation to the ViewContext
     * @param  angle: Angle in radians to add
     */
    virtual void addRotation(double angle);

    /**
     * @brief  Adds the specified translation to the ViewContext
     * @param  x: x translation amount
     * @param  y: y translation amount
     */
    virtual void addTranslation(double x, double y);

    /**
     * @brief  Applies scaling to the ViewContext
     * @param  s: Amount the current scale should be scaled by
     */
    virtual void applyScaling(double s);

    /**
     * @brief  Convert model coordinates to device coordinates
     * @param  coordinates: matrix of model coordinates
     * @retval matrix of device coordinates
     */
    virtual matrix modelToDevice(const matrix &coordinates);

    /**
     * @brief  Convert device coordinates to model coordinates
     * @param  coordinates: matrix of device coordinates
     * @retval matrix of model coordinates
     */
    virtual matrix deviceToModel(const matrix &coordinates);

  private:
    int windowHeight;
    int windowWidth;

    matrix m;
    matrix mInv;

    double rotation;
    double transX, transY, transZ;
    double scale;

    /**
     * @brief  Internal method to recalculate m and mInv
     */
    void recalculateMatrices();
};
#endif // __VCONTEXT_H__