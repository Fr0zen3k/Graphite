#include "Graphite/Core/grpch.h"
#include "Box.h"
namespace Graphite
{
	namespace Math
	{
		Box::Box(glm::vec3 size, glm::vec3 position, Transform transformation = Transform()) : b_Transformation(transformation)
		{
			b_Transformation.Translate(position);
			b_Vertex = size * 0.5;
		}

 		// 2nd way of defining a box: point (one vertex of the box) and 3 vectors which define 3 edges from the given point
		// 3rd way: point (one vertex), vector which is pointing to the opposing vertex (the one which is not neighbor to the neighbor sides of the given vertex), angle of rotation around given vector
		// these are ways with sufficient data because opposing sides are not distinguishable, but not very practical imho
	}
}