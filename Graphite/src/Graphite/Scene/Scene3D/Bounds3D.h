#pragma once

#ifndef GRAPHITE_BOUNDS3D_H
#define GRAPHITE_BOUNDS3D_H

#include "Graphite/Core/grpch.h"

#include "glm/glm.hpp"

namespace Graphite
{

	struct grBoundingBox3D
	{
		glm::vec3 m_min, m_max;

		grBoundingBox3D(const std::vector<glm::vec3>& vertexBuffer)
		{
			glm::vec3 temp;

			temp = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.x > right.x;
				});
			m_max.x = temp.x;

			temp = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.y > right.y;
				});
			m_max.y = temp.y;

			temp = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.z > right.z;
				});
			m_max.z = temp.z;

			temp = *std::min_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.x < right.x;
				});
			m_min.x = temp.x;

			temp = *std::min_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.y < right.y;
				});
			m_min.y = temp.y;

			temp = *std::min_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return left.z < right.z;
				});
			m_min.z = temp.z;
		}
	};

	struct grBoundingSphere3D
	{
		float m_radius;

		grBoundingSphere3D(const std::vector<glm::vec3>& vertexBuffer)
		{
			glm::vec3 max = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
				{
					return std::sqrt(left.x * left.x + left.y * left.y + left.z * left.z) > std::sqrt(right.x * right.x + right.y * right.y + right.z * right.z);
				});

			m_radius = std::sqrt(max.x * max.x + max.y * max.y + max.z * max.z);
		}
	};
	
}

#endif