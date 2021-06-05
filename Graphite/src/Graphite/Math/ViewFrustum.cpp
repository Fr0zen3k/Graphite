#include "Graphite/Core/grpch.h"
#include "ViewFrustum.h"

namespace Graphite
{

	ViewFrustum::ViewFrustum(const glm::mat4& projection)
	{
		glm::mat4 inverse = glm::inverse(projection);

		glm::vec4 p1, p2, p3;

		// Near
		p1 = inverse * glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
		p2 = inverse * glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
		p3 = inverse * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Near = Plane(p2 - p1, p3 - p1, p1);

		// Far
		p1 = inverse * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
		p2 = inverse * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
		p3 = inverse * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Far = Plane(p3 - p1, p2 - p1, p1);

		// Left
		p1 = inverse * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
		p2 = inverse * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
		p3 = inverse * glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Left = Plane(p2 - p1, p3 - p1, p1);

		// Right
		p1 = inverse * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		p2 = inverse * glm::vec4(1.0f, -1.0f, 0.0f, 1.0f);
		p3 = inverse * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Right = Plane(p2 - p1, p3 - p1, p1);

		// Bottom
		p1 = inverse * glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
		p2 = inverse * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		p3 = inverse * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Bottom = Plane(p2 - p1, p3 - p1, p1);

		// Top
		p1 = inverse * glm::vec4(1.0f, -1.0f, 0.0f, 1.0f);
		p2 = inverse * glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
		p3 = inverse * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
		p1 /= p1.w;
		p2 /= p2.w;
		p3 /= p3.w;

		m_Top = Plane(p2 - p1, p3 - p1, p1);
	}
	
	bool ViewFrustum::Check(const BoundingBox& boundingBox, const glm::mat4& transformMatrix) const
	{
		glm::vec3 dimensions = boundingBox.GetDimensions();
		
		std::vector<glm::vec3> boxPoints = {
			{dimensions.x / 2.0f, dimensions.y / 2.0f, dimensions.z / 2.0f},
			{dimensions.x / 2.0f, dimensions.y / 2.0f, -dimensions.z / 2.0f},
			{dimensions.x / 2.0f, -dimensions.y / 2.0f, dimensions.z / 2.0f},
			{dimensions.x / 2.0f, -dimensions.y / 2.0f, -dimensions.z / 2.0f},
			{-dimensions.x / 2.0f, dimensions.y / 2.0f, dimensions.z / 2.0f},
			{-dimensions.x / 2.0f, dimensions.y / 2.0f, -dimensions.z / 2.0f},
			{-dimensions.x / 2.0f, -dimensions.y / 2.0f, dimensions.z / 2.0f},
			{-dimensions.x / 2.0f, -dimensions.y / 2.0f, -dimensions.z / 2.0f}
		};

		for(auto p : boxPoints)
		{
			if(Check(glm::vec3(transformMatrix * glm::vec4(p, 1))))
			{
				return true;
			}
		}

		return false;
	}

	bool ViewFrustum::Check(const BoundingSphere& boundingSphere, const glm::vec3& position) const
	{
		glm::vec3 checkPoint;

		checkPoint = position;
		checkPoint.x += boundingSphere.GetRadius();

		if(Check(checkPoint))
		{
			return true;
		}

		checkPoint = position;
		checkPoint.x -= boundingSphere.GetRadius();

		if (Check(checkPoint))
		{
			return true;
		}

		checkPoint = position;
		checkPoint.y += boundingSphere.GetRadius();

		if (Check(checkPoint))
		{
			return true;
		}

		checkPoint = position;
		checkPoint.y -= boundingSphere.GetRadius();

		if (Check(checkPoint))
		{
			return true;
		}

		checkPoint = position;
		checkPoint.z += boundingSphere.GetRadius();

		if (Check(checkPoint))
		{
			return true;
		}

		checkPoint = position;
		checkPoint.z -= boundingSphere.GetRadius();

		if (Check(checkPoint))
		{
			return true;
		}

		return false;
	}

