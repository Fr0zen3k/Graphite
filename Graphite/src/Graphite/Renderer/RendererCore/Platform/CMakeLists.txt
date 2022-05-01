add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Direct3D")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/GNMX")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Metal")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/OpenGL")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Vulkan")

set(
        PLATFORM_SOURCES
        "${DIRECT3D_SOURCES}"
        "${GNMX_SOURCES}"
        "${METAL_SOURCES}"
        "${OPENGL_SOURCES}"
        "${VULKAN_SOURCES}"
        CACHE INTERNAL "" FORCE
)

set(
        PLATFORM_HEADERS
        "${DIRECT3D_HEADERS}"
        "${GNMX_HEADERS}"
        "${METAL_HEADERS}"
        "${OPENGL_HEADERS}"
        "${VULKAN_HEADERS}"
        CACHE INTERNAL  "" FORCE
)