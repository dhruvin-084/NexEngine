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
IncludeDir["spdlog"] = "NexEngine/vendor/spdlog/include"
IncludeDir["GLFW"] = "NexEngine/vendor/GLFW/include"
IncludeDir["glad"] = "NexEngine/vendor/glad/include"
IncludeDir["ImGui"] = "NexEngine/vendor/ImGui"
IncludeDir["glm"] = "NexEngine/vendor/glm"

include "NexEngine/vendor/GLFW"
include "NexEngine/vendor/glad"
include "NexEngine/vendor/ImGui"

project "NexEngine"
	location "NexEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines {
			"NEX_PLATFORM_WINDOWS",
			"NEX_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
		}

	filter "configurations:Debug"
		defines "NEX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NEX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEX_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}

	includedirs {
		"%{IncludeDir.spdlog}",
		"NexEngine/Src",
		"%{IncludeDir.glm}"
	}

	links {
		"NexEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines {
			"NEX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NEX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NEX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEX_DIST"
		runtime "Release"
		optimize "On"