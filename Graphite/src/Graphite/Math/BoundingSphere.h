#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_BOUNDINGSPHERE_H
#define GRAPHITE_BOUNDINGSPHERE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

namespace Graphite {

	class GRAPHITE_API BoundingSphere
	{
	public:
		BoundingSphere() = default;
		BoundingSphere(float radius);
		BoundingSphere(std::vector<glm::vec3>& vertexBuffer);
		virtual ~BoundingSphere() = default;

		inline float GetRadius() const { return m_Radius; }

	private:
		float m_Radius = 0.0f;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif