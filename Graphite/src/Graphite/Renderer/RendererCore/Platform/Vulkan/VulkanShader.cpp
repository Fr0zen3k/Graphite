#include "Graphite/Core/grpch.h"
#include "VulkanShader.h"


#ifdef GRAPHITE_RENDERER_VULKAN

#include "VulkanGraphicsContext.h"
#include "../../../Renderer3D/Renderer3D.h"

namespace Graphite
{
	VulkanShader::VulkanShader(): Shader()
	{
		m_Type = ShaderType::None;
		m_Filepath = "";
	}

	
	VulkanShader::VulkanShader(ShaderType type): m_Type(type), m_Filepath(""), Shader()
	{		
		m_ShaderStageCreateInfo = {};

		m_ShaderStageCreateInfo.pName = nullptr;
	}

	VulkanShader::VulkanShader(ShaderType type, const std::string& filepath): m_Type(type), Shader()
	{
		SetShaderFilepath(filepath);
	}

	VulkanShader::~VulkanShader()
	{
		Shutdown();
	}
	
	void VulkanShader::SetShaderFilepath(const std::string& filepath)
	{
		m_Filepath = filepath;
	}

	void VulkanShader::Init()
	{
		LoadBytecode();

		VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.codeSize = m_BytecodeBuffer.size();
		shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(m_BytecodeBuffer.data());

		VkResult result = vkCreateShaderModule(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&shaderModuleCreateInfo,
			nullptr,
			&m_ShaderModule);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a shader module!");
		}
		
	}

	void VulkanShader::Shutdown()
	{
		vkDeviceWaitIdle(GR_GRAPHICS_CONTEXT->GetLogicalDevice());
		vkDestroyShaderModule(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_ShaderModule,
			nullptr);
	}

	void VulkanShader::LoadBytecode()
	{
		std::ifstream file(m_Filepath, std::ios::ate | std::ios::binary);

		size_t fileSize = (size_t)file.tellg();
		m_BytecodeBuffer.resize(fileSize);

		file.seekg(0);
		file.read(
			m_BytecodeBuffer.data(),
			fileSize);

		file.close();
	}
}

#endif
