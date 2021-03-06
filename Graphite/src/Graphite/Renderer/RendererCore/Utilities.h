#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_UTILITIES_H
#define GRAPHITE_UTILITIES_H

#include "glm/glm.hpp"

namespace Graphite
{

	enum class ShaderType
	{
		None,
		Vertex,
		Tessellation,
		Geometry,
		Fragment,
		Compute
	};

	struct Vertex
	{
		glm::vec3 position;			// Position (x, y, z)
		glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);			// Color (r, g, b)
		glm::vec2 textureCoords;	// Texture Coordinates (u, v)
		glm::vec3 normal;
	};

	struct ViewProjection
	{
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
	};
	
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif