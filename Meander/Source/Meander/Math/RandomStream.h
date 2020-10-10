#pragma once
#include <random>
#include <glm/vec3.hpp>

namespace Meander
{
    struct RandomStream
    {
    public:
        RandomStream() 
            : m_RNG((uint32_t)time(nullptr))
        {
        }

        RandomStream(uint32_t seed) 
            : m_RNG(seed)
        {
        }

        /* Re-seeds the underlying random number generator. */
        void Seed(uint32_t seed);

        /* Returns a random integer between 0 and upper integer limit. */
        int Int();

        /* Returns a random integer between range. */
        int Int(int min, int max);

        /* Returns a random float between 0 and 1.*/
        float Float();

        /* Returns a random float between range.*/
        float Float(float min, float max);

        /* Returns a random double between 0 and 1. */
        double Double();

        /* Returns a random double between range. */
        double Double(double min, double max);

        /* Returns either true or false. */
        bool Flip();

        /* Returns a random normalized axis. */
        glm::vec3 Axis();

    protected:
        std::mt19937 m_RNG;
    };
}
