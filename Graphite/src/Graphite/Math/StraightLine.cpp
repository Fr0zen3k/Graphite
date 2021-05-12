#include "Graphite/Core/grpch.h"
#include "StraightLine.h"

namespace Graphite {
	StraightLine::StraightLine(const glm::vec3& point1, const glm::vec3& point2)
	{
		glm::vec3 direction = point2 - point1;

		m_Parameters = glm::mat4x2(direction.x, point1.x, direction.y, point1.y, direction.z, point1.z, 0, 1);
	}

	bool StraightLine::PointOnLine(const glm::vec3& point) const
	{
		return glm::normalize(point - glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0])) == glm::normalize(glm::vec3(m_Parameters[0][1], m_Parameters[1][1], m_Parameters[2][1]))
			|| glm::normalize(point - glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0])) == -1.0f * glm::normalize(glm::vec3(m_Parameters[0][1], m_Parameters[1][1], m_Parameters[2][1]));
	}

	bool StraightLine::Parallel(const StraightLine& line) const
	{
		return glm::normalize(glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0]))
			== glm::normalize(glm::vec3(line.m_Parameters[0][0], line.m_Parameters[1][0], line.m_Parameters[2][0]))
			|| glm::normalize(glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0]))
			== -1.0f * glm::normalize(glm::vec3(line.m_Parameters[0][0], line.m_Parameters[1][0], line.m_Parameters[2][0]));
	}

	bool StraightLine::Parallel(const glm::vec3& vector) const
	{
		return glm::normalize(glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0]))
			== glm::normalize(vector)
			|| glm::normalize(glm::vec3(m_Parameters[0][0], m_Parameters[1][0], m_Parameters[2][0]))
			== -1.0f * glm::normalize(vector);
	}

	float StraightLine::Distance(const glm::vec3& point) const
	{
		float tf = 2.0f * (m_Parameters[0][0] * (point.x - m_Parameters[0][1]) + m_Parameters[1][0] * (point.x - m_Parameters[1][1]) + m_Parameters[2][0] * (point.x - m_Parameters[2][1]));
		float bf = glm::pow(m_Parameters[0][0], 2) + glm::pow(m_Parameters[1][0], 2) + glm::pow(m_Parameters[2][0], 2);

		float t = tf / bf;

		glm::vec3 pointOnLine = Get(t);

		return glm::length(point - pointOnLine);
	}

	glm::vec3 StraightLine::Get(float t) const
	{
		return glm::vec3(m_Parameters[0][0] * t + m_Parameters[0][1], m_Parameters[1][0] * t + m_Parameters[1][1], m_Parameters[2][0] * t + m_Parameters[2][1]);
	}
}
