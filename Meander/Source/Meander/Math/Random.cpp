#include "pch.h"
#include "Random.h"
#include <glm/detail/func_geometric.inl>

namespace Meander
{
	void Random::Seed(unsigned int seed)
	{
		m_RNG.seed(seed);
	}

	int Random::Int()
	{
		return std::uniform_int_distribution(0, std::numeric_limits<int>::max())(m_RNG);
	}

	int Random::Int(int min, int max)
	{
		return std::uniform_int_distribution(min, max)(m_RNG);
	}

	float Random::Float()
	{
		return std::uniform_real_distribution<float>(0.f, 1.f)(m_RNG);
	}

	float Random::Float(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(m_RNG);
	}

	double Random::Double()
	{
		return std::uniform_real_distribution<double>(0.0, 1.0)(m_RNG);
	}

	double Random::Double(double min, double max)
	{
		return std::uniform_real_distribution<double>(min, max)(m_RNG);
	}

	bool Random::Flip()
	{
		return std::uniform_int_distribution(0, 1)(m_RNG);
	}

	glm::vec3 Random::Axis()
	{
		glm::vec3 axis;
		axis.x = Float(-1.f, 1.f);
		axis.y = Float(-1.f, 1.f);
		axis.z = Float(-1.f, 1.f);
		return glm::normalize(axis);
	}
}
