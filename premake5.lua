    -- premake5.lua
workspace "PotatoGameengine"
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "sandbox"

project "engine"
    kind "SharedLib"
    language "C++"

    targetdir "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files { "./engine/**.hpp", "./engine/**.cpp" }

    includedirs { "./vcpkg/installed/x64-windows/include" }
    libdirs { "./vcpkg/installed/x64-windows/lib" }
    links { "glfw3dll", "bgfx", "bimg", "bx" }

    filter { "system:windows" }
        cppdialect "C++17"
        prebuildcommands { 'PowerShell "Get-ChildItem .\\%{prj.name}\\ -Recurse -Filter "*.cpp" | ForEach-Object { & makeheaders $_.FullName }"' }
        --postbuildcommands { "copy bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/*.dll bin/sandbox/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" }
        
    filter "configurations:Release"
		defines
		{
			"NDEBUG",
			"BX_CONFIG_DEBUG=0"
		}
		optimize "On"
	filter "configurations:Debug*"
		defines
		{
			"_DEBUG",
            "DEBUG",
			"BX_CONFIG_DEBUG=1"
		}
		symbols "On"

project "sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    dependson { "engine" }

    files { "./sandbox/**.hpp", "./sandbox/**.cpp" }

    includedirs { "./vcpkg/installed/x64-windows/include", "./engine" }
    libdirs { "./vcpkg/installed/x64-windows/lib" }
    links { "engine", "glfw3dll" }

    filter { "system:windows" }
        cppdialect "C++17"
        prebuildcommands { 'PowerShell "Get-ChildItem .\\%{prj.name}\\ -Recurse -Filter "*.cpp" | ForEach-Object { & makeheaders $_.FullName }"' }

    filter "configurations:Release"
		defines
		{
			"NDEBUG",
			"BX_CONFIG_DEBUG=0"
		}
		optimize "On"

	filter "configurations:Debug*"
		defines
		{
			"_DEBUG",
            "DEBUG",
			"BX_CONFIG_DEBUG=1"
		}
		symbols "On"
