#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include "../Renderer/Color.h"

#include <string>

namespace Engine {
    class Vector4 {
        public:
            Vector4(float x, float y, float z, float w);
            Vector4(Color color);

        public:
            float x, y, z, w;
            
            static Vector4 zero;
            static Vector4 one;

        public:
            Vector4& operator+=(const Vector4& other) {
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
                this->w += other.w;
                return *this;
            }

            Vector4& operator-=(const Vector4& other) {
                this->x -= other.x;
                this->y -= other.y;
                this->z -= other.z;
                this->w -= other.w;
                return *this;
            }

            Vector4 operator+(const Vector4& rhs) {
                Vector4 res(this->x, this->y, this->z, this->w);
                res += rhs;
                return res;
            };

            Vector4 operator-(const Vector4& rhs) {
                Vector4 res(this->x, this->y, this->z, this->w);
                res -= rhs;
                return res;
            };

            Vector4 operator*(const Vector4& rhs) {
                Vector4 res(this->x, this->y, this->z, this->w);
                res.x = res.x * rhs.x;
                res.y = res.y * rhs.y;
                res.z = res.z * rhs.z;
                res.w = res.w * rhs.w;
                return res;
            }

            Vector4 operator/(const Vector4& rhs) {
                Vector4 res(this->x, this->y, this->z, this->w);
                res.x = res.x / rhs.x;
                res.y = res.y / rhs.y;
                res.z = res.z / rhs.z;
                res.w = res.w / rhs.w;
                return res;
            }

            bool operator==(const Vector4& other) {
                return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
            }

            bool Equals(Vector4 other);
            void Normalize();
            void Set(float newX, float newY);
            std::string ToString();

            static float Angle(Vector4 from, Vector4 to);
            static Vector4 ClampMagnitude(Vector4 vector, float maxLength);
            static float Distance(Vector4 a, Vector4 b);
            static float Dot(Vector4 lhs, Vector4 rhs);
            static Vector4 Lerp(Vector4 a, Vector4 b, float t);
            static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
            static Vector4 Max(Vector4 lhs, Vector4 rhs);
            static Vector4 Min(Vector4 lhs, Vector4 rhs);
            static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);
            static Vector4 Perpendicular(Vector4 inDirection);
            static Vector4 Reflect(Vector4 inDirection, Vector4 inNormal);
            static Vector4 Scale(Vector4 a, Vector4 b);
            static Vector4 SignedAngle(Vector4 from, Vector4 to);
    };
}