#pragma once

#include <string>
#include <vector>

#define DllExport __declspec( dllexport )

namespace Engine {
    class DllExport PanelInterface {
        public:
            PanelInterface() = default;
            ~PanelInterface() = default;

            virtual void OnImGuiRender() = 0;
            void ToggleWindow() {
                m_WindowIsOpen = !m_WindowIsOpen;
            };
        protected:
            bool m_WindowIsOpen;
            std::vector<std::string> m_MenuPath;
    };
}