#pragma once

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#include <flecs.h>
#include <flecs/addons/cpp/world.hpp>

namespace Engine {
    class SceneManager {
        public:
            SceneManager();
            ~SceneManager() = default;

            void LoadScene();
            void UnloadScene();
        public:
            flecs::world m_World;
    };
}