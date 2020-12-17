#pragma once

#ifndef GRAPHITE_TEXTUREPOOL_H
#define GRAPHITE_TEXTUREPOOL_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Texture.h"
#include "../Platform/Vulkan/VulkanTexture.h"


namespace Graphite
{

	class GRAPHITE_API TexturePool
	{
	public:
		TexturePool() = default;
		~TexturePool();

		uint32_t AddTexture(const std::string& filePath);
		
	private:
		std::vector<Texture*> m_Textures;
	};
	
}


#endif
