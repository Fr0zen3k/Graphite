#include "Graphite/Core/grpch.h"

#include "TexturePool.h"

namespace Graphite
{

	TexturePool::~TexturePool()
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		VulkanTexture::DestroyCommonSampler();
#endif

		for(Texture* texture : m_Textures)
		{
			delete texture;
		}
	}

	uint32_t TexturePool::AddTexture(const std::string& filePath)
	{
		Texture* texture = Texture::CreateTexture(filePath);
		m_Textures.emplace_back(texture);

		return static_cast<uint32_t>(m_Textures.size() - 1);
	}
	
}