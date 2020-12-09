#pragma once
#include "GeoEntity.h"
#include "Point.h"


class Plain : public GeoEntity
{
private:
	Point a;
	glm::vec3 n;

public:
	Plain(Point a, glm::vec3 n);
	Plain(Point a, Point b, Point c);
	
	glm::vec3 getVectorNormal();
	Point getStartPoint();
};