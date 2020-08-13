workspace "NexEngine"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "NexEngine/vendor/GLFW/include"
IncludeDir["glad"] = "NexEngine/vendor/glad/include"

include "NexEngine/vendor/GLFW"
include "NexEngine/vendor/glad"

project "NexEngine"
	location "NexEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nexpch.h"
	pchsource "NexEngine/Src/nexpch.cpp"

	files {
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}

	includedirs {
		"%{prj.name}/Src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}"
	}

	links{
		"GLFW",
		"glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		defines {
			"NEX_PLATFORM_WINDOWS",
			"NEX_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NEX_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "NEX_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "NEX_DIST"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}

	includedirs {
		"NexEngine/vendor/spdlog/include",
		"NexEngine/Src"
	}

	links {
		"NexEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		defines {
			"NEX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NEX_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "NEX_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "NEX_DIST"
		optimize "on"