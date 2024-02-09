    -- premake5.lua
workspace "PotatoGameEngine"
    configurations { "Debug", "Release" }

project "Engine"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/engine/%{cfg.buildcfg}"

    filter { "system:windows" }
    --prebuildcommands { 'Get-ChildItem .\\engine\\ -Recurse -Filter "*.cpp" | ForEach-Object { & .\\makeheaders.exe $_.FullName }' }

    files { "./engine/**.hpp", "./engine/**.cpp" }

    includedirs { "./vcpkg/installed/x64-windows/include" }
    libdirs { "./vcpkg/installed/x64-windows/lib" }
    --links {  }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Sandbox"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/sandbox/%{cfg.buildcfg}"

    files { "./sandbox/**.hpp", "./sandbox/**.cpp" }

    includedirs { "./vcpkg/installed/x64-windows/include" }
    libdirs { "./vcpkg/installed/x64-windows/lib" }
    --links {  }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
