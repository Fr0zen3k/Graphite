#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_VIEWFRUSTUM_H
#define GRAPHITE_VIEWFRUSTUM_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "glm/glm.hpp"

#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Plane.h"

namespace Graphite
{
	class GRAPHITE_API ViewFrustum
	{
	public:
		inline static ViewFrustum OrthographicFrustum(float t, float b, float l, float r, float n, float f) { return ViewFrustum(t, b, l, r, n, f); }
		inline static ViewFrustum PerspectiveFrustim(float aspect, float fov, float nearPlane, float farPlane) { return ViewFrustum(aspect, fov, nearPlane, farPlane); }

		virtual ~ViewFrustum() = default;

		bool Check(const BoundingBox& boundingBox, const glm::mat4& transformMatrix) const;
		bool Check(const BoundingSphere& boundingSphere, const glm::vec3& position) const;
		bool Check(const glm::vec3& point) const;
		
	protected:
		ViewFrustum() = default;
		ViewFrustum(float t, float b, float l, float r, float n, float f);
		ViewFrustum(float aspect, float fov, float nearPlane, float farPlane);
		
	private:
		void Init(Plane topPlane, Plane bottomPlane, Plane leftPlane, Plane rightPlane, Plane nearPlane, Plane farPlane);

	private:
		Plane m_Top;
		Plane m_Bottom;
		Plane m_Left;
		Plane m_Right;
		Plane m_Near;
		Plane m_Far;
		
	};
}

#endif


#if defined (_MSC_VER)
#pragma warning(pop)
#endif