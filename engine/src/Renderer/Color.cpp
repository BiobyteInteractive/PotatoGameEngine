#include "Color.h"

#include <format>
#include <tuple>

namespace Engine {
    Color::Color(int r, int g, int b, int a) {
        this->r = r / 255.0f;
        this->g = g / 255.0f;
        this->b = b / 255.0f;
        this->a = a / 255.0f;
    }
    
    Color::Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    std::string Color::ToString() {
        return std::format("({}, {}, {}, {})", this->r, this->g, this->b, this->a);
    }

    Color Color::HSVToRGB(float h, float s, float v) {
        float c = v * s;
        float x = c * (1 - std::fabs(fmod(h / 60.0, 2) - 1));
        float m = v - c;

        float r, g, b;
        if (0 <= h && h < 60) {
            r = c; g = x; b = 0;
        } else if (60 <= h && h < 120) {
            r = x; g = c; b = 0;
        } else if (120 <= h && h < 180) {
            r = 0; g = c; b = x;
        } else if (180 <= h && h < 240) {
            r = 0; g = x; b = c;
        } else if (240 <= h && h < 300) {
            r = x; g = 0; b = c;
        } else if (300 <= h && h < 360) {
            r = c; g = 0; b = x;
        } else {
            r = 0; g = 0; b = 0; // Hue out of range
        }

        int R = static_cast<int>((r + m) * 255);
        int G = static_cast<int>((g + m) * 255);
        int B = static_cast<int>((b + m) * 255);

        Color color(R, G, B, 255);
        return color;
    }

    std::tuple<float, float, float> Color::RGBToHSV(Color rgbColor) {
        float r = rgbColor.r / 255.0f;
        float g = rgbColor.g / 255.0f;
        float b = rgbColor.b / 255.0f;

        float max = std::max({r, g, b});
        float min = std::min({r, g, b});
        float delta = max - min;

        float h = 0, s = 0, v = 0;

        v = max; // Value

        if (max == 0.0f) {
            s = 0.0f; // Saturation
        } else {
            s = delta / max; // Saturation
        }

        if (delta == 0.0f) {
            h = 0.0f; // Hue
        } else {
            if (max == r) {
                h = 60.0f * (fmod(((g - b) / delta), 6.0f));
            } else if (max == g) {
                h = 60.0f * (((b - r) / delta) + 2.0f);
            } else if (max == b) {
                h = 60.0f * (((r - g) / delta) + 4.0f);
            }

            if (h < 0.0f) {
                h += 360.0f;
            }
        }

        return std::make_tuple(h, s, v);
    }

    Color Color::s_Black   = Color(0  , 0  , 0  , 255);
    Color Color::s_Blue    = Color(0  , 0  , 255, 255);
    Color Color::s_Clear   = Color(0  , 0  , 0  , 0  );
    Color Color::s_Cyan    = Color(0  , 255, 255, 255);
    Color Color::s_Gray    = Color(127, 127, 127, 255);
    Color Color::s_Green   = Color(0  , 255, 0  , 255);
    Color Color::s_Grey    = Color(127, 127, 127, 255);
    Color Color::s_Magenta = Color(255, 0  , 255, 0  );
    Color Color::s_Red     = Color(255, 0  , 0  , 255);
    Color Color::s_White   = Color(255, 255, 255, 255);
    Color Color::s_Yellow  = Color(255, 235, 4  , 255);
}