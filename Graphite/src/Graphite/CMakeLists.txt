add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Assets")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Core")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/EventCore")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Math")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Renderer")

set(
        GRAPHITE_SOURCE_FILES
        "${ASSET_SOURCES}"
        "${CORE_SOURCES}"
        "${EVENT_CORE_SOURCES}"
        "${MATH_SOURCES}"
        "${RENDERER_SOURCES}"
        CACHE INTERNAL "" FORCE
)

set(
        GRAPHITE_HEADER_FILES
        "${ASSET_HEADERS}"
        "${CORE_HEADERS}"
        "${EVENT_CORE_HEADERS}"
        "${MATH_HEADERS}"
        "${RENDERER_HEADERS}"
        CACHE INTERNAL  "" FORCE
)