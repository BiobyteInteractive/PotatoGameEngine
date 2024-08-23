#include "SceneManager.h"
#include "flecs/addons/cpp/world.hpp"
#include "flecs/addons/flecs_c.h"
#include "flecs/private/addons.h"
#include <flecs/addons/json.h>
#include <string>
#include <iostream>
#include <flecs/addons/meta.h>


namespace Engine {
    #undef ECS_META_IMPL
    #ifndef FLECS_COMPONENTS_TRANSFORM_IMPL
    #define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
    #endif

    ECS_STRUCT(Position, {
        float x;
        float y;
    });

    ECS_COMPONENT_DECLARE(Positon);

    SceneManager::SceneManager(): m_World(flecs::world()), m_App(flecs::app_builder(m_World)){
        const char* code = R"( using flecs.meta
 
struct Position {
  x = f32
  y = f32
}
 
my_entity {
  Position: {x: 10, y: 20}
})";

        m_World.script_run("position", code);

        std::cout << m_World.to_json() << std::endl;
    }
    SceneManager::SceneManager(SceneManager::AppSettings settings): m_World(flecs::world()), m_App(flecs::app_builder(m_World)){}
    SceneManager::SceneManager(std::string settings): m_World(flecs::world()), m_App(flecs::app_builder(m_World)){}

    void SceneManager::LoadScene(std::string name, std::string scene) {}
    void SceneManager::UnloadScene(std::string name) {}
}