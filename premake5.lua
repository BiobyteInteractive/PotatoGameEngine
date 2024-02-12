workspace "PotatoGameengine"
    configurations { "Debug", "Release" }
    architecture "x64"
    startproject "sandbox"

include "engine/premake5.lua"
include "sandbox/premake5.lua"
