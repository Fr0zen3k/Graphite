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
		class GRAPHITE_API Sphere : GeoEntity
		{
		public:
			// Construct sphere by defining point used to position center of the sphere and radius of the sphere
			Sphere(glm::vec3 point, float radius);
			virtual ~Sphere() = default;

			// Returns the point of the center of the sphere
			inline glm::vec3 GetCenter() const { return s_Center; }

			// Returns the radius of the sphere
			inline float GetRadius() const { return s_Radius; }

			// Sets the position of the center of the sphere by given point
			inline void SetCenter(glm::vec3 point) { s_Center = point; }

			// Sets the radius of the sphere
			inline void SetRadius(float radius) { s_Radius = radius; }

		private:
			glm::vec3 s_Center;
			float s_Radius;
		};
	}
}