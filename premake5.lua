workspace "gene"
	configurations { "Debug", "Release" }
	architecture "x86_64"
	location "build"

	filter "configurations:Debug"
		defines "DEBUG"

	filter "configurations:Release"
		defines "NDEBUG"

	filter "action:vs*"
		debugdir "$(SolutionDir)"

	filter {}

include "premake5raylib"

project "genelang"
	language "C++"

	location "%{wks.location}/%{prj.name}"
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

	kind "StaticLib"

	filter {}

	vpaths
	{
		["Header Files"] = { "%{prj.name}/include/**.h" },
		["Source Files"] = { "%{prj.name}/source/**.cpp" }
	}
	files { "%{prj.name}/include/**.h", "%{prj.name}/source/**.cpp" }

	includedirs
	{
		"%{prj.name}/include"
	}

project "gene"
	language "C++"

	location "%{wks.location}/%{prj.name}"
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

	kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter {}

	vpaths
	{
		["Header Files"] = { "%{prj.name}/include/**.h" },
		["Source Files"] = { "%{prj.name}/source/**.cpp" }
	}
	files { "%{prj.name}/include/**.h", "%{prj.name}/source/**.cpp" }

	includedirs
	{
		"%{prj.name}/include",
		"genelang/include",
		"raylib/src"
	}

	links { "genelang" }
	dependson { "genelang" }

	link_raylib()