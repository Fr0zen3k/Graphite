#include "Graphite/Core/grpch.h"
#include "BoundingSphere.h"

namespace Graphite {

	BoundingSphere::BoundingSphere(float radius) : m_Radius(radius)
	{

	}

	BoundingSphere::BoundingSphere(std::vector<glm::vec3>& vertexBuffer)
	{
		float maxSize = 0.0f;

		for (glm::vec3 v : vertexBuffer)
		{
			if (glm::length(v) > maxSize)
			{
				maxSize = glm::length(v);
			}
		}

		m_Radius = maxSize;
	}
}