add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Renderer2D")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Renderer3D")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RendererCore")

set(
        RENDERER_SOURCES
        "${RENDERER_2D_SOURCES}"
        "${RENDERER_3D_SOURCES}"
        "${RENDERER_CORE_SOURCES}"
        CACHE INTERNAL "" FORCE
)

set(
        RENDERER_HEADERS
        "${RENDERER_2D_HEADERS}"
        "${RENDERER_3D_HEADERS}"
        "${RENDERER_CORE_SOURCES}"
        CACHE INTERNAL  "" FORCE
)