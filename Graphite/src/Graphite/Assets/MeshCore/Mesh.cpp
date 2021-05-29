#include "Graphite/Core/grpch.h"
#include "Mesh.h"

namespace Graphite
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
		m_Vertices = std::vector<Vertex>(vertices);
		m_Indices = std::vector<uint32_t>(indices);

		m_VertexBuffer = VertexBuffer::CreateVertexBuffer(m_Vertices.data(), vertices.size());
		m_IndexBuffer = IndexBuffer::CreateIndexBuffer(m_Indices.data(), indices.size());
	}

	Mesh::~Mesh()
	{
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

	void Mesh::SetTextureCoordinates(glm::vec2* uvCoords)
	{
		size_t size = m_VertexBuffer->Size();
		
		for(int i = 0; i < size; i++)
		{
			m_Vertices[i].textureCoords = uvCoords[i];
		}

		delete m_VertexBuffer;

		m_VertexBuffer = VertexBuffer::CreateVertexBuffer(m_Vertices.data(), size);
	}

	void Mesh::SetMeshColor(const glm::vec4& color)
	{
		size_t size = m_VertexBuffer->Size();

		for(int i = 0; i < size; i++)
		{
			m_Vertices[i].color = color;
		}

		delete m_VertexBuffer;

		m_VertexBuffer = VertexBuffer::CreateVertexBuffer(m_Vertices.data(), size);
	}

	void Mesh::SetVertexColors(glm::vec4* colors)
	{
		size_t size = m_VertexBuffer->Size();

		for (int i = 0; i < size; i++)
		{
			m_Vertices[i].color = colors[i];
		}

		delete m_VertexBuffer;

		m_VertexBuffer = VertexBuffer::CreateVertexBuffer(m_Vertices.data(), size);
	}

	float Mesh::GetMaxDistance() const
	{
		if(m_BoundingRadius > 0)
		{
			return m_BoundingRadius;
		}

		float max = 0.0f;

		for (int i = 0; i < m_VertexBuffer->Size(); i++)
		{
			if (glm::length(m_Vertices[i].position) > max)
			{
				max = glm::length(m_Vertices[i].position);
			}
		}

		return max;
	}
}
