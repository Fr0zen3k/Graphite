#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_MATH_LINE_H
#define GRAPHITE_MATH_LINE_H

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
			/// <summary>
			/// Constructs a line by defining the point used to position the line and the vector used to orient the line
			/// </summary>
			/// <param name="point"></param>
			/// <param name="vector"></param>
			Line(glm::vec3 point, glm::vec3 vector);
			virtual ~Line() = default;

			/// <returns>a vector of the line used to orient the line</returns>
			inline glm::vec3 GetOrientation() const { return l_Vector; }

			/// <returns>a point of the line used to position the line</returns>
			inline glm::vec3 GetPosition() const override { return l_Point; }

			/// <summary>
			/// Sets the position of the line by given point
			/// </summary>
			/// <param name="point"></param>
			inline void SetPosition(glm::vec3 point) { l_Point = point; }

			/// <summary>
			/// Sets the orientation of the line by given vector
			/// </summary>
			/// <param name="vector"></param>
			inline void SetOrientation(glm::vec3 vector) { l_Vector = vector; }
		};
	}
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif
