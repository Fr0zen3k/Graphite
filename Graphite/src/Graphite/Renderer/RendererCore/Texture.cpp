#include "Graphite/Core/grpch.h"
#include "Texture.h"

#include "Platform/Vulkan/VulkanTexture.h"

namespace Graphite
{
	Texture* Texture::CreateTexture(const std::string& filePath)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanTexture(filePath);
#endif
	}

	Texture* Texture::CreateTexture(std::istream& srcStream)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanTexture(srcStream);
#endif
	}
	
}
