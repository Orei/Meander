#pragma once

namespace Meander
{
    template <typename T>
    Quaternion<T> Quaternion<T>::Inverse()
    {
        return Quaternion<T>(-X, -Y, -Z, W);
    }
    
    template <typename T>
    T Quaternion<T>::Pitch() const
    {
        return atan2((T)2 * (Y * Z + W * X), W * W - X * X - Y * Y + Z * Z);
    }

    template <typename T>
    T Quaternion<T>::Yaw() const
    {
        return asin(clamp((T)-2 * (X * Z - W * Y), (T)-1, (T)1));
    }

    template <typename T>
    T Quaternion<T>::Roll() const
    {
        return atan2((T)2 * (X * Y + W * Z), W * W + X * X - Y * Y - Z * Z);
    }
    
    template <typename T>
    Vector3<T, 3> Quaternion<T>::Euler() const
    {
        const T xx(X * X);
        const T yy(Y * Y);
        const T zz(Z * Z);
        const T ww(W * W);

        T pitch = atan2((T)2 * (X * Z + W * X), ww - xx - yy + zz);
        T roll = atan2((T)2 * (X * Y + W * Z), ww + xx - yy - zz);

        return Vector<T, 3>(pitch, Yaw(), roll);
    }

    template<typename T>
    const Quaternion<T> Quaternion<T>::Identity(0, 0, 0, 1);
}