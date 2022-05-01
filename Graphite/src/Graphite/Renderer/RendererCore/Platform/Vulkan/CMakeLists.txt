set(
        VULKAN_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanFrameBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanGraphicsContext.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanIndexBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanOrthographicCamera.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanPerspectiveCamera.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanRendererAPI.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanShader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanTexture.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanValidator.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanVertexBuffer.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        VULKAN_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/Utils.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanFrameBuffer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanGraphicsContext.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanIndexBuffer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanOrthographicCamera.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanPerspectiveCamera.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanRendererAPI.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanShader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanTexture.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanValidator.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VulkanVertexBuffer.h"
        CACHE INTERNAL  "" FORCE
)