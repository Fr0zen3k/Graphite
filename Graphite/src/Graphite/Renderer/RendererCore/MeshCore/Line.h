#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_LINE_H
#define GRAPHITE_LINE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Mesh.h"

#include "../Utilities.h"

namespace Graphite
{

	class GRAPHITE_API Line : public Mesh
	{
	public:
		Line() : Mesh(s_LineVertices, s_LineIndices) {}
		~Line() = default;

		static void Init();

	private:
		static std::vector<Vertex> s_LineVertices;
		static std::vector<uint32_t> s_LineIndices;
	};

}


#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif