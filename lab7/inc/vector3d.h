#include <ostream>
class vector3d
{
public:
    
    vector3d(double x, double y, double z);


    double mag() const;
    vector3d normalize() const;

    vector3d cross(const vector3d & other) const;

    vector3d operator-(const vector3d & other) const;
    vector3d operator+(const vector3d & other) const;
    vector3d operator*(const vector3d & other) const;
    vector3d operator*(double scale) const;
    vector3d operator/(double scale) const;

    vector3d operator=(const vector3d & other);

    double x, y, z;

};

std::ostream &operator<<(std::ostream &os, const vector3d &rhs);



