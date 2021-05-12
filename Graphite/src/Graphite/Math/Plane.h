#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_PLANE_H
#define GRAPHITE_PLANE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

namespace Graphite {
	
	class GRAPHITE_API Plane {
	public:
		Plane() = default;
		Plane(const glm::vec3& vector1, const glm::vec3& vector2, const glm::vec3& point);
		Plane(const glm::vec3& normal, const glm::vec3& point);
		Plane(const glm::vec3& normal, float distanceToOrigin);
		virtual ~Plane() = default;

		float Distance(const glm::vec3 & point) const;
		float Distance(const glm::vec4 & point) const;
		float Distance(const glm::mat4x2& lineParameters) const;
		float Distance(const Plane& plane) const;

		bool OnPlane(const glm::vec3& point) const;
		bool OnPlane(const glm::vec4& point) const;
		bool OnPlane(const glm::mat4x2& lineParameters) const;

		bool Parallel(const Plane& plane) const;
		bool Parallel(const glm::mat4x2& lineParameters) const;
		bool Parallel(const glm::vec3 vector) const;
		
	private:
		glm::vec4 m_Parameters{};
	};

}

#endif


#if defined (_MSC_VER)
#pragma warning(pop)
#endif