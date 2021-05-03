#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_QUAD_H
#define GRAPHITE_QUAD_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Mesh.h"

#include "Graphite/Renderer/RendererCore/Utilities.h"

namespace Graphite
{

	class GRAPHITE_API Quad : public Mesh
	{
	public:
		Quad() : Mesh(s_QuadVertices, s_QuadIndices) {}
		~Quad() = default;

		static void Init();

	private:
		static std::vector<Vertex> s_QuadVertices;
		static std::vector<uint32_t> s_QuadIndices;
	};
	
}


#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif