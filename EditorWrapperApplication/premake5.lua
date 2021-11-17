workspace "EditorWrapperApplication"
	configurations { "Debug", "Release" }

project "wrapper"
	location "wrapper"
	language "C++"
	kind "ConsoleApp"

	targetdir ("wrapper")
	objdir ("obj")

	files 
	{ 
		"wrapper/**.h",
		"wrapper/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"