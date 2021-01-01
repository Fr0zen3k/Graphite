#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_VERTEXBUFFER_H
#define GRAPHITE_VERTEXBUFFER_H

#include "Graphite/Core/Core.h"
#include "Utilities.h"

namespace Graphite
{

	class GRAPHITE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual size_t Size() const = 0;

		static VertexBuffer* CreateVertexBuffer(Vertex* pVertices, size_t size);
		
	protected:
		VertexBuffer() = default;
	};
	
}

#endif
