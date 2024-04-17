outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

include "vendor/IMAF/IMAF"

workspace "ImageExtract"
	architecture "x64"
	configurations {"Debug","Release"}

    filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
      systemversion "latest"

    filter "configurations:Debug"
      defines { "_DEBUG" }
      runtime "Debug"
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
      symbols "Off"

project "ImageExtract"
	kind "windows"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")

	files {
		"src/**.cpp",
		"src/**.h",
		"src/**.c"
	}

	libdirs {
		"vendor/opencv/lib"
	}

	includedirs {
		"vendor/IMAF/IMAF/src",
		"src/",
		"vendor/imgui",
		"vendor/opencv/include"
	}

	links {
		"IMAF"
	}