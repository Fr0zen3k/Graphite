#pragma once

#ifndef GRAPHITE_TRANSFORM_H
#define GRAPHITE_TRANSFORM_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include "GeoEntity.h"

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API Plain : GeoEntity
		{
		private:
			glm::vec3 p_Point;  // This point is used to set position the plain
			glm::vec3 p_NormalVector;

		public:
			// Construct plain by defining point (position) and vector (orientation)
			Plain(glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 vector = glm::vec3(1.0f, 0.0f, 0.0f));

			// Construct plain by defining 3 points that belong to the plain
			Plain(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
			virtual ~Plain() = default;

			// Returns the normal vector of the plain, it is used to orient the plane
			inline glm::vec3 GetNormalVector() const { return p_NormalVector; }

			// Returns the point which is used to position the plain
			inline glm::vec3 GetPosition() const { return p_Point; }

			// Sets the position of the plain
			inline void SetPosition(glm::vec3 point) { p_Point = point; }

			// Sets the orientation of the plain
			inline void SetNormalVector(glm::vec3 vector) { p_NormalVector = glm::normalize(vector); }
		};
	}
}