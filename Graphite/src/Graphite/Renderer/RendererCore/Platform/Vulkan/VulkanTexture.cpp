#include "Graphite/Core/grpch.h"

#ifdef GRAPHITE_RENDERER_VULKAN

#define STB_IMAGE_IMPLEMENTATION

#include "VulkanTexture.h"
#include "../../../Renderer3D/Renderer3D.h"
#include "VulkanRendererAPI.h"
#include "VulkanGraphicsContext.h"

namespace Graphite
{

	VkSampler VulkanTexture::s_CommonTextureSampler;
	VkDescriptorSetLayout VulkanTexture::s_TextureSamplerDescriptorSetLayout;
	
	VulkanTexture::VulkanTexture(const std::string& filePath): Texture()
	{
		Init(filePath);
	}

	VulkanTexture::VulkanTexture(std::istream& srcStream) : Texture()
	{
		Init(srcStream);
	}

	VulkanTexture::~VulkanTexture()
	{
		Shutdown();
	}

	void VulkanTexture::DestroyCommonSampler()
	{
		vkDestroySampler(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			s_CommonTextureSampler,
			nullptr);
	}


	void VulkanTexture::Init(const std::string& filePath)
	{
		CreateImage(filePath);
		CreateImageView();
		CreateDescriptorSet();
	}


	void VulkanTexture::Init(std::istream& srcStream)
	{
		CreateImage(srcStream);
		CreateImageView();
		CreateDescriptorSet();
	}

	void VulkanTexture::Shutdown()
	{
		vkDeviceWaitIdle(GR_GRAPHICS_CONTEXT->GetLogicalDevice());
		vkDestroyImage(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Image,
			nullptr);
		vkDestroyImageView(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_ImageView,
			nullptr);
		vkFreeDescriptorSets(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			VulkanRendererAPI::GetSamplerDescriptorPool(),
			1,
			&m_DescriptorSet);
	}

	void VulkanTexture::CreateImage(const std::string& filePath)
	{
		stbi_uc* rawData = LoadTextureFile(filePath);

		VkDeviceSize size = m_Height * m_Width * 4;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMem;
		VulkanUtilities::CreateBuffer(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&stagingBuffer,
			&stagingMem);

		void* data;
		vkMapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingMem,
			0,
			size,
			0,
			&data);
		memcpy(
			data,
			rawData,
			static_cast<size_t>(size));
		vkUnmapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingMem);

		stbi_image_free(rawData);

		m_Image = VulkanUtilities::CreateImage(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Width,
			m_Height,
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&m_ImageMemory);

		VulkanUtilities::TransitionImageLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			m_Image,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		VulkanUtilities::CopyImageBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			stagingBuffer,
			m_Image,
			m_Width,
			m_Height);

		VulkanUtilities::TransitionImageLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			m_Image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

		vkDestroyBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBuffer,
			nullptr);
		vkFreeMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingMem,
			nullptr);
	}

	void VulkanTexture::CreateImage(std::istream& srcStream)
	{
		stbi_uc* rawData = LoadTextureStream(srcStream);

		VkDeviceSize size = m_Height * m_Width * 4;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMem;
		VulkanUtilities::CreateBuffer(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&stagingBuffer,
			&stagingMem);

		void* data;
		vkMapMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingMem,
			0,
			size,
			0,
			&data);
		memcpy(
			data,
			rawData,
			static_cast<size_t>(size));
		vkUnmapMemory(GR_GRAPHICS_CONTEXT->GetLogicalDevice(), stagingMem);

		stbi_image_free(rawData);

		VulkanUtilities::CreateImage(
			GR_GRAPHICS_CONTEXT->GetPhysicalDevice(),
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Width,
			m_Height,
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&m_ImageMemory);

		VulkanUtilities::TransitionImageLayout(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			m_Image,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		VulkanUtilities::CopyImageBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			GR_GRAPHICS_CONTEXT->GetGraphicsQueue(),
			VulkanRendererAPI::GetGraphicsCommandPool(),
			stagingBuffer,
			m_Image,
			m_Width,
			m_Height);

		vkDestroyBuffer(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingBuffer,
			nullptr);
		vkFreeMemory(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			stagingMem,
			nullptr);
	}

	void VulkanTexture::CreateImageView()
	{
		m_ImageView = VulkanUtilities::CreateImageView(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			m_Image,
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_IMAGE_ASPECT_COLOR_BIT);
	}

	void VulkanTexture::CreateDescriptorSet()
	{
		
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = VulkanRendererAPI::GetSamplerDescriptorPool();
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = VulkanRendererAPI::GetSamplerDescriptorSetLayout();

		VkResult result = vkAllocateDescriptorSets(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&allocInfo,
			&m_DescriptorSet);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a texture descriptor set!");
		}

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = m_ImageView;
		imageInfo.sampler = s_CommonTextureSampler;

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = m_DescriptorSet;
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			1,
			&descriptorWrite,
			0,
			nullptr);
	}

	stbi_uc* VulkanTexture::LoadTextureFile(const std::string& filePath)
	{
		int channels;

		stbi_set_flip_vertically_on_load(true);
		
		stbi_uc * file = stbi_load(
			filePath.c_str(),
			&m_Width,
			&m_Height,
			&channels,
			STBI_rgb_alpha);

		if(!file)
		{
			throw std::runtime_error("Failed to load a Texture file (" + filePath + ")");
		}

		return file;
	}

	stbi_uc* VulkanTexture::LoadTextureStream(std::istream& srcStream)
	{
		int channels;

		std::vector<stbi_uc> bufferVec;
		srcStream.seekg(0, std::ios::end);
		bufferVec.resize(srcStream.tellg());
		srcStream.seekg(0, std::ios::beg);
		
		if (srcStream.read((char*)bufferVec.data(), bufferVec.size()))
		{
			stbi_uc* file = stbi_load_from_memory(bufferVec.data(), static_cast<int>(bufferVec.size()), &m_Width, &m_Height, &channels, STBI_rgb_alpha);

			if (!file)
			{
				throw std::runtime_error("Failed to load a Texture from stream");
			}

			return file;
		}
		else
		{
			throw std::runtime_error("Failed to load a Texture from stream");
		}
	}


	void VulkanTexture::CreateCommonSampler()
	{
		VkSamplerCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		createInfo.magFilter = VK_FILTER_LINEAR;
		createInfo.minFilter = VK_FILTER_LINEAR;
		createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.anisotropyEnable = VK_TRUE;
		createInfo.maxAnisotropy = 16;
		createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		createInfo.unnormalizedCoordinates = VK_FALSE;
		createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		createInfo.mipLodBias = 0.0f;
		createInfo.minLod = 0.0f;
		createInfo.maxLod = 0.0f;

		VkResult result = vkCreateSampler(
			GR_GRAPHICS_CONTEXT->GetLogicalDevice(),
			&createInfo,
			nullptr,
			&s_CommonTextureSampler);

		if(result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a texture sampler!");
		}
	}

}


#endif
