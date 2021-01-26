#include "Graphite/Core/grpch.h"
#include "Line.h"

namespace Graphite
{

	std::vector<Vertex> Line::s_LineVertices;
	std::vector<uint32_t> Line::s_LineIndices;
	
	void Line::Init()
	{
		Vertex v;
		v.position = { -0.5f, 0.0f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 0.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_LineVertices.emplace_back(v);

		v.position = { 0.5f, 0.0f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 1.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_LineVertices.emplace_back(v);

		s_LineIndices.emplace_back(0);
		s_LineIndices.emplace_back(1);
		s_LineIndices.emplace_back(0);
	}

	
}