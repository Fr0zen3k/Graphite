#pragma once

#ifndef GRAPHITE_INDEXBUFFER_H
#define GRAPHITE_INDEXBUFFER_H

#include "Graphite/Core/Core.h"

namespace Graphite
{

	class GRAPHITE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual size_t Size() const = 0;

		static IndexBuffer* CreateIndexBuffer(uint32_t* pIndices, size_t size);
		
	protected:
		IndexBuffer() = default;
	};
	
}

#endif
