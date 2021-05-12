#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_BOUNDINGBOX_H
#define GRAPHITE_BOUNDINGBOX_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

namespace Graphite {

	class GRAPHITE_API BoundingBox final
	{
	public:
		BoundingBox() = default;
		BoundingBox(float width, float height, float depth);
		BoundingBox(float l, float r, float t, float b, float n, float f);
		BoundingBox(std::vector<glm::vec3>& vertexBuffer);
		virtual ~BoundingBox() = default;

		inline glm::vec3 GetDimensions() const { return m_Dimensions; }
	private:
		glm::vec3 m_Dimensions;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif