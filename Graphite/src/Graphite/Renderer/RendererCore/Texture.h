#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_TEXTURE_H
#define GRAPHITE_TEXTURE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

namespace Graphite
{

	class GRAPHITE_API Texture
	{
	public:
		virtual ~Texture() = default;
		
		static Texture* CreateTexture(const std::string& filePath);

		virtual std::pair<uint32_t, uint32_t> GetTextureSize() const = 0;
		
	protected:
		Texture() = default;
	};
	
}


#endif
