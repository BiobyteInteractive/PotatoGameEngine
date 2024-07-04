#pragma once

#define DllExport __declspec( dllexport )

#include <string>

namespace Engine {
    class Vector3 {
        public:
            Vector3(float x, float y, float z);
        public:
            float x, y, z;

            static Vector3 up;
            static Vector3 down;
            static Vector3 right;
            static Vector3 left;
            static Vector3 back;
            static Vector3 forward;

            static Vector3 zero;
            static Vector3 one;

        public:
            Vector3& operator+=(const Vector3& other) {
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
                return *this;
            }

            Vector3& operator-=(const Vector3& other) {
                this->x -= other.x;
                this->y -= other.y;
                this->z -= other.z;
                return *this;
            }

            Vector3 operator+(const Vector3& rhs) {
                Vector3 res(this->x, this->y, this->z);
                res += rhs;
                return res;
            };

            Vector3 operator-(const Vector3& rhs) {
                Vector3 res(this->x, this->y, this->z);
                res -= rhs;
                return res;
            };

            Vector3 operator*(const Vector3& rhs) {
                Vector3 res(this->x, this->y, this->z);
                res.x = res.x * rhs.x;
                res.y = res.y * rhs.y;
                res.z = res.z * rhs.z;
                return res;
            }

            Vector3 operator/(const Vector3& rhs) {
                Vector3 res(this->x, this->y, this->z);
                res.x = res.x / rhs.x;
                res.y = res.y / rhs.y;
                res.z = res.z / rhs.z;
                return res;
            }

            bool operator==(const Vector3& other) {
                return (this->x == other.x && this->y == other.y && this->z == other.z);
            }

            bool Equals(Vector3 other);
            void Normalize();
            void Set(float newX, float newY);
            std::string ToString();

            static float Angle(Vector3 from, Vector3 to);
            static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
            static float Distance(Vector3 a, Vector3 b);
            static float Dot(Vector3 lhs, Vector3 rhs);
            static Vector3 Lerp(Vector3 a, Vector3 b, float t);
            static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
            static Vector3 Max(Vector3 lhs, Vector3 rhs);
            static Vector3 Min(Vector3 lhs, Vector3 rhs);
            static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
            static Vector3 Perpendicular(Vector3 inDirection);
            static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
            static Vector3 Scale(Vector3 a, Vector3 b);
            static Vector3 SignedAngle(Vector3 from, Vector3 to);
    };
}