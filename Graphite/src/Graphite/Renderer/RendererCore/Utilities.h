#pragma once

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
		glm::vec4 color;			// Color (r, g, b)
		float textureID;			// Texture ID
		glm::vec2 textureCoords;	// Texture Coordinates (u, v)
	};
	
}

#endif
