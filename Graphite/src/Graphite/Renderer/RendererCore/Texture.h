#pragma once


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
		static Texture* CreateTexture(std::istream& srcStream);

		virtual std::pair<uint32_t, uint32_t> GetTextureSize() const = 0;
		
	protected:
		Texture() = default;
	};
	
}


#endif
