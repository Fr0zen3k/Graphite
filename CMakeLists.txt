cmake_minimum_required(VERSION 3.20.0)

# Graphite version 0.2 - first to use cmake
project(Graphite VERSION 0.2)

# C++ standards, version, architecture etc.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_GENERATOR_PLATFORM x64)


# Platform specific operations (only Windows for now)
if (WIN32)
	# Find Vulkan (and DX12/11 in the future)
	find_package(Vulkan REQUIRED FATAL_ERROR)
endif (WIN32)


# Add the header and source files of Graphite
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Graphite/src")


# Compile dependencies
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor")

# Combine all files
set(
	GRAPHITE_FILES
	"${GRAPHITE_SOURCES}"
	"${GRAPHITE_HEADERS}"
	CACHE INTERNAL "" FORCE
	)

message("${GRAPHITE_FILES}")

# Create the shared library
add_library(
	Graphite
	SHARED
	${GRAPHITE_FILES}
	)



# Link the libraries
target_link_libraries(Graphite ${VULKAN_LIB_LIST})
target_link_libraries(Graphite assimp)
target_link_libraries(Graphite glfw)
target_link_libraries(Graphite glm)
target_link_libraries(Graphite RapidJSON)
	
	
# Add preprocessor defines
target_compile_definitions(Graphite PRIVATE GLFW_INCLUDE_VULKAN)
target_compile_definitions(Graphite PUBLIC _USE_MATH_DEFINES)


# Add include directories
# TODO: cleanup
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/src")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/spdlog/include")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/glfw/include")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/glm")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/imgui")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/RapidJSON/include")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/STBI")
target_include_directories(Graphite PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Graphite/vendor/assimp/include")
