#pragma once

#include "Graphite/Core/grpch.h"
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API GeoEntity
		{
		public:
			GeoEntity();
			virtual ~GeoEntity() = default;

			GetPosition();
		};
	}
}
