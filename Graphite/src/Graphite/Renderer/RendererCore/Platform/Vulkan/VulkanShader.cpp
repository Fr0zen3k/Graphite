#include "Graphite/Core/grpch.h"
#include "VulkanShader.h"


namespace Graphite
{
	VulkanShader::VulkanShader(ShaderType type): m_Type(type), m_Filepath("")
	{
		m_ShaderStageCreateInfo = {};

		m_ShaderStageCreateInfo.pName = nullptr;
	}

	VulkanShader::VulkanShader(ShaderType type, const std::string& filepath): m_Type(type)
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

		if(m_ShaderStageCreateInfo.pName != nullptr)
		{
			Shutdown();
		}

		Init();
	}

	void VulkanShader::Init()
	{
		LoadBytecode();

		VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.codeSize = m_BytecodeBuffer.size();
		shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(m_BytecodeBuffer.data());

		VkResult result = vkCreateShaderModule(m_GraphicsContext->m_LogicalDevice, &shaderModuleCreateInfo, nullptr, &m_ShaderModule);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a shader module!");
		}

		m_ShaderStageCreateInfo = {};
		m_ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

		switch (m_Type)
		{
			case(ShaderType::Vertex):
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
				break;
			}

			case(ShaderType::Fragment):
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				break;
			}
			case(ShaderType::Tessellation):
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
				break;
			}

			case(ShaderType::Geometry):
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
				break;
			}
			
			case(ShaderType::Compute):
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
				break;
			}
			
			default:
			{
				m_ShaderStageCreateInfo.stage = VK_SHADER_STAGE_ALL_GRAPHICS;
				break;
			}
		}

		m_ShaderStageCreateInfo.module = m_ShaderModule;
		m_ShaderStageCreateInfo.pName = "main";
	}

	void VulkanShader::Shutdown()
	{
		vkDestroyShaderModule(m_GraphicsContext->m_LogicalDevice, m_ShaderModule, nullptr);
	}

	void VulkanShader::LoadBytecode()
	{
		std::ifstream file(m_Filepath, std::ios::ate | std::ios::binary);

		size_t fileSize = (size_t)file.tellg();
		m_BytecodeBuffer.resize(fileSize);

		file.seekg(0);
		file.read(m_BytecodeBuffer.data(), fileSize);

		file.close();
	}
}
