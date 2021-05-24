#include "Graphite/Core/grpch.h"
#include "Plane.h"

namespace Graphite
{
	Plane::Plane(const glm::vec3& vector1, const glm::vec3& vector2, const glm::vec3& point)
	{
		glm::vec3 normal = glm::cross(vector1, vector2);
		normal = glm::normalize(normal);

		float d = -1.0f * (normal.x * point.x + normal.y * point.y + normal.z * point.z);

		m_Parameters = glm::vec4(normal, d);
	}

	Plane::Plane(const glm::vec3& normal, const glm::vec3& point)
	{
		glm::vec3 norm = glm::normalize(normal);
		
		float d = -1.0f * (norm.x * point.x + norm.y * point.y + norm.z * point.z);

		m_Parameters = glm::vec4(norm, d);
	}

	Plane::Plane(const glm::vec3& normal, float distanceToOrigin)
	{
		glm::vec3 norm = glm::normalize(normal);

		glm::vec3 point = distanceToOrigin * norm;

		float d = -1.0f * (norm.x * point.x + norm.y * point.y + norm.z * point.z);

		m_Parameters = glm::vec4(norm, d);
	}

	float Plane::Distance(const glm::vec3& point) const
	{
		return m_Parameters.x * point.x + m_Parameters.y * point.y + m_Parameters.z * point.z + m_Parameters.w;
	}

	float Plane::Distance(const glm::vec4& point) const
	{
		if(point.w == 0)
		{
			throw std::runtime_error("Cannot calculate distance of a point in infinity.");
		}
		
		glm::vec3 p = point / point.w;

		return Distance(p);
	}

	float Plane::Distance(const glm::mat4x2& lineParameters) const
	{
		return false;
	}

	float Plane::Distance(const Plane& plane) const
	{
		return false;
	}

	bool Plane::OnPlane(const glm::vec3& point) const
	{
		return Distance(point) == 0;
	}

	bool Plane::OnPlane(const glm::vec4& point) const
	{
		return Distance(point) == 0;
	}

	bool Plane::OnPlane(const glm::mat4x2& lineParameters) const
	{
		return false;
	}

	bool Plane::Parallel(const Plane& plane) const
	{
		return glm::abs((m_Parameters.x * plane.m_Parameters.x + m_Parameters.y * plane.m_Parameters.y + m_Parameters.z * plane.m_Parameters.z)
			/ (glm::length(glm::vec3(m_Parameters) * glm::length(glm::vec3(plane.m_Parameters))))) >= 0.9999f;
	}

	bool Plane::Parallel(const glm::mat4x2& lineParameters) const
	{
		return false;
	}

	bool Plane::Parallel(const glm::vec3 vector) const
	{
		return glm::abs((m_Parameters.x * vector.x + m_Parameters.y * vector.y + m_Parameters.z * vector.z)
			/ (glm::length(glm::vec3(m_Parameters) * glm::length(vector)))) < 0.0001f;
	}
}
