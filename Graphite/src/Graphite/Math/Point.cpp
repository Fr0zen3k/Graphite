#include "Point.h"

// dal uopce treba point (vektor je zapravo point)
class Point :
    public GeoEntity
{
private:
    float x;
    float y;
    float z;

public:
    // default constructor
    Point(float x = 0, float y = 0, float z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    // constructor for cylinder coordinate system
    Point(float r, float phi, float z) {
        x = r * glm::cos(phi);
        y = r * glm::sin(phi);
        z = z;
    }
    // constructor for sphere coordinate system
    Point(float r, float phi, float theta) {
        x = r * glm::sin(theta) * glm::cos(phi);
        y = r * glm::sin(theta) * glm::sin(phi);
        z = r * glm::cos(theta);
    }
    // constructor for given vector from (0,0,0)
    Point(glm::vec3 v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }

    // returns distance from (0,0,0)
    float abs() { return glm::sqrt(x * x + y * y + z * z); }

    // Override
    template <class T>
    bool contains(T e) {
        if (std::is_base_of(Point, T) && this == e)
            return true;
        return false;
    }
};

//overload operators
inline bool operator==(Point& lhs, Point& rhs) { 
    if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ())
        return true;
    return false;
}
inline bool operator!=(Point& lhs, Point& rhs) { return !(lhs == rhs); }