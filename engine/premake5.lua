project "engine"
    kind "SharedLib"
    language "C++"

    targetdir "../bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files { "./src/**.hpp", "./src/**.cpp" }

    includedirs { "%{wks.location}/vendor/vcpkg/installed/x64-windows/include" }
    libdirs { "%{wks.location}/vendor/vcpkg/installed/x64-windows/lib" }
    links { "glfw3dll", "bgfx", "bimg", "bx" }

    filter { "system:windows" }
        cppdialect "C++20"
        buildoptions { "/Zc:__cplusplus", "/std:c++20" }
        includedirs { "%{wks.location}/vendor/vcpkg/installed/x64-windows/include/bx/compat/msvc" }
        prebuildcommands { 'PowerShell "Get-ChildItem %{prj.location}\\src\\ -Recurse -Filter "*.cpp" | ForEach-Object { & %{wks.location}/vendor/windows/makeheaders/makeheaders.exe $_.FullName }"' }
        postbuildcommands { "{COPY} ../bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/*.dll ../bin/sandbox/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" }
        
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

