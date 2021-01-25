#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_GEOENTITY_H
#define GRAPHITE_GEOENTITY_H

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

			virtual glm::vec3 GetPosition() const = 0;
		};
	}
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif
