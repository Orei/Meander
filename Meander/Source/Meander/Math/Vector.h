#pragma once

typedef unsigned char uint8_t;

namespace Meander
{
    template<typename T, uint8_t N>
    struct Vector
    {
        std::array<T, N> Data;

        Vector();
        Vector(const T& value);
        Vector(const std::initializer_list<T>& elements);

        std::string ToString() const;
        
        T operator[](uint8_t index) const;
        T& operator[](uint8_t index);
    };

    template<typename T>
    struct Vector<T, 2>
    {
        union
        {
            std::array<T, 2> Data;

            struct
            {
                T X;
                T Y;
            };
        };

        Vector();
        Vector(const T& value);
        Vector(const std::initializer_list<T>& elements);
        Vector(const T& x, const T& y);

        T Length() const;
        T LengthSqr() const;
        void Normalize();
        Vector<T, 2> Normal() const;
        T Dot(const Vector<T, 2>& rhs) const;
        Vector<T, 2> Cross(const Vector<T, 2>& rhs) const;
        T Distance(const Vector<T, 2>& rhs) const;
        T DistanceSqr(const Vector<T, 2>& rhs) const;

        std::string ToString() const;

        T operator[](uint8_t index) const;
        T& operator[](uint8_t index);
        
        static const Vector<T, 2> Zero;
        static const Vector<T, 2> One;
        static const Vector<T, 2> UnitX;
        static const Vector<T, 2> UnitY;
    };
    
    template<typename T>
    struct Vector<T, 3>
    {
        union
        {
            std::array<T, 3> Data;
    
            struct
            {
                T X;
                T Y;
                T Z;
            };
        };
    
        Vector();
        Vector(const T& value);
        Vector(const std::initializer_list<T>& elements);
        Vector(const T& x, const T& y, const T& z);

        T Length() const;
        T LengthSqr() const;
        void Normalize();
        Vector<T, 3> Normal() const;
        T Dot(const Vector<T, 3>& rhs) const;
        Vector<T, 3> Cross(const Vector<T, 3>& rhs) const;
        T Distance(const Vector<T, 3>& rhs) const;
        T DistanceSqr(const Vector<T, 3>& rhs) const;

        std::string ToString() const;
        
        T operator[](uint8_t index) const;
        T& operator[](uint8_t index);
    
        static const Vector<T, 3> Zero;
        static const Vector<T, 3> One;
        static const Vector<T, 3> Right;
        static const Vector<T, 3> Up;
        static const Vector<T, 3> Forward;
        static const Vector<T, 3> Left;
        static const Vector<T, 3> Down;
        static const Vector<T, 3> Back;
    };

    template<typename T>
    struct Vector<T, 4>
    {
        union
        {
            std::array<T, 4> Data;
    
            struct
            {
                T X;
                T Y;
                T Z;
                T W;
            };
    
            struct
            {
                T R;
                T G;
                T B;
                T A;
            };
        };
    
        Vector();
        Vector(const T& value);
        Vector(const std::initializer_list<T>& elements);
        Vector(const T& x, const T& y, const T& z, const T& w);

        T Length() const;
        T LengthSqr() const;
        void Normalize();
        Vector<T, 4> Normal() const;
        T Dot(const Vector<T, 4>& rhs) const;
        Vector<T, 4> Cross(const Vector<T, 4>& rhs) const;
        T Distance(const Vector<T, 4>& rhs) const;
        T DistanceSqr(const Vector<T, 4>& rhs) const;

        std::string ToString() const;
        
        T operator[](uint8_t index) const;
        T& operator[](uint8_t index);

        static const Vector<T, 4> Zero;
        static const Vector<T, 4> One;
    };

    template<typename T, uint8_t N> Vector<T, N> operator-(const Vector<T, N>& lhs);

    template<typename T, uint8_t N> Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator*(const Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator/(const Vector<T, N>& lhs, const Vector<T, N>& rhs);

    template<typename T, uint8_t N> Vector<T, N> operator+(const Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N> operator+(const T& scalar, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator-(const Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N> operator-(const T& scalar, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator*(const Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N> operator*(const T& scalar, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N> operator/(const Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N> operator/(const T& scalar, const Vector<T, N>& rhs);

    template<typename T, uint8_t N> Vector<T, N>& operator +=(Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N>& operator +=(Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N>& operator -=(Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N>& operator -=(Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N>& operator *=(Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N>& operator *=(Vector<T, N>& lhs, const T& scalar);
    template<typename T, uint8_t N> Vector<T, N>& operator /=(Vector<T, N>& lhs, const Vector<T, N>& rhs);
    template<typename T, uint8_t N> Vector<T, N>& operator /=(Vector<T, N>& lhs, const T& scalar);

    template <typename T, uint8_t N> std::ostream& operator<<(std::ostream& output, const Vector<T, N>& vector);
    
    typedef Vector<float, 2> Vector2;
    typedef Vector<float, 3> Vector3;
    typedef Vector<float, 4> Vector4;
}

#include "Vector.inl"