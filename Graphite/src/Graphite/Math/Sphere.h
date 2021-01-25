#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_SPHERE_H
#define GRAPHITE_SPHERE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include <glm/glm.hpp>
#include "GeoEntity.h"

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API Sphere : GeoEntity
		{
		public:
			/// <summary>
			/// Construct sphere by defining point used to position center of the sphere and radius of the sphere
			/// </summary>
			/// <param name="point"></param>
			/// <param name="radius"></param>
			Sphere(glm::vec3 point, float radius) : s_Center(point), s_Radius(radius) {};
			virtual ~Sphere() = default;

			/// <returns>a point of the center of the sphere</returns>
			inline glm::vec3 GetPosition() const override { return s_Center; }

			/// <returns>radius of the sphere</returns>
			inline float GetRadius() const { return s_Radius; }

			/// <summary>
			/// Sets the position of the center of the sphere by given point
			/// </summary>
			/// <param name="point"></param>
			inline void SetPosition(glm::vec3 point) { s_Center = point; }

			/// <summary>
			/// Sets the radius of the sphere
			/// </summary>
			/// <param name="radius"></param>
			inline void SetRadius(float radius) { s_Radius = radius; }

		private:
			glm::vec3 s_Center;
			float s_Radius;
		};
	}
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif