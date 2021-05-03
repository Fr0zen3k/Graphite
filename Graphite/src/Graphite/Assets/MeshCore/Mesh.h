#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_MESH_H
#define GRAPHITE_MESH_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Graphite/Renderer/RendererCore/Utilities.h"
#include "Graphite/Renderer/RendererCore/VertexBuffer.h"
#include "Graphite/Renderer/RendererCore/IndexBuffer.h"

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

		inline VertexBuffer* GetVertexBuffer() { return m_VertexBuffer; }
		inline IndexBuffer* GetIndexBuffer() { return m_IndexBuffer; }
		
	private:
		Vertex* m_Vertices;
		uint32_t* m_Indices;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif