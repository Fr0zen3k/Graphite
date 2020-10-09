#pragma once

#ifndef GRAPHITE_BOUNDS2D_H
#define GRAPHITE_BOUNDS2D_H

#include "Graphite/Core/grpch.h"

#include "glm/glm.hpp"

namespace Graphite
{

	struct grBoundingSquare2D
	{
		glm::vec4 m_dimensions;

		grBoundingSquare2D(const std::vector<glm::vec3>& vertexBuffer)
		{
			glm::vec3 maxX, maxY, minX, minY;

			maxX = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right) { return left.x > right.x; });
			maxY = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right) { return left.y > right.y; });
			minX = *std::min_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right) { return left.x < right.x; });
			minY = *std::min_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right) { return left.y < right.y; });

			m_dimensions.x = maxX.x;
			m_dimensions.y = minX.x;
			m_dimensions.z = maxY.y;
			m_dimensions.w = minY.y;
		}
	};

	struct grBoundingCircle2D
	{
		float m_radius;

		grBoundingCircle2D(const std::vector<glm::vec3>& vertexBuffer)
		{
			glm::vec3 max = *std::max_element(vertexBuffer.begin(), vertexBuffer.end(), [](glm::vec3 left, glm::vec3 right)
			{
				return std::sqrt(left.x * left.x + left.y * left.y) > std::sqrt(right.x * right.x + right.y * right.y);
			});

			m_radius = std::sqrt(max.x * max.x + max.y * max.y);
		}
	};
	
}

#endif
