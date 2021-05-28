#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifdef GRAPHITE_RENDERER_VULKAN

#ifndef GRAPHITE_UTILS_H
#define GRAPHITE_UTILS_H

#include "GLFW/glfw3.h"
#include "Graphite/Core/grpch.h"
#include "glm/glm.hpp"

namespace Graphite
{
	namespace VulkanUtilities
	{
		struct PushConstantsData
		{
			glm::mat4 model;
			glm::mat4 normal;
			glm::vec4 ambient;
			glm::vec4 specular;
			glm::vec4 light;
			glm::vec4 phongData;
		};
		
		struct QueueFamilies
		{
			int GraphicsFamily = -1;
			int PresentationFamily = -1;

			inline bool areFamiliesValid()
			{
				if(GraphicsFamily >= 0 && PresentationFamily >= 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		struct SwapchainInfo
		{
			VkSurfaceCapabilitiesKHR m_SurfaceCapabilities;
			std::vector<VkSurfaceFormatKHR>  m_SurfaceFormats;
			std::vector<VkPresentModeKHR> m_PresentModes;

			// Further extend and allow definition of color class based on the formats
			inline VkSurfaceFormatKHR ChooseBestSurfaceFormat()
			{
				if (m_SurfaceFormats.size() == 1 && m_SurfaceFormats[0].format == VK_FORMAT_UNDEFINED)
				{
					return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
				}

				for (const auto& format : m_SurfaceFormats)
				{
					if ((format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
						&& format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
					{
						return format;
					}
				}

				return m_SurfaceFormats[0];
			}

			inline VkPresentModeKHR ChooseBestPresentMode()
			{
				for (const auto& presentationMode : m_PresentModes)
				{
					if (presentationMode == VK_PRESENT_MODE_MAILBOX_KHR)
					{
						return presentationMode;
					}
				}

				return VK_PRESENT_MODE_FIFO_KHR;
			}

			inline VkExtent2D ChooseSwapchainExtent(GLFWwindow * window)
			{
				if (m_SurfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
				{
					return m_SurfaceCapabilities.currentExtent;
				}
				else
				{
					int width, height;
					glfwGetFramebufferSize(window, &width, &height);

					VkExtent2D newExtent = {};
					newExtent.width = static_cast<uint32_t>(width);
					newExtent.height = static_cast<uint32_t>(height);

					newExtent.width = std::max(
						m_SurfaceCapabilities.minImageExtent.width,
						std::min(
							m_SurfaceCapabilities.maxImageExtent.width,
							newExtent.width));
					newExtent.height = std::max(
						m_SurfaceCapabilities.minImageExtent.height,
						std::min(
							m_SurfaceCapabilities.maxImageExtent.height,
							newExtent.height));

					return newExtent;
				}
			}
		};

		static SwapchainInfo GetSwapchainDetails(
			VkPhysicalDevice device,
			VkSurfaceKHR surface)
		{
			SwapchainInfo info;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
				device,
				surface,
				&info.m_SurfaceCapabilities);

			uint32_t count = 0;
			vkGetPhysicalDeviceSurfacePresentModesKHR(
				device,
				surface,
				&count,
				nullptr);

			if(count > 0)
			{
				info.m_PresentModes.resize(count);
				vkGetPhysicalDeviceSurfacePresentModesKHR(
					device,
					surface,
					&count,
					info.m_PresentModes.data());
			}

			count = 0;

			vkGetPhysicalDeviceSurfaceFormatsKHR(
				device,
				surface,
				&count,
				nullptr);

			if(count > 0)
			{
				info.m_SurfaceFormats.resize(count);
				vkGetPhysicalDeviceSurfaceFormatsKHR(
					device,
					surface,
					&count,
					info.m_SurfaceFormats.data());
			}

			return info;
		}

		static VkFormat ChooseSupportedFormat(
			VkPhysicalDevice device,
			const std::vector<VkFormat>& formats,
			VkImageTiling tiling,
			VkFormatFeatureFlagBits fetureFlags)
		{
			for(VkFormat f : formats)
			{
				VkFormatProperties props;
				vkGetPhysicalDeviceFormatProperties(
					device,
					f,
					&props);
				
				if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & fetureFlags) == fetureFlags)
				{
					return f;
				}
				else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & fetureFlags) == fetureFlags)
				{
					return f;
				}
			}

			throw std::runtime_error("Failed to find a supported format!");
		}

		static bool CheckInstanceExtensions(std::vector<const char*>& extensions)
		{
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(
				nullptr,
				&extensionCount,
				nullptr);

			std::vector<VkExtensionProperties> supportedExtensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(
				nullptr,
				&extensionCount,
				supportedExtensions.data());

			for (const auto& checkExtension : extensions)
			{
				bool supported = false;

				for (const auto& extension : supportedExtensions)
				{
					if (strcmp(checkExtension, extension.extensionName) == 0)
					{
						supported = true;
						break;
					}
				}

				if (!supported)
				{
					return false;
				}
			}

			return true;
		}

