#pragma once

namespace Meander
{
    class Math
    {
    public:
        static float Sin(float value) { return sinf(value); }
        static float Cos(float value) { return cosf(value); }
        static float Tan(float value) { return tanf(value);}
        static float Asin(float value) { return asinf(value); }
        static float Acos(float value) { return acosf(value); }
        static float Atan(float value) { return atanf(value); }
        static float Atan2(float y, float x) { return atan2f(y, x); }
        static float Sinh(float value) { return sinhf(value); }
        static float Sqrt(float value) { return sqrtf(value); }
        static float Pow(float base, float exponent) { return powf(base, exponent); }
        static float Exp(float value) { return expf(value); }
        static float Log(float value) { return logf(value); }
        
        template<typename T>
        inline static T Min(T a, T b)
        {
            return (a < b) ? a : b;
        }

        template<typename T>
        inline static T Max(T a, T b)
        {
            return (a > b) ? a : b;
        }

        template<typename T>
        inline static T Lerp(T a, T b, float t)
        {
            return a + (b - a) * t;
        }

        template<typename T>
        inline static T Abs(T value)
        {
            return (value >= (T)0) ? value : -value;
        }

        template<typename T>
        inline static T Sign(T value)
        {
            T zero = (T)0;
            return (value > zero) ? (T)1 : (value < zero) ? (T)-1 : zero;
        }
        
        template<typename T>
        inline static T Clamp(T value, T min = (T)0, T max = (T)1)
        {
            if (min > max)
            {
                T tmp = min;
                min = max;
                max = tmp;
            }
            
            return (value < min) ? min : (value > max) ? max : value;
        }
    };
}