add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Graphite")

set(
        GRAPHITE_SOURCES
        "${GRAPHITE_SOURCE_FILES}"
        CACHE INTERNAL "" FORCE
)

set(
        GRAPHITE_HEADERS
        "${GRAPHITE_HEADER_FILES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Graphite.h"
        CACHE INTERNAL  "" FORCE
)