add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Color")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Platform")

set(
        RENDERER_CORE_SOURCES
        "${COLOR_SOURCES}"
        "${PLATFORM_SOURCES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Framebuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/GraphicsContext.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        RENDERER_CORE_HEADERS
        "${COLOR_HEADERS}"
        "${PLATFORM_HEADERS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Camera.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Framebuffer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/GraphicsContext.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Texture.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Utilities.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.h"
        CACHE INTERNAL  "" FORCE
)