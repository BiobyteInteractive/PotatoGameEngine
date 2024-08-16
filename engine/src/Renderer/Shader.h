#pragma once

#ifndef DllExport
#define DllExport __declspec( dllexport )
#endif

#include <string>

namespace Engine {
    class DllExport Shader {
        public:
            Shader(const char* vertexPath, const char* fragmentPath);
            
            void Use() const;
            void SetBool(const std::string& name, bool value) const;
            void SetInt(const std::string& name, int value) const;
            void SetFloat(const std::string& name, float value) const;
        public:
            unsigned int m_Id;

        private:
            void CheckCompileErrors(unsigned int shader, std::string type);
    };
}