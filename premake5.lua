workspace "Spotlight"
	architecture "x64"
	startproject "CenterStage"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Spotlight/vendor/GLFW"
include "Spotlight/vendor/Glad"
include "Spotlight/vendor/ImGui"

project "Spotlight"
	location "Spotlight"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "splpch.h"
	pchsource "Spotlight/src/splpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SPL_PLATFORM_WINDOWS",
			"SPL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/CenterStage/\"")
		}

		links
		{
			"Glad",
			"GLFW",
			"ImGui",
			"opengl32.lib"
		}
		
	filter "configurations:Debug"
		defines "SPL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SPL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SPL_DIST"
		runtime "Release"
		optimize "On"

project "CenterStage"
	location "CenterStage"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Spotlight/src",
		"Spotlight/vendor/spdlog/include"
	}

	links
	{
		"Spotlight"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SPL_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SPL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SPL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SPL_DIST"
		runtime "Release"
		optimize "On"