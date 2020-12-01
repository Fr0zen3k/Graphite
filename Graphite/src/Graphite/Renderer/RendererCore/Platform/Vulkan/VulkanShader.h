#pragma once

#ifndef GRAPHITE_VULKANSHADER_H
#define GRAPHITE_VULKANSHADER_H

#include "Graphite/Core/grpch.h"

#include "vulkan/vulkan.h"

#include "Graphite/Core/Core.h"
#include "Graphite/EventCore/Events.h"

#include "Utils.h"
#include "VulkanGraphicsContext.h"

namespace Graphite
{

	class GRAPHITE_API VulkanShader
	{
	public:
		VulkanShader(ShaderType type);
		VulkanShader(ShaderType type, const std::string& filepath);
		~VulkanShader();

		inline VkShaderModule GetShader()
		{
			
		}
		void SetShaderFilepath(const std::string& filepath);
		
	private:
		void Init();
		void Shutdown();
		void LoadBytecode();

	private:
		static VulkanGraphicsContext* m_GraphicsContext;
		
		ShaderType m_Type;
		
		std::string m_Filepath;
		std::vector<char> m_BytecodeBuffer;

		VkShaderModule m_ShaderModule;
		VkPipelineShaderStageCreateInfo m_ShaderStageCreateInfo;
	};
	
}


#endif
