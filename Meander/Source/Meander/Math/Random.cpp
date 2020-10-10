#include "pch.h"
#include "Random.h"
#include "RandomStream.h"

namespace Meander
{
    RandomStream& GetRandomStream()
    {
        static RandomStream stream; 
        return stream;
    }

    void Random::Seed(unsigned seed)
    {
        GetRandomStream().Seed(seed);
    }

    int Random::Int()
    {
        return GetRandomStream().Int();
    }

    int Random::Int(int min, int max)
    {
        return GetRandomStream().Int(min, max);
    }

    float Random::Float()
    {
        return GetRandomStream().Float();
    }

    float Random::Float(float min, float max)
    {
        return GetRandomStream().Float(min, max);
    }

    double Random::Double()
    {
        return GetRandomStream().Double();
    }

    double Random::Double(double min, double max)
    {
        return GetRandomStream().Double(min, max);
    }

    bool Random::Flip()
    {
        return GetRandomStream().Flip();
    }

    glm::vec3 Random::Axis()
    {
        return GetRandomStream().Axis();
    }
}
