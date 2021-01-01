#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANSHADER_H
#define GRAPHITE_VULKANSHADER_H

#include "Graphite/Core/grpch.h"

#include "vulkan/vulkan.h"

#include "Graphite/Core/Core.h"
#include "../../Utilities.h"

#include "../../Shader.h"

namespace Graphite
{

	class GRAPHITE_API VulkanShader: public Shader
	{
	public:
		VulkanShader();
		VulkanShader(ShaderType type);
		VulkanShader(ShaderType type, const std::string& filepath);
		~VulkanShader();

		inline VkShaderModule GetShader() { return m_ShaderModule; }
		inline VkPipelineShaderStageCreateInfo GetCreateInfo() { return m_ShaderStageCreateInfo; }

		inline ShaderType GetShaderType() const override { return m_Type; }
		void SetShaderFilepath(const std::string& filepath) override;
		inline void SetShaderType(ShaderType type) override { m_Type = type; }
		
	private:
		void Init();
		void Shutdown();
		void LoadBytecode();

	private:		
		ShaderType m_Type;
		
		std::string m_Filepath;
		std::vector<char> m_BytecodeBuffer;

		VkShaderModule m_ShaderModule;
		VkPipelineShaderStageCreateInfo m_ShaderStageCreateInfo;
	};
	
}


#endif

#endif

