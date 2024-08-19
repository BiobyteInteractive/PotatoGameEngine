#pragma once

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#include "../Assets/AssetDatabase.h"
#include "SceneManager.h"

#include <GLFW/glfw3.h>

namespace Engine {
    class DllExport Application {
        public:
            Application();
            ~Application();
        public:
            AssetDatabase m_AssetDatabase;
            SceneManager  m_SceneManager;
    };
}