workspace "Graphite"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Graphite/vendor/imgui"

project "Graphite"
	location "Graphite"
	kind "SharedLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "off"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	pchheader "Graphite/Core/grpch.h"
	pchsource "Graphite/src/Graphite/Core/grpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/spdlog/**.h",
		"%{prj.name}/vendor/spdlog/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include/",
		"%{prj.name}/src/",
		"%{prj.name}/vendor/glfw_x64/include/",
		"%{prj.name}/vendor/glm",
		"C:/VulkanSDK/1.2.148.1/Include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/RapidJSON/include",
		"%{prj.name}/vendor/STBI"
	}

	libdirs
	{
		"C:/VulkanSDK/1.2.148.1/Lib",
		"%{prj.name}/vendor/glfw_x64/lib-vc2019"
	}

	links
	{
		"vulkan-1",
		"ImGui",
		"glfw3"
	}

	defines
	{
		"GLFW_INCLUDE_VULKAN",
		"GLM_FORCE_DEPTH_ZERO_TO_ONE"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GR_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
			"GR_BUILD_DLL",
			"GRAPHITE_RENDERER_VULKAN"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines
		{
			"GR_DEBUG",
			"GR_ENABLE_ASSERT"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"GR_RELEASE",
			"GR_ENABLE_ASSERT"
		}

		optimize "On"

	filter "configurations:Dist"
		defines "GR_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/spdlog/**.h",
		"%{prj.name}/vendor/spdlog/**.cpp"
	}

	includedirs
	{
		"Graphite/vendor/spdlog/include/",
		"Graphite/src/",
		"Graphite/vendor/glfw_x64/include/",
		"Graphite/vendor/glm",
		"Graphite/vendor/Vulkan/1.2.148.1/Include/",
		"C:/VulkanSDK/1.2.148.1/Include",
		"Graphite/vendor/imgui",
		"Graphite/vendor/STBI",
		"Graphite/vendor/RapidJSON/include",
		"Graphite/vendor/imgui"
	}
	links
	{
		"Graphite"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GR_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "GR_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "GR_DIST"
		optimize "on"
