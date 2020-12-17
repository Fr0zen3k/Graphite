#pragma once
#include "GeoEntity.h"

class Point :
    public GeoEntity
{
private:
    float x;
    float y;
    float z;

public:
    Point(float x, float y, float z);
    Point(float r, float phi, float z);
    Point(float r, float phi, float theta);
    float getX();
    float getY();
    float getZ();
    float abs();

    // Override
    template <class T> bool contains(T e);
};

//overload operators
inline bool operator==(Point& lhs, Point& rhs);
inline bool operator!=(Point& lhs, Point& rhs);
