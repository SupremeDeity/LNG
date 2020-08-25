workspace "LNG"
    architecture "x86_64"

    startproject "Example"

    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"
IncludeDir = {}


project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir    ("bin-int/%{prj.name}/" .. outputdir)

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/src/vendor/**.cc"
    }

    includedirs {
        "LNG/src/",
    }
	
	libdirs {
        "bin/LNG/" .. outputdir .. "/"
    }
	
	links {
        "LNG",
        "LNG.lib"
    }

    filter "system:windows"
        cppdialect "C++Latest"
        systemversion "latest"

        defines {
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"

project "LNG"
    location "LNG"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir    ("bin-int/%{prj.name}/" .. outputdir)
    
	includedirs {
        "LNG/src/",
    }
	
	pchheader "lngpch.h"
    pchsource "LNG/src/lngpch.cpp"
	
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    filter "system:windows"
        cppdialect "C++Latest"
        systemversion "latest"
		
		 defines {
            "PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
