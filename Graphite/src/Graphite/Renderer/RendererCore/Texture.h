#pragma once


#ifndef GRAPHITE_TEXTURE_H
#define GRAPHITE_TEXTURE_H

#include "Graphite/Core/grpch.h"

namespace Graphite
{

	class Texture
	{
	public:
		static Texture* CreateTexture(const std::string& filePath);

		virtual std::pair<uint32_t, uint32_t> GetTextureSize() const = 0;
		
	protected:
		Texture() = default;
		virtual ~Texture() = default;
	};
	
}


#endif
