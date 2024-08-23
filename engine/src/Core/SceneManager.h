#pragma once

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#include <flecs.h>
#include <flecs/addons/cpp/mixins/app/builder.hpp>
#include <flecs/addons/cpp/world.hpp>
#include <flecs/addons/meta.h>

#include <string>



namespace Engine {

    class SceneManager {
        public:
            struct AppSettings {};
        public:
            SceneManager();
            SceneManager(AppSettings settings);
            SceneManager(std::string settings);
            ~SceneManager() = default;

            void LoadScene(std::string name, std::string scene);
            void UnloadScene(std::string name);
        public:
            flecs::world m_World;
            flecs::app_builder m_App;
    };
}