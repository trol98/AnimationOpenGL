workspace "AnimationOpenGL"
	architecture "x86"
	startproject "TerrainGen"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Dependencies/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Dependencies/Glad/include"


project "AnimationOpenGL"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{	
		"%{wks.location}/AnimationOpenGL/res/**.**",
		"%{wks.location}/AnimationOpenGL/src/*.h",
		"%{wks.location}/AnimationOpenGL/src/*.cpp",
		"%{wks.location}/AnimationOpenGL/src/vendor/glm/glm/**.hpp",
		"%{wks.location}/AnimationOpenGL/src/vendor/glm/glm/**.inl",
	}

	defines
	{
		"GLEW_STATIC"
	}

	includedirs
	{
		"vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"OpenGL32.lib",
		"User32.lib",
		"gdi32.lib",
		"Shell32.lib"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

group "Dependencies"
	include "AnimationOpenGL/src/vendor/premake"
	include "Dependencies/GLFW"
	include "Dependencies/Glad"
group ""