		static int RatePhysicalDevice(VkPhysicalDevice device)
		{
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;

			vkGetPhysicalDeviceProperties(
				device,
				&properties);
			vkGetPhysicalDeviceFeatures(
				device,
				&features);

			int score = 0;

			if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				score += 1000;
			}

			score += properties.limits.maxImageDimension2D;

			if (!features.geometryShader)
			{
				return 0;
			}

			return score;
		}

		static uint32_t FindMemoryTypeIndex(
			VkPhysicalDevice physicalDevice,
			uint32_t types,
			VkMemoryPropertyFlags properties)
		{
			VkPhysicalDeviceMemoryProperties memProps;

			vkGetPhysicalDeviceMemoryProperties(
				physicalDevice,
				&memProps);

			for(uint32_t i = 0; i < memProps.memoryTypeCount; i++)
			{
				if((types & (1 << i)) && (memProps.memoryTypes[i].propertyFlags & properties) == properties)
				{
					return i;
				}
			}

			throw std::runtime_error("Failed to find suitable memory type on the physical device!");
		}
		
		static void CreateBuffer(
			VkPhysicalDevice physicalDevice,
			VkDevice device,
			VkDeviceSize bufferSize,
			VkBufferUsageFlags bufferUsage,
		    VkMemoryPropertyFlags bufferProperties,
			VkBuffer* buffer,
			VkDeviceMemory* bufferMemory)
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = bufferSize;
			bufferInfo.usage = bufferUsage;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			VkResult result = vkCreateBuffer(
				device,
				&bufferInfo,
				nullptr,
				buffer);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create a Vertex Buffer!");
			}

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(
				device,
				*buffer,
				&memRequirements);
			
			VkMemoryAllocateInfo memoryAllocInfo = {};
			memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			memoryAllocInfo.allocationSize = memRequirements.size;
			memoryAllocInfo.memoryTypeIndex = FindMemoryTypeIndex(physicalDevice, memRequirements.memoryTypeBits,
			                                                      bufferProperties);
		
