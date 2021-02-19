workspace "OpenGL"
	configurations { "Debug", "Release" }

project "OpenGL"
	location "OpenGL"
	language "C++"
	kind "ConsoleApp"

	targetdir ("bin")
	objdir ("obj")

	files 
	{ 
		"**.h", 
		"**.hpp",
		"**.cpp"
	}

	includedirs
	{
		"%{prj.name}/res",
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"%{prj.name}/src/vendor/yaml-cpp-master/include",
		"Dependencies/GLFW/include",
		"Dependencies/GLEW/include"
	}

	libdirs
	{
		"Dependencies/GLFW/lib-vc2015",
		"Dependencies/GLEW/lib/Release/Win32"
	}

	links
	{
		"glfw3",
		"glew32s",
		"opengl32.lib"
	}

	defines
	{
		"GLEW_STATIC",
		"_MBCS"
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