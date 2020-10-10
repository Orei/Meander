#include "pch.h"
#include "RandomStream.h"
#include <glm/geometric.hpp>

namespace Meander
{
    void RandomStream::Seed(unsigned int seed)
    {
        m_RNG.seed(seed);
    }

    int RandomStream::Int()
    {
        return std::uniform_int_distribution(0, std::numeric_limits<int>::max())(m_RNG);
    }

    int RandomStream::Int(int min, int max)
    {
        return std::uniform_int_distribution(min, max)(m_RNG);
    }

    float RandomStream::Float()
    {
        return std::uniform_real_distribution<float>(0.f, 1.f)(m_RNG);
    }

    float RandomStream::Float(float min, float max)
    {
        return std::uniform_real_distribution<float>(min, max)(m_RNG);
    }

    double RandomStream::Double()
    {
        return std::uniform_real_distribution<double>(0.0, 1.0)(m_RNG);
    }

    double RandomStream::Double(double min, double max)
    {
        return std::uniform_real_distribution<double>(min, max)(m_RNG);
    }

    bool RandomStream::Flip()
    {
        return std::uniform_int_distribution(0, 1)(m_RNG);
    }

    glm::vec3 RandomStream::Axis()
    {
        glm::vec3 axis;
        axis.x = Float(-1.f, 1.f);
        axis.y = Float(-1.f, 1.f);
        axis.z = Float(-1.f, 1.f);
        return glm::normalize(axis);
    }
}
