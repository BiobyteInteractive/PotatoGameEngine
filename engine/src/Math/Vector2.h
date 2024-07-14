#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

#include <string>

namespace Engine {
    class Vector2 {
        public:
            Vector2(float x, float y);
        public:
            float x, y;

            static Vector2 up;
            static Vector2 down;
            static Vector2 right;
            static Vector2 left;

            static Vector2 zero;
            static Vector2 one;

        public:
            Vector2& operator+=(const Vector2& other) {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }

            Vector2& operator-=(const Vector2& other) {
                this->x -= other.x;
                this->y -= other.y;
                return *this;
            }

            Vector2 operator+(const Vector2& rhs) {
                Vector2 res(this->x, this->y);
                res += rhs;
                return res;
            };

            Vector2 operator-(const Vector2& rhs) {
                Vector2 res(this->x, this->y);
                res -= rhs;
                return res;
            };

            Vector2 operator*(const Vector2& rhs) {
                Vector2 res(this->x, this->y);
                res.x = res.x * rhs.x;
                res.y = res.y * rhs.y;
                return res;
            }

            Vector2 operator/(const Vector2& rhs) {
                Vector2 res(this->x, this->y);
                res.x = res.x / rhs.x;
                res.y = res.y / rhs.y;
                return res;
            }

            bool operator==(const Vector2& other) {
                return (this->x == other.x && this->y == other.y);
            }
            
            bool operator!=(const Vector2& other) {
                return !(this->x == other.x && this->y == other.y);
            }
        
            bool Equals(Vector2 other);
            void Normalize();
            void Set(float newX, float newY);
            std::string ToString();

            static float Angle(Vector2 from, Vector2 to);
            static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
            static float Distance(Vector2 a, Vector2 b);
            static float Dot(Vector2 lhs, Vector2 rhs);
            static Vector2 Lerp(Vector2 a, Vector2 b, float t);
            static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
            static Vector2 Max(Vector2 lhs, Vector2 rhs);
            static Vector2 Min(Vector2 lhs, Vector2 rhs);
            static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);
            static Vector2 Perpendicular(Vector2 inDirection);
            static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);
            static Vector2 Scale(Vector2 a, Vector2 b);
            static Vector2 SignedAngle(Vector2 from, Vector2 to);
    };
}