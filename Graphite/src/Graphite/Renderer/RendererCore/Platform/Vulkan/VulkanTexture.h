#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

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
		VulkanTexture(std::istream& srcStream);
		~VulkanTexture() override;

		inline VkImage GetNativeImage() const { return m_Image; }
		inline VkImageView GetImageView() const { return m_ImageView; }
		inline std::pair<uint32_t, uint32_t> GetTextureSize() const override { return std::pair<uint32_t, uint32_t>(m_Width, m_Height); }

		inline VkDescriptorSet GetDescriptorSet() const { return m_DescriptorSet; }
		
		static inline VkSampler GetCommonSampler() { return s_CommonTextureSampler; }

		static void DestroyCommonSampler();

		static void CreateCommonSampler();

	private:
		void Init(const std::string& filePath);
		void Init(std::istream& srcStream);
		void Shutdown();

		void CreateImage(const std::string& filePath);
		void CreateImage(std::istream& srcStream);
		void CreateImageView();
		void CreateDescriptorSet();
		
		stbi_uc* LoadTextureFile(const std::string& filePath);
		stbi_uc* LoadTextureStream(std::istream& srcStream);

		
	private:
		int m_Width;
		int m_Height;
		
		VkImage m_Image;
		VkDeviceMemory m_ImageMemory;
		VkImageView m_ImageView;
		VkDescriptorSet m_DescriptorSet;
		
		static VkSampler s_CommonTextureSampler;
		static VkDescriptorSetLayout s_TextureSamplerDescriptorSetLayout;
	};
	
}

#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif