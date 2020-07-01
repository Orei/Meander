#pragma once

namespace Meander
{
    //
    // VECTOR N
    // 
    template<typename T, uint8_t N>
    Vector<T, N>::Vector()
    {
        for (uint8_t i = 0; i < N; ++i)
            Data[i] = 0;
    }

    template<typename T, uint8_t N>
    Vector<T, N>::Vector(const T& value)
    {
        for (uint8_t i = 0; i < N; ++i)
            Data[i] = value;
    }
    
    template<typename T, uint8_t N>
    Vector<T, N>::Vector(const std::initializer_list<T>& elements)
    {
        uint8_t index = 0;
        for (auto it = elements.begin(); it != elements.end(); ++it)
            Data[index++] = *it;
    }

    template<typename T, uint8_t N>
    std::string Vector<T, N>::ToString() const
    {
        std::string string("{");
        for (int i = 0; i < N; ++i)
        {
            string.append(std::to_string(Data[i]));
            
            if (i < N - 1)
                string.append(", ");
        }
        string.append("}");
        return string;
    }
    
    template<typename T, uint8_t N>
    T Vector<T, N>::operator[](uint8_t index) const { return Data.at(index); }
    
    template<typename T, uint8_t N>
    T& Vector<T, N>::operator[](uint8_t index) { return Data.at(index); }

    template <typename T, uint8_t N>
    Vector<T, N> operator-(const Vector<T, N>& lhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = -lhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] + rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] - rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator*(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] * rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator/(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] / rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator+(const Vector<T, N>& lhs, const T& scalar)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] + scalar;
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator+(const T& scalar, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = scalar + rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator-(const Vector<T, N>& lhs, const T& scalar)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] - scalar;
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator-(const T& scalar, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = scalar - rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator*(const Vector<T, N>& lhs, const T& scalar)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] * scalar;
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator*(const T& scalar, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = scalar * rhs[i];
        return result;
    }

    template <typename T, uint8_t N>
    Vector<T, N> operator/(const Vector<T, N>& lhs, const T& scalar)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = lhs[i] / scalar;
        return result;
    }
    
    template <typename T, uint8_t N>
    Vector<T, N> operator/(const T& scalar, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (uint8_t i = 0; i < N; ++i)
            result[i] = scalar / rhs[i];
        return result;
    }
    
    template<typename T, uint8_t N>
    Vector<T, N>& operator +=(Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] += rhs[i];

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator +=(Vector<T, N>& lhs, const T& scalar)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] += scalar;

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator -=(Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] -= rhs[i];

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator -=(Vector<T, N>& lhs, const T& scalar)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] -= scalar;

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator *=(Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] *= rhs[i];

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator *=(Vector<T, N>& lhs, const T& scalar)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] *= scalar;

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator /=(Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] /= rhs[i];

        return lhs;
    }

    template<typename T, uint8_t N>
    Vector<T, N>& operator /=(Vector<T, N>& lhs, const T& scalar)
    {
        for (int i = 0; i < N; ++i)
            lhs[i] /= scalar;

        return lhs;
    }

    template <typename T, uint8_t N>
    std::ostream& operator<<(std::ostream& output, const Vector<T, N>& vector)
    {
        output << "{";
        for (int i = 0; i < N; ++i)
            output << vector[i] << ", ";
        return output << "}";
    }
    
    //
    // VECTOR2
    //
    template<typename T>
    Vector<T, 2>::Vector() : X((T)0), Y((T)0) { }

    template<typename T>
    Vector<T, 2>::Vector(const T& value) : X(value), Y(value) { }

    template<typename T>
    Vector<T, 2>::Vector(const std::initializer_list<T>& elements)
    {
        uint8_t index = 0;
        for (auto it = elements.begin(); it != elements.end(); ++it)
            Data[index++] = *it;
    }

    template<typename T>
    Vector<T, 2>::Vector(const T& x, const T& y) : X(x), Y(y) { }

    template<typename T>
    T Vector<T, 2>::operator[](uint8_t index) const { return Data.at(index); }
    
    template<typename T>
    T& Vector<T, 2>::operator[](uint8_t index) { return Data.at(index); }

    template<typename T>
    void Vector<T, 2>::Normalize()
    {
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 2; ++i)
                Data[i] *= invLength;
        }
    }
    
    template<typename T>
    Vector<T, 2> Vector<T, 2>::Normal() const
    {
        Vector<T, 2> normal(X, Y);
        
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 2; ++i)
                normal[i] *= invLength;
        }
        
        return normal;
    }
    
    template<typename T>
    T Vector<T, 2>::Length() const
    {
        return sqrt(LengthSqr());
    }
    
    template<typename T>
    T Vector<T, 2>::LengthSqr() const
    {
        T length = (T)0;
        for (uint8_t i = 0; i < 2; ++i)
            length += Data[i] * Data[i];
        return length;
    }
    
    template<typename T>
    T Vector<T, 2>::Dot(const Vector<T, 2>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 2; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    Vector<T, 2> Vector<T, 2>::Cross(const Vector<T, 2>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 2; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    T Vector<T, 2>::Distance(const Vector<T, 2>& rhs) const
    {
        return (*this - rhs).Length();
    }
    
    template<typename T>
    T Vector<T, 2>::DistanceSqr(const Vector<T, 2>& rhs) const
    {
        return (*this - rhs).LengthSqr();
    }

    template<typename T>
    std::string Vector<T, 2>::ToString() const
    {
        return "{" + std::to_string(X) + ", " + std::to_string(Y) + "}";
    }
    
    template<typename T> const Vector<T, 2> Vector<T, 2>::Zero = Vector<T, 2>(0);
    template<typename T> const Vector<T, 2> Vector<T, 2>::One = Vector<T, 2>(1);
    template<typename T> const Vector<T, 2> Vector<T, 2>::UnitX = Vector<T, 2>(1, 0);
    template<typename T> const Vector<T, 2> Vector<T, 2>::UnitY = Vector<T, 2>(0, 1);

    //
    // VECTOR3
    //
    template<typename T>
    Vector<T, 3>::Vector() : X((T)0), Y((T)0), Z((T)0) { }

    template<typename T>
    Vector<T, 3>::Vector(const T& value) : X(value), Y(value), Z(value) { }

    template<typename T>
    Vector<T, 3>::Vector(const std::initializer_list<T>& elements) : X((T)0), Y((T)0), Z((T)0)
    {
        uint8_t index = 0;
        for (auto it = elements.begin(); it != elements.end(); ++it)
            Data[index++] = *it;
    }

    template<typename T>
    Vector<T, 3>::Vector(const T& x, const T& y, const T& z) : X(x), Y(y), Z(z) { }
    
    template<typename T>
    T Vector<T, 3>::operator[](uint8_t index) const { return Data.at(index); }
    
    template<typename T>
    T& Vector<T, 3>::operator[](uint8_t index) { return Data.at(index); }
    
    template<typename T>
    void Vector<T, 3>::Normalize()
    {
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 3; ++i)
                Data[i] *= invLength;
        }
    }
    
    template<typename T>
    Vector<T, 3> Vector<T, 3>::Normal() const
    {
        Vector<T, 3> normal(X, Y, Z);
        
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 3; ++i)
                normal[i] *= invLength;
        }
        
        return normal;
    }
    
    template<typename T>
    T Vector<T, 3>::Length() const
    {
        return sqrt(LengthSqr());
    }
    
    template<typename T>
    T Vector<T, 3>::LengthSqr() const
    {
        T length = (T)0;
        for (uint8_t i = 0; i < 3; ++i)
            length += Data[i] * Data[i];
        return length;
    }
    
    template<typename T>
    T Vector<T, 3>::Dot(const Vector<T, 3>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 3; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    Vector<T, 3> Vector<T, 3>::Cross(const Vector<T, 3>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 3; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    T Vector<T, 3>::Distance(const Vector<T, 3>& rhs) const
    {
        return (*this - rhs).Length();
    }
    
    template<typename T>
    T Vector<T, 3>::DistanceSqr(const Vector<T, 3>& rhs) const
    {
        return (*this - rhs).LengthSqr();
    }

    template<typename T>
    std::string Vector<T, 3>::ToString() const
    {
        return "{" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + "}";
    }
    
    template<typename T> const Vector<T, 3> Vector<T, 3>::Zero = Vector<T, 3>(0);
    template<typename T> const Vector<T, 3> Vector<T, 3>::One = Vector<T, 3>(1);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Right = Vector<T, 3>(1, 0, 0);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Up = Vector<T, 3>(0, 1, 0);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Forward = Vector<T, 3>(0, 0, 1);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Left = Vector<T, 3>(-1, 0, 0);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Down = Vector<T, 3>(0, -1, 0);
    template<typename T> const Vector<T, 3> Vector<T, 3>::Back = Vector<T, 3>(0, 0, -1);

    //
    // VECTOR4
    //
    template<typename T>
    Vector<T, 4>::Vector() : X((T)0), Y((T)0), Z((T)0), W((T)0) { }

    template<typename T>
    Vector<T, 4>::Vector(const T& value) : X(value), Y(value), Z(value), W(value) { }

    template<typename T>
    Vector<T, 4>::Vector(const std::initializer_list<T>& elements) : X((T)0), Y((T)0), Z((T)0), W((T)0)
    {
        uint8_t index = 0;
        for (auto it = elements.begin(); it != elements.end(); ++it)
            Data[index++] = *it;
    }

    template<typename T>
    Vector<T, 4>::Vector(const T& x, const T& y, const T& z, const T& w) : X(x), Y(y), Z(z), W(w) { }

    template<typename T>
    T Vector<T, 4>::operator[](uint8_t index) const { return Data.at(index); }
    
    template<typename T>
    T& Vector<T, 4>::operator[](uint8_t index) { return Data.at(index); }

    template<typename T>
    void Vector<T, 4>::Normalize()
    {
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 4; ++i)
                Data[i] *= invLength;
        }
    }
    
    template<typename T>
    Vector<T, 4> Vector<T, 4>::Normal() const
    {
        Vector<T, 4> normal(X, Y, Z, W);
        
        T lengthSqr = LengthSqr();
        if (lengthSqr > (T)0 && lengthSqr != (T)1)
        {
            T invLength = (T)1 / sqrt(lengthSqr);
    
            for (uint8_t i = 0; i < 4; ++i)
                normal[i] *= invLength;
        }
        
        return normal;
    }
    
    template<typename T>
    T Vector<T, 4>::Length() const
    {
        return sqrt(LengthSqr());
    }
    
    template<typename T>
    T Vector<T, 4>::LengthSqr() const
    {
        T length = (T)0;
        for (uint8_t i = 0; i < 4; ++i)
            length += Data[i] * Data[i];
        return length;
    }
    
    template<typename T>
    T Vector<T, 4>::Dot(const Vector<T, 4>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 4; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    Vector<T, 4> Vector<T, 4>::Cross(const Vector<T, 4>& rhs) const
    {
        T dotProduct = (T)0;
        for (uint8_t i = 0; i < 4; ++i)
            dotProduct += Data[i] * rhs[i];
        return dotProduct;
    }
    
    template<typename T>
    T Vector<T, 4>::Distance(const Vector<T, 4>& rhs) const
    {
        return (*this - rhs).Length();
    }
    
    template<typename T>
    T Vector<T, 4>::DistanceSqr(const Vector<T, 4>& rhs) const
    {
        return (*this - rhs).LengthSqr();
    }

    template<typename T>
    std::string Vector<T, 4>::ToString() const
    {
        return "{" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + ", " + std::to_string(W) + "}";
    }
    
    template<typename T> const Vector<T, 4> Vector<T, 4>::Zero = Vector<T, 4>(0);
    template<typename T> const Vector<T, 4> Vector<T, 4>::One = Vector<T, 4>(1);
}