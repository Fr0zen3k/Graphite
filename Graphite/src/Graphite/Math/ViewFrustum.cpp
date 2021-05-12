#include "Graphite/Core/grpch.h"
#include "ViewFrustum.h"

namespace Graphite
{
	
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

	}

	ViewFrustum::ViewFrustum(float aspect, float fov, float nearPlane, float farPlane)
	{

	}

	void ViewFrustum::Init(Plane topPlane, Plane bottomPlane, Plane leftPlane, Plane rightPlane, Plane nearPlane,
		Plane farPlane)
	{
		m_Top = topPlane;
		m_Bottom = bottomPlane;
		m_Left = leftPlane;
		m_Right = rightPlane;
		m_Near = nearPlane;
		m_Far = farPlane;
	}
	
}
