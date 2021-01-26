#include "Graphite/Core/grpch.h"
#include "Plain.h"

namespace Graphite
{
	namespace Math
	{
		Plain::Plain(glm::vec3 point, glm::vec3 vector) : p_Point(point)
		{
			p_NormalVector = glm::normalize(vector);
		}

		Plain::Plain(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3) : p_Point(point1)
		{
			p_NormalVector = glm::normalize((point1 - point2) * (point1 - point3));
		}

		int Plain::Facing(glm::vec3 point) 
		{
			float angle = glm::angle(p_NormalVector, glm::normalize(point - p_Point));
			if (glm::abs(angle) < FLT_EPSILON)
				return 0;
			else if (glm::abs(glm::abs(angle) - 90.0f) < FLT_EPSILON)
				return 1;
			else
				return -1;
		}
	}
}
