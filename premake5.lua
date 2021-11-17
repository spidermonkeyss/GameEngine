workspace "OpenGL"
	configurations { "Debug", "Release" }

project "OpenGL"
	location "OpenGL"
	language "C++"
	kind "ConsoleApp"

	targetdir ("OpenGL")
	objdir ("obj")

	files 
	{ 
		"OpenGL/res/**.h",
		"OpenGL/res/**.hpp",
		"OpenGL/res/**.cpp",

		"OpenGL/src/*.h", 
		"OpenGL/src/*.hpp",
		"OpenGL/src/*.cpp",
		"OpenGL/src/Editor/**.h", 
		"OpenGL/src/Editor/**.hpp",
		"OpenGL/src/Editor/**.cpp",
		"OpenGL/src/vendor/glm/**.h", 
		"OpenGL/src/vendor/glm/**.hpp",
		"OpenGL/src/vendor/glm/**.cpp",
		"OpenGL/src/vendor/imgui/**.h", 
		"OpenGL/src/vendor/imgui/**.hpp",
		"OpenGL/src/vendor/imgui/**.cpp",
		"OpenGL/src/vendor/stb_image/**.h", 
		"OpenGL/src/vendor/stb_image/**.hpp",
		"OpenGL/src/vendor/stb_image/**.cpp",
		"OpenGL/src/vendor/yaml-cpp-master/src/**.h",
		"OpenGL/src/vendor/yaml-cpp-master/src/**.cpp",
		"OpenGL/src/vendor/yaml-cpp-master/include/**.h"
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