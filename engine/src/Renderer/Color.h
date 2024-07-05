#pragma once

#define DllExport __declspec( dllexport )

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

            static Color black;   // These don't work??? Unresolved symbols.
            static Color blue;    // These don't work??? Unresolved symbols.
            static Color clear;   // These don't work??? Unresolved symbols.
            static Color cyan;    // These don't work??? Unresolved symbols.
            static Color gray;    // These don't work??? Unresolved symbols.
            static Color green;   // These don't work??? Unresolved symbols.
            static Color grey;    // These don't work??? Unresolved symbols.
            static Color magenta; // These don't work??? Unresolved symbols.
            static Color red;     // These don't work??? Unresolved symbols.
            static Color white;   // These don't work??? Unresolved symbols.
            static Color yellow;  // These don't work??? Unresolved symbols.
    };
}