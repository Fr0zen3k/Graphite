#pragma once

#ifndef GRAPHITE_VERTEXBUFFER_H
#define GRAPHITE_VERTEXBUFFER_H

#include "Graphite/Core/Core.h"
#include "Utilities.h"

namespace Graphite
{

	class GRAPHITE_API VertexBuffer
	{
	public:
		virtual size_t Size() const = 0;

		static VertexBuffer* CreateVertexBuffer(Vertex* pVertices, size_t size);
		
	protected:
		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;
	};
	
}

#endif
