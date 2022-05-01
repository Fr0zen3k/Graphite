add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Management")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/MeshCore")

set(
        ASSET_SOURCES
        "${MANAGEMENT_SOURCES}"
        "${MESH_CORE_SOURCES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Material.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp"
        CACHE INTERNAL  "" FORCE
)

set(
        ASSET_HEADERS
        "${MANAGEMENT_HEADERS}"
        "${MESH_CORE_HEADERS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Material.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/GameObject.h"
        CACHE INTERNAL  "" FORCE
)