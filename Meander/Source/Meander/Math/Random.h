#pragma once
#include <random>
#include <glm/vec3.hpp>

namespace Meander
{
	class Random
	{
	public:
		Random() 
			: m_RNG((unsigned int)time(nullptr))
		{
		}

		Random(unsigned int seed) 
			: m_RNG(seed)
		{
		}

		/* Re-seeds the random number generator. */
		void Seed(unsigned int seed);

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

	private:
		std::mt19937 m_RNG;
	};
}