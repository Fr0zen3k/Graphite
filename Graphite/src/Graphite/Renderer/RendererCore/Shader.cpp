#include "Graphite/Core/grpch.h"

#include "Shader.h"

#include "Platform/Vulkan/VulkanShader.h"

namespace Graphite
{

	Shader* Shader::CreateShader()
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanShader();
#endif
	}

	Shader* Shader::CreateShader(ShaderType type)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanShader(type);
#endif
	}

	Shader* Shader::CreateShader(ShaderType type, const std::string& filepath)
	{
#ifdef GRAPHITE_RENDERER_VULKAN
		return new VulkanShader(type, filepath);
#endif
	}

	
}
