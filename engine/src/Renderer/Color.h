#pragma once

#define DllExport __declspec( dllexport )

#include <string>

namespace Engine {
    class Color {
        public:
            Color(int r, int g, int b, int a);
            Color(float r, float g, float b, float a);

            std::string ToString();

            static Color HSVToRGB(float h, float s, float v);
            static void  RGBToHSV(Color rgbColor, float* h, float* s, float* v);
            static Color Lerp(Color from, Color to, float t);
            static Color LerpUnclamped(Color from, Color to, float t);
        public:
            float r, g, b, a;

            static Color black;
            static Color blue;
            static Color clear;
            static Color cyan;
            static Color gray;
            static Color green;
            static Color grey;
            static Color magenta;
            static Color red;
            static Color white;
            static Color yellow;
    };
}