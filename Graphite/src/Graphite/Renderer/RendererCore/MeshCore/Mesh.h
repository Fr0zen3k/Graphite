#pragma once

#ifndef GRAPHITE_MESH_H
#define GRAPHITE_MESH_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Utilities.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

#include "glm/glm.hpp"

namespace Graphite
{

	class GRAPHITE_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		~Mesh();

		void SetTextureCoordinates(glm::vec2* uvCoords);
		void SetMeshColor(const glm::vec4& color);
		void SetVertexColors(glm::vec4* colors);

		inline size_t VertexCount() const { return m_VertexBuffer->Size(); }
		inline size_t IndexCount() const { return m_IndexBuffer->Size(); }
		
	private:
		Vertex* m_Vertices;
		uint32_t* m_Indices;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
	};

}

#endif
