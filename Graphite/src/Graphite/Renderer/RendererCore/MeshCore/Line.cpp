#include "Graphite/Core/grpch.h"
#include "Line.h"

namespace Graphite
{

	void Line::Init()
	{
		Vertex v;
		v.position = { -0.5f, 0.0f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 0.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);

		v.position = { 0.5f, 0.0f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 1.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);

		s_QuadIndices.emplace_back(0);
		s_QuadIndices.emplace_back(1);
		s_QuadIndices.emplace_back(0);
	}

	
}