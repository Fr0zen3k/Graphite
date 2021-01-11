#include "Graphite/Core/grpch.h"
#include "Plain.h"

namespace Graphite
{
	namespace Math
	{
		Plain::Plain(glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 vector = glm::vec3(1.0f, 0.0f, 0.0f)) : p_Point(point) 
		{
			p_NormalVector = glm::normalize(vector);
		}

		Plain::Plain(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3) : p_Point(point1)
		{
			p_NormalVector = glm::normalize((point1 - point2) * (point1 - point3));
		}
	}
}
