#include "Graphite/Core/grpch.h"
#include "Sphere.h"
namespace Graphite
{
	namespace Math
	{
		Sphere::Sphere(glm::vec3 point, float radius) : s_Center(point), s_Radius(radius) {};
	}
}