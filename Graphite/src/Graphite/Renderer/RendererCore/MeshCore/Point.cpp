#include "Graphite/Core/grpch.h"
#include "Point.h"

namespace Graphite
{
	std::vector<Vertex> Point::s_QuadVertices;
	std::vector<uint32_t> Point::s_QuadIndices;

	void Point::Init()
	{
		Vertex v;
		v.position = { 0.0f, 0.0f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 0.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);

		s_QuadIndices.emplace_back(0);
		s_QuadIndices.emplace_back(0);
		s_QuadIndices.emplace_back(0);
	}

	
}