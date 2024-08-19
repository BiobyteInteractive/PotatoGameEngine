#include "SceneManager.h"

namespace Engine {
    SceneManager::SceneManager() {
        m_World = flecs::world();

        m_World.set_threads(4);
    }

    void SceneManager::LoadScene() {}

    void SceneManager::UnloadScene() {}
}