add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Benchmarking")

set(
        CORE_SOURCES
        "${BENCHMARKING_SOURCES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Layer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        CORE_HEADERS
        "${BENCHMARKING_HEADERS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Application.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/grpch.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Input.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Layer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Log.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Utilities.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Window.h"
        CACHE INTERNAL  "" FORCE
)