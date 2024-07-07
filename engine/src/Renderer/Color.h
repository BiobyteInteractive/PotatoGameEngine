#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include <string>
#include <tuple>

namespace Engine {
    class DllExport Color {
        public:
            Color(int r, int g, int b, int a);
            Color(float r, float g, float b, float a);

            std::string ToString();

            static Color HSVToRGB(float h, float s, float v);
            static std::tuple<float, float, float>  RGBToHSV(Color rgbColor);
            //static Color Lerp(Color from, Color to, float t);
            //static Color LerpUnclamped(Color from, Color to, float t);
        public:
            float r, g, b, a;

            static Color s_Black;
            static Color s_Blue;
            static Color s_Clear;
            static Color s_Cyan;
            static Color s_Gray;
            static Color s_Green;
            static Color s_Grey;
            static Color s_Magenta;
            static Color s_PowderBlue;
            static Color s_Purple;
            static Color s_Red;
            static Color s_White;
            static Color s_Yellow;
    };
}