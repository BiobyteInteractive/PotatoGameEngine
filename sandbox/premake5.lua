project "sandbox"
    kind "ConsoleApp"
    dependson { "engine" }
    language "C++"

    targetdir "../bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files { "./src/**.hpp", "./src/**.cpp" }

    includedirs { "%{wks.location}/vcpkg/installed/x64-windows/include", "%{wks.location}/engine/src" }
    libdirs { "%{wks.location}/vcpkg/installed/x64-windows/lib" }
    links { "engine", "glfw3dll" }

    filter { "system:windows" }
        cppdialect "C++20"
        prebuildcommands { 'PowerShell "Get-ChildItem %{prj.location}\\src\\ -Recurse -Filter "*.cpp" | ForEach-Object { & makeheaders $_.FullName }"' }

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