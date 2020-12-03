#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANSHADER_H
#define GRAPHITE_VULKANSHADER_H

#include "Graphite/Core/grpch.h"

#include "vulkan/vulkan.h"

#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "Utils.h"
#include "VulkanGraphicsContext.h"
#include "VulkanFrameBuffer.h"

namespace Graphite
{

	class GRAPHITE_API VulkanShader
	{
	public:
		VulkanShader();
		VulkanShader(ShaderType type);
		VulkanShader(ShaderType type, const std::string& filepath);
		~VulkanShader();

		inline VkShaderModule GetShader() { return m_ShaderModule; }
		inline ShaderType GetShaderType() { return m_Type; }
		inline VkPipelineShaderStageCreateInfo GetCreateInfo() { return m_ShaderStageCreateInfo; }
		void SetShaderFilepath(const std::string& filepath);
		inline void SetShaderType(ShaderType type)
		{
			m_Type = type;
		}
		
	private:
		void Init();
		void Shutdown();
		void LoadBytecode();

	private:
		static VulkanGraphicsContext* s_GraphicsContext;
		
		ShaderType m_Type;
		
		std::string m_Filepath;
		std::vector<char> m_BytecodeBuffer;

		VkShaderModule m_ShaderModule;
		VkPipelineShaderStageCreateInfo m_ShaderStageCreateInfo;
	};
	
}


#endif

#endif

