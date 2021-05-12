#include "Graphite/Core/grpch.h"
#include "BoundingBox.h"

namespace Graphite {

	inline BoundingBox::BoundingBox(float width, float height, float depth): m_Dimensions(glm::vec3(width, height, depth))
	{
	}

	inline BoundingBox::BoundingBox(float l, float r, float t, float b, float n, float f): m_Dimensions(glm::vec3(l-r, t-b, f-n))
	{
	}

	inline BoundingBox::BoundingBox(std::vector<glm::vec3>& vertexBuffer)
	{
		glm::vec3 min(0);
		glm::vec3 max(0);

		for(glm::vec3 v : vertexBuffer)
		{
			if(v.x < min.x)
			{
				min.x = v.x;
			}

			if(v.y < min.y)
			{
				min.y = v.y;
			}

			if(v.z < min.z)
			{
				min.z = v.z;
			}

			if (v.x > max.x)
			{
				max.x = v.x;
			}

			if (v.y > max.y)
			{
				max.y = v.y;
			}

			if (v.z > max.z)
			{
				max.z = v.z;
			}
		}

		m_Dimensions = max - min;
	}

}