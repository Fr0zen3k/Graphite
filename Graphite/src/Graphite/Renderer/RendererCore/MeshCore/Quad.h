#pragma once

#ifndef GRAPHITE_QUAD_H
#define GRAPHITE_QUAD_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Mesh.h"

#include "../Utilities.h"

namespace Graphite
{

	class GRAPHITE_API Quad : public Mesh
	{
	public:
		Quad() : Mesh(s_QuadVertices, s_QuadIndices) {}
		~Quad();

		static void Init();

	private:
		static std::vector<Vertex> s_QuadVertices;
		static std::vector<uint32_t> s_QuadIndices;
	};
	
}


#endif
