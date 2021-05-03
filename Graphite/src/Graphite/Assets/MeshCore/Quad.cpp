#include "Graphite/Core/grpch.h"

#include "Quad.h"

#include "glm/glm.hpp"

namespace Graphite
{

	std::vector<Vertex> Quad::s_QuadVertices;
	std::vector<uint32_t> Quad::s_QuadIndices;
	
	void Quad::Init()
	{
		Vertex v;
		v.position = {-0.5f, 0.5f, 0.0f};
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = {0.0f, 0.0f};
		v.normal = {0, 0, 1};
		s_QuadVertices.emplace_back(v);

		v.position = { 0.5f, 0.5f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 1.0f, 0.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);

		v.position = { -0.5f, -0.5f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 0.0f, 1.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);
		
		v.position = { 0.5f, -0.5f, 0.0f };
		v.color = { 0.0f, 0.0f, 0.0f, 0.0f };
		v.textureCoords = { 1.0f, 1.0f };
		v.normal = { 0, 0, 1 };
		s_QuadVertices.emplace_back(v);

		s_QuadIndices.emplace_back(0);
		s_QuadIndices.emplace_back(1);
		s_QuadIndices.emplace_back(2);
		s_QuadIndices.emplace_back(2);
		s_QuadIndices.emplace_back(3);
		s_QuadIndices.emplace_back(1);
	}
	
}
