#pragma once
#include "Vector.h"

namespace Meander
{
    template<typename T>
    struct Quaternion
    {
        union
        {
            struct
            {
                T X;
                T Y;
                T Z;
                T W;
            };
        };
        
        Quaternion() : X(0), Y(0), Z(0), W(1) { }
        Quaternion(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) { }
        Quaternion(const Vector<T, 3>& axis, const T& angle)
        {
            const T halfAngle = angle * (T)0.5;
            const T halfSin = sin(halfAngle);
            X = axis.X * halfSin;
            Y = axis.Y * halfSin;
            Z = axis.Z * halfSin;
            W = cos(halfAngle);
        }
        
        explicit Quaternion(const Vector<T, 3>& euler)
        {
            Vector<T, 3> h = euler * (T)0.5;
            Vector<T, 3> c(cos(h.X), cos(h.Y), cos(h.Z));
            Vector<T, 3> s(sin(h.X), sin(h.Y), sin(h.Z));

            X = s.X * c.Y * c.Z - c.X * s.Y * s.Z;
            Y = c.X * s.Y * c.Z + s.X * c.Y * s.Z;
            Z = c.X * c.Y * s.Z - s.X * s.Y * c.Z;
            W = c.X * c.Y * c.Z + s.X * s.Y * s.Z;
        }

        Quaternion<T> Inverse();
        
        T Pitch() const;
        T Yaw() const;
        T Roll() const;
        Vector3<T, 3> Euler() const;

        static const Quaternion<T> Identity;
    };

    typedef Quaternion<float> Quat;
}

#include "Quaternion.inl"