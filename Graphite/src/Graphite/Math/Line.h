#pragma once

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include "GeoEntity.h"

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API Line : GeoEntity
		{
		private:
			glm::vec3 l_Point;
			glm::vec3 l_Vector;

		public:
			// Constructs a line by defining the point used to position the line and the vector used to orient the line
			Line(glm::vec3 point, glm::vec3 vector);
			virtual ~Line() = default;
			
			// Returns a vector of the line used to orient the line
			inline glm::vec3 GetOrientation() const { return l_Vector; }

			// Returns a point of the line used to position the line
			inline glm::vec3 GetPosition() const { return l_Point; }

			// Sets the position of the line by given point
			inline void SetPosition(glm::vec3 point) { l_Point = point; }

			// Sets the orientation of the line by given vector
			inline void SetOrientation(glm::vec3 vector{ l_Vector = vector; }
		};
	}
}
