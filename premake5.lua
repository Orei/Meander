workspace "Meander"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }
    defines { "_CRT_SECURE_NO_WARNINGS" }
    startproject "Sandbox"

    cfgoutdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    targetdir "Binaries/%{cfgoutdir}/%{prj.name}/"
    objdir "Intermediate/%{cfgoutdir}/%{prj.name}/"

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"
        pic "on"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    group "Dependencies"
        include "Meander/Dependencies/glad"
        include "Meander/Dependencies/glfw"
        include "Meander/Dependencies/imgui"

    group ""

project "Meander"
    location "Meander"
    kind "StaticLib"
    pchheader "pch.h"
    pchsource "%{prj.name}/Source/pch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.inl",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Dependencies/glm/glm/**.hpp",
        "%{prj.name}/Dependencies/glm/glm/**.inl",
        "%{prj.name}/Dependencies/stb/**.h",
        "%{prj.name}/Dependencies/stb/**.cpp",
    }

    links
    {
        "opengl32.lib",
        "glad",
        "glfw",
        "imgui"
    }

    includedirs
    {
        "%{prj.name}/Source/",
        "%{prj.name}/Dependencies/glad/include/",
        "%{prj.name}/Dependencies/glfw/include/",
        "%{prj.name}/Dependencies/glm/",
        "%{prj.name}/Dependencies/spdlog/include/",
        "%{prj.name}/Dependencies/stb/",
        "%{prj.name}/Dependencies/imgui/",
    }

    filter "system:windows"
        defines { "GLFW_INCLUDE_NONE" }

    filter "configurations:Debug"
        defines { "MN_DEBUG" }

    filter "configurations:Release"
        defines { "MN_RELEASE" }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    links { "Meander" }

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/Source/",

        "Meander/Source",
        "Meander/Dependencies/",
        "Meander/Dependencies/glm/",
        "Meander/Dependencies/spdlog/include/",
    }