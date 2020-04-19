workspace "LNG"
    architecture "x86_64"

    startproject "LNG"

    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["FMT"] = "PersonalCUtils/vendor/fmt/include"


project "PersonalCUtils"
    location "PersonalCUtils"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir    ("bin-int/%{prj.name}/" .. outputdir)

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/src/vendor/**.cc"
    }

    includedirs {
        "PersonalCUtils/src/",
		"%{IncludeDir.FMT}"
    }

    pchheader "pcpch.h"
    pchsource "PersonalCUtils/src/pcpch.cpp"

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
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/%{prj.name}/" .. outputdir)
    objdir    ("bin-int/%{prj.name}/" .. outputdir)
    
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs {
        "PersonalCUtils/src/",
		"%{IncludeDir.FMT}"
    }

    libdirs {
        "bin/PersonalCUtils/" .. outputdir .. "/"
    }

    links {
        "PersonalCUtils",
        "PersonalCUtils.lib"
    }

    filter "system:windows"
        cppdialect "C++Latest"
        systemversion "latest"
    
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