	bool ViewFrustum::Check(const glm::vec3& point) const
	{
		return m_Top.Distance(point) >= 0.0f
			&& m_Bottom.Distance(point) >= 0.0f
			&& m_Left.Distance(point) >= 0.0f
			&& m_Right.Distance(point) >= 0.0f
			&& m_Near.Distance(point) >= 0.0f
			&& m_Far.Distance(point) >= 0.0f;
	}

	ViewFrustum::ViewFrustum(float t, float b, float l, float r, float n, float f)
	{
		glm::vec3 origin, point1, point2;
		origin = glm::vec3(l, n, b);
		point1 = glm::vec3(l, n, t);
		point2 = glm::vec3(r, n, b);

		m_Near = Plane(point1 - origin, point2 - origin, origin);

		origin = glm::vec3(r, f, b);
		point1 = glm::vec3(r, f, t);
		point2 = glm::vec3(l, f, b);

		m_Far = Plane(point1 - origin, point2 - origin, origin);

		origin = glm::vec3(l, n, b);
		point1 = glm::vec3(l, f, t);
		point2 = glm::vec3(l, n, b);

		m_Left = Plane(point1 - origin, point2 - origin, origin);

		origin = glm::vec3(r, f, b);
		point1 = glm::vec3(r, n, b);
		point2 = glm::vec3(r, f, t);

		m_Right = Plane(point1 - origin, point2 - origin, origin);

		origin = glm::vec3(r, n, t);
		point1 = glm::vec3(l, n, t);
		point2 = glm::vec3(r, f, t);

		m_Top = Plane(point1 - origin, point2 - origin, origin);

		origin = glm::vec3(l, n, b);
		point1 = glm::vec3(r, n, b);
		point2 = glm::vec3(l, f, b);

		m_Bottom = Plane(point1 - origin, point2 - origin, origin);
	}

	ViewFrustum::ViewFrustum(float aspect, float fov, float nearPlane, float farPlane)
	{
		fov = glm::radians(fov);
		
		glm::vec3 flt, flb, frt, frb, nlt, nlb, nrt, nrb;
		
		flt = glm::vec3(-farPlane * glm::tan(aspect * fov / 2.0f), farPlane, farPlane * glm::tan(fov / 2.0f));
		flb = glm::vec3(-farPlane * glm::tan(aspect * fov / 2.0f), farPlane, -farPlane * glm::tan(fov / 2.0f));
		frt = glm::vec3(farPlane * glm::tan(aspect * fov / 2.0f), farPlane, farPlane * glm::tan(fov / 2.0f));
		flb = glm::vec3(farPlane * glm::tan(aspect * fov / 2.0f), farPlane, -farPlane * glm::tan(fov / 2.0f));
		nlb = glm::vec3(-nearPlane * glm::tan(aspect * fov / 2.0f), nearPlane, -nearPlane * glm::tan(fov / 2.0f));
		nlt = glm::vec3(-nearPlane * glm::tan(aspect * fov / 2.0f), nearPlane, nearPlane * glm::tan(fov / 2.0f));
		nrb = glm::vec3(nearPlane * glm::tan(aspect * fov / 2.0f), nearPlane, -nearPlane * glm::tan(fov / 2.0f));
		nrt = glm::vec3(nearPlane * glm::tan(aspect * fov / 2.0f), nearPlane, nearPlane * glm::tan(fov / 2.0f));

		m_Near = Plane(nlt - nlb, frb - nlb, nlb);
		m_Far = Plane(frt - frb, flb - frb, frb);
		m_Left = Plane(flt - flb, nlb - flb, flb);
		m_Right = Plane(nrt - nrb, frb - nrb, nrb);
		m_Bottom = Plane(nrb - nlb, flb - nlb, nlb);
		m_Top = Plane(nlt - nrt, frt - nrt, nrt);
	}
	
}