			result = vkAllocateMemory(
				device,
				&memoryAllocInfo,
				nullptr,
				bufferMemory);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to allocate Vertex Buffer Memory!");
			}

			vkBindBufferMemory(
				device,
				*buffer,
				*bufferMemory,
				0);
		}

		static VkCommandBuffer BeginCommandBuffer(
			VkDevice device,
			VkCommandPool commandPool)
		{
			VkCommandBuffer commandBuffer;

			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandPool = commandPool;
			allocInfo.commandBufferCount = 1;

			vkAllocateCommandBuffers(
				device,
				&allocInfo,
				&commandBuffer);

			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			vkBeginCommandBuffer(
				commandBuffer,
				&beginInfo);

			return commandBuffer;
		}

		static void EndAndSubmitCommandBuffer(
			VkDevice device,
			VkCommandPool commandPool,
			VkQueue queue,
			VkCommandBuffer commandBuffer)
		{
			vkEndCommandBuffer(commandBuffer);

			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &commandBuffer;

			vkQueueSubmit(
				queue,
				1,
				&submitInfo,
				VK_NULL_HANDLE);
			vkQueueWaitIdle(queue);

			vkFreeCommandBuffers(
				device,
				commandPool,
				1,
				&commandBuffer);
		}

		static void CopyBuffer(
			VkDevice device,
			VkQueue transferQueue,
			VkCommandPool transferCommandPool,
		    VkBuffer srcBuffer,
			VkBuffer dstBuffer,
			VkDeviceSize bufferSize)
		{
			VkCommandBuffer transferCommandBuffer = BeginCommandBuffer(
				device,
				transferCommandPool);

			VkBufferCopy bufferCopyRegion = {};
			bufferCopyRegion.srcOffset = 0;
			bufferCopyRegion.dstOffset = 0;
			bufferCopyRegion.size = bufferSize;

			vkCmdCopyBuffer(
				transferCommandBuffer,
				srcBuffer,
				dstBuffer,
				1,
				&bufferCopyRegion);

			EndAndSubmitCommandBuffer(
				device,
				transferCommandPool,
				transferQueue,
				transferCommandBuffer);
		}

		static VkImage CreateImage(
			VkPhysicalDevice physicalDevice,
			VkDevice logicalDevice,
			uint32_t width,
			uint32_t height,
			VkFormat format, 
		    VkImageTiling imageTiling,
			VkImageUsageFlags imageFlags,
			VkMemoryPropertyFlags memoryFlags,
			VkDeviceMemory* pImageMemory)
		{
			VkImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.extent.width = width;
			imageCreateInfo.extent.height = height;
			imageCreateInfo.extent.depth = 1;
			imageCreateInfo.mipLevels = 1;	// Add functionality in the future
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.format = format;
			imageCreateInfo.tiling = imageTiling;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.usage = imageFlags;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			VkImage image;
		
			VkResult result = vkCreateImage(
				logicalDevice,
				&imageCreateInfo,
				nullptr,
				&image);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create an Image!");
			}

			VkMemoryRequirements memoryRequirements;
			vkGetImageMemoryRequirements(
				logicalDevice,
				image,
				&memoryRequirements);
			
			VkMemoryAllocateInfo memoryAllocInfo = {};
			memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			memoryAllocInfo.allocationSize = memoryRequirements.size;
			memoryAllocInfo.memoryTypeIndex = FindMemoryTypeIndex(
				physicalDevice,
				memoryRequirements.memoryTypeBits,
				memoryFlags);

			result = vkAllocateMemory(
				logicalDevice,
				&memoryAllocInfo,
				nullptr,
				pImageMemory);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to allocate memory for image!");
			}

			vkBindImageMemory(
				logicalDevice,
				image,
				*pImageMemory,
				0);

			return image;
		}

		static VkImageView CreateImageView(
			VkDevice logicalDevice,
			VkImage image,
			VkFormat format,
			VkImageAspectFlags aspectFlags)
		{
			VkImageViewCreateInfo viewCreateInfo = {};
			viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewCreateInfo.image = image;
			viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewCreateInfo.format = format;
			viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			viewCreateInfo.subresourceRange.aspectMask = aspectFlags;
			viewCreateInfo.subresourceRange.baseMipLevel = 0;
			viewCreateInfo.subresourceRange.levelCount = 1;
			viewCreateInfo.subresourceRange.baseArrayLayer = 0;
			viewCreateInfo.subresourceRange.layerCount = 1;

			VkImageView imageView;

			VkResult result = vkCreateImageView(
				logicalDevice,
				&viewCreateInfo,
				nullptr,
				&imageView);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create an Image View!");
			}
			
			return imageView;
		}

		static void TransitionImageLayout(
			VkDevice device,
			VkQueue queue,
			VkCommandPool commandPool,
			VkImage image,
			VkImageLayout oldLayout,
			VkImageLayout newLayout)
		{
			VkCommandBuffer commandBuffer = BeginCommandBuffer(
				device,
				commandPool);

			VkImageMemoryBarrier imageMemoryBarrier = {};
			imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			imageMemoryBarrier.oldLayout = oldLayout;
			imageMemoryBarrier.newLayout = newLayout;
			imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			imageMemoryBarrier.image = image;
			imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
			imageMemoryBarrier.subresourceRange.levelCount = 1;
			imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
			imageMemoryBarrier.subresourceRange.layerCount = 1;

			VkPipelineStageFlags srcStage;
			VkPipelineStageFlags dstStage;

			if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
			{
				imageMemoryBarrier.srcAccessMask = 0;
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

				srcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			}
			else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
			{
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

				srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				dstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			}

			vkCmdPipelineBarrier(
				commandBuffer,
				srcStage,
				dstStage,
				0,
				0,
				nullptr,
				0,
				nullptr,
				1,
				&imageMemoryBarrier);

			EndAndSubmitCommandBuffer(
				device,
				commandPool,
				queue,
				commandBuffer);
		}

		static void CopyImageBuffer(
			VkDevice device,
			VkQueue transferQueue,
			VkCommandPool transferCommandPool,
			VkBuffer src,
			VkImage dst,
			uint32_t width,
			uint32_t height)
		{
			VkCommandBuffer transferCommandBuffer = BeginCommandBuffer(
				device,
				transferCommandPool);

			VkBufferImageCopy imageRegion = {};
			imageRegion.bufferOffset = 0;
			imageRegion.bufferRowLength = 0;
			imageRegion.bufferImageHeight = 0;
			imageRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageRegion.imageSubresource.mipLevel = 0;
			imageRegion.imageSubresource.baseArrayLayer = 0;
			imageRegion.imageSubresource.layerCount = 1;
			imageRegion.imageOffset = { 0, 0, 0 };
			imageRegion.imageExtent = { width, height, 1 };

			vkCmdCopyBufferToImage(
				transferCommandBuffer,
				src,
				dst,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1,
				&imageRegion);

			EndAndSubmitCommandBuffer(
				device,
				transferCommandPool,
				transferQueue,
				transferCommandBuffer);
		}
	}
}

#endif

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif