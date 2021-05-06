#include "vector3d.h"
#include <cmath>
#include <ostream>

vector3d::vector3d(double x, double y, double z) : x(x), y(y), z(z)
{
    
}

double vector3d::mag() const
{
    return sqrt(x*x+y*y+z*z);
}

vector3d vector3d::normalize() const
{
    return (*this)/this->mag();
}

vector3d vector3d::cross(const vector3d & other) const
{
    return vector3d(y*other.z-z*other.y, z*other.x-x*other.z, x*other.y-y*other.x);
}

vector3d vector3d::operator-(const vector3d & other) const
{
    return vector3d(x-other.x, y-other.y, z-other.z);
}

vector3d vector3d::operator/(double scale) const
{
    return vector3d(x/scale, y/scale, z/scale);
}

vector3d vector3d::operator=(const vector3d & other) 
{
    x=other.x;
    y=other.y;
    z=other.z;
    return *this;
}

vector3d vector3d::operator*(double scale) const
{
    return vector3d(x*scale, y*scale, z*scale);
}

vector3d vector3d::operator*(const vector3d & other) const
{
    return vector3d(x*other.x, y*other.y, z*other.z);
}

vector3d vector3d::operator+(const vector3d & other) const
{
    return vector3d(x+other.x, y+other.y, z+other.z);
}




std::ostream& operator<<(std::ostream &os, const vector3d &rhs) 
{
    return os<<"("<<rhs.x<<","<<rhs.y<<","<<rhs.z<<")"<<std::endl;
}