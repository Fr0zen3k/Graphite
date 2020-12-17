
#include "Plain.h"

class Plain : public GeoEntity
{
private:
	Point a;
	glm::vec3 n;

public:
	Plain(Point a = Point(0,0,0), glm::vec3 n = glm::vec3(0,0,0)) {
		this->a = a;
		this->n = glm::normalize(n);
	}
	Plain(Point a, Point b, Point c) {
		this->a = a;
		glm::vec3 v1 = glm::vec3(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
		glm::vec3 v2 = glm::vec3(a.getX() - c.getX(), c.getY() - c.getY(), c.getZ() - c.getZ());
		this->n = glm::normalize(v1 * v2);
	}

	Point getStartPoint() { return a; }
	glm::vec3 getVectorNormal() { return n;}

};