#pragma once
#include <glm/vec3.hpp>

namespace Meander
{
	class Random
	{
	public:
		/* Re-seeds the underlying random number generator. */
		static void Seed(unsigned int seed);

		/* Returns a random integer between 0 and upper integer limit. */
		static int Int();

		/* Returns a random integer between range. */
		static int Int(int min, int max);

		/* Returns a random float between 0 and 1.*/
		static float Float();

		/* Returns a random float between range.*/
		static float Float(float min, float max);

		/* Returns a random double between 0 and 1. */
		static double Double();

		/* Returns a random double between range. */
		static double Double(double min, double max);

		/* Returns either true or false. */
		static bool Flip();

		/* Returns a random normalized axis. */
		static glm::vec3 Axis();

	private:
		Random() = delete;
		Random(const Random& r) = delete;
		~Random() = delete;
	};
}