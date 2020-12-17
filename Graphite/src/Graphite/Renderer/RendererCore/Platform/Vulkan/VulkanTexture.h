#pragma once

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_VULKANTEXTURE_H
#define GRAPHITE_VULKANTEXTURE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"
#include "Utils.h"

#include "vulkan/vulkan.h"
#include "stb_image.h"

#include "../../Texture.h"

namespace Graphite
{

	class GRAPHITE_API VulkanTexture: public Texture
	{
	public:
		VulkanTexture(const std::string& filePath);
		~VulkanTexture();

		inline VkImage GetNativeImage() const { return m_Image; }
		inline VkImageView GetImageView() const { return m_ImageView; }
		inline std::pair<uint32_t, uint32_t> GetTextureSize() const override { return std::pair<uint32_t, uint32_t>(m_Width, m_Height); }
		
		static inline VkSampler GetCommonSampler() { return s_CommonTextureSampler; }
		static inline bool Initialized() { return s_SampleInitialized; }

		static void DestroyCommonSampler();

		// Add a texture sampler recreation function for when new renderer settings are introduced, or when old settings change (after implementing the renderer settings functionality to the engine)

	private:
		void Init(const std::string& filePath);
		void Shutdown();

		void CreateImage(const std::string& filePath);
		void CreateImageView();
		void CreateDescriptorSet();

		stbi_uc* LoadTextureFile(const std::string& filePath);

		static void CreateCommonSampler();
		
	private:
		int m_Width;
		int m_Height;
		
		VkImage m_Image;
		VkDeviceMemory m_ImageMemory;
		VkImageView m_ImageView;
		VkDescriptorSet m_DescriptorSet;
		
		static VkSampler s_CommonTextureSampler;
		static bool s_SampleInitialized;
	};
	
}

#endif

#endif
