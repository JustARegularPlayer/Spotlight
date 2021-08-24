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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "splpch.h"
	pchsource "Spotlight/src/splpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/glm/glm/**.h",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/ImGui",
		"%{prj.name}/vendor/glm"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SPL_PLATFORM_WINDOWS",
			"SPL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
		symbols "on"

	filter "configurations:Release"
		defines "SPL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SPL_DIST"
		runtime "Release"
		optimize "on"

project "CenterStage"
	location "CenterStage"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Spotlight/src",
		"Spotlight/vendor/spdlog/include",
		"Spotlight/vendor/ImGui",
		"Spotlight/vendor/glm"
	}

	links
	{
		"Spotlight"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SPL_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SPL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SPL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SPL_DIST"
		runtime "Release"
		optimize "on"