project "ImGui"

kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir ("bin/" .. outdir .. "/%{prj.name}")
objdir ("bin-int/" .. outdir .. "/%{prj.name}")

files
{
	"imconfig.h",
	"imgui.cpp",
	"imgui.h",
	"imgui_demo.cpp",
	"imgui_draw.cpp",
	"imgui_internal.h",
	"imgui_widgets.cpp",
	"imstb_rectpack.h",
	"imstb_textedit.h",
	"imstb_truetype.h"
}

filter "system:windowss"
	systemversion "latest"
	
filter "system:linux"
	pic "on"
	systemversion "latest"
	
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
	
filter "configurations:Release"
	runtime "Release"
	optimize "on"
