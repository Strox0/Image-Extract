outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

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

include "vendor/IMAF/IMAF"

project "ImageExtract"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")

	includedirs {
		"vendor/IMAF/IMAF/src",
		"src/",
		"vendor/IMAF/vendor/imgui",
		"vendor/opencv/include"
	}

	files {
		"src/**.cpp",
		"src/**.h",
		"src/**.c"
	}

	links {
		"IMAF"
	}

	filter "configurations:Debug"
			libdirs {
				"vendor/opencv/libs/Debug"
			}
      links {
      	"gif.lib",
				"jpeg.lib",
				"libpng16d.lib",
				"libsharpyuv.lib",
				"libwebp.lib",
				"lzma.lib",
				"opencv_calib3d4d.lib",
				"opencv_core4d.lib",
				"opencv_dnn4d.lib",
				"opencv_features2d4d.lib",
				"opencv_flann4d.lib",
				"opencv_highgui4d.lib",
				"opencv_imgcodecs4d.lib",
				"opencv_imgproc4d.lib",
				"opencv_ml4d.lib",
				"opencv_objdetect4d.lib",
				"opencv_photo4d.lib",
				"opencv_stitching4d.lib",
				"opencv_video4d.lib",
				"opencv_videoio4d.lib",
				"openjp2.lib",
				"tiffd.lib",
				"turbojpeg.lib",
				"zlibd.lib"
      }

	filter "configurations:Release"
			libdirs {
				"vendor/opencv/libs/Release"
			}
      links {
      	"gif.lib",
				"jpeg.lib",
				"libpng16.lib",
				"libsharpyuv.lib",
				"libwebp.lib",
				"lzma.lib",
				"opencv_calib3d4.lib",
				"opencv_core4.lib",
				"opencv_dnn4.lib",
				"opencv_features2d4.lib",
				"opencv_flann4.lib",
				"opencv_highgui4.lib",
				"opencv_imgcodecs4.lib",
				"opencv_imgproc4.lib",
				"opencv_ml4.lib",
				"opencv_objdetect4.lib",
				"opencv_photo4.lib",
				"opencv_stitching4.lib",
				"opencv_video4.lib",
				"opencv_videoio4.lib",
				"openjp2.lib",
				"tiff.lib",
				"turbojpeg.lib",
				"zlib.lib"
      }