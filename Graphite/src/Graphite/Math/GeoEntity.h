#pragma once

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include <glm/glm.hpp>

namespace Graphite
{
	namespace Math
	{
		class GRAPHITE_API GeoEntity
		{
		public:
			GeoEntity();
			virtual ~GeoEntity() = default;
		};
	}
}
