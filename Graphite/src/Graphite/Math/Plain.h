#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif


#ifndef GRAPHITE_PLAIN_H
#define GRAPHITE_PLAIN_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>
#include "GeoEntity.h"
#include <glm/gtx/vector_angle.hpp>

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API Plain : GeoEntity
		{
		private:
			glm::vec3 p_Point;  // This point is used to set the position of the plain
			glm::vec3 p_NormalVector;

		public:
			/// <summary>
			/// Construct plain by defining point (position) and vector (orientation)
			/// </summary>
			/// <param name="point">used for position</param>
			/// <param name="vector">normal vector of the plain, used for orientation (direction)</param>
			Plain(glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 vector = glm::vec3(1.0f, 0.0f, 0.0f));

			/// <summary>
			/// Construct plain by defining 3 points that belong to the plain
			/// </summary>
			/// <param name="point1">used for position</param>
			/// <param name="point2"></param>
			/// <param name="point3"></param>
			Plain(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
			virtual ~Plain() = default;

			/// <returns>the normal vector of the plain, it is used to orient the plane</returns>
			inline glm::vec3 GetNormalVector() const { return p_NormalVector; }

			/// <returns>a point which is used to position the plain</returns>
			inline glm::vec3 GetPosition() const override { return p_Point; }

			/// <summary>
			/// Sets the position of the plain
			/// </summary>
			/// <param name="point"></param>
			inline void SetPosition(glm::vec3 point) { p_Point = point; }

			/// <summary>
			/// Sets the orientation of the plain
			/// </summary>
			/// <param name="vector"></param>
			inline void SetNormalVector(glm::vec3 vector) { p_NormalVector = glm::normalize(vector); }

			/// <summary>
			/// Check if the point belongs to the plain, or on which side of the plain is the given point
			/// </summary>
			/// <param name="point"></param>
			/// <returns> 1 if plain is facing given point (normal vector of the plain points in direction of the given point), 0 if plain contains the point and -1 if the point is on other side</returns>
			int Facing(glm::vec3 point);
		};
	}
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif