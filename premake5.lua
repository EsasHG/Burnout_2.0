
workspace "Burnout_2.0"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDirs = {}
	IncludeDirs["GLFW"] = "Burnout_2.0/vendor/GLFW/include"
	IncludeDirs["Glad"] = "Burnout_2.0/vendor/Glad/include"
	IncludeDirs["ImGui"] = "Burnout_2.0/vendor/imgui"
	IncludeDirs["glm"] = "Burnout_2.0/vendor/glm"
	
	group "Dependencies"
		include "Burnout_2.0/vendor/GLFW"
		include "Burnout_2.0/vendor/Glad"
		include "Burnout_2.0/vendor/imgui"
	
	

	group ""

project "Burnout_2.0"
	location "Burnout_2.0"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}");
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}");

	pchheader "bopch.h"
	pchsource "Burnout_2.0/src/bopch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}"

	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BO_PLATFORM_WINDOWS",
			"BO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}");
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}");

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Burnout_2.0/vendor/spdlog/include",
		"Burnout_2.0/src",
		"Burnout_2.0/vendor",
		"%{IncludeDirs.glm}"
	}

	links 
	{
		"Burnout_2.0"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BO_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"