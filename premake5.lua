workspace "Graphite"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Graphite"
	location "Graphite"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/glfw-3.3.2.bin.WIN64/include/",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/Vulkan/1.2.148.1/Include/"
	}
	
	libdirs 
	{
		"%{prj.name}/vendor/glfw-3.3.2.bin.WIN64/lib-vc2019",
		"%{prj.name}/vendor/Vulkan/1.2.148.1/Lib"
	}
	
	links 
	{
		"glfw3",
		"vulkan-1"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines	
		{
			"GR_PLATFORM_WINDOWS",
			"GR_BUILD_DLL"
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
		"Graphite/vendor/glfw-3.3.2.bin.WIN64/include/",
		"Graphite/vendor/glm",
		"Graphite/vendor/Vulkan/1.2.148.1/Include/"
	}

	links 
	{
		"Graphite" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GR_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GR_DIST"
		optimize "On"