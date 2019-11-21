#pragma once
#include <chrono>

namespace Meander
{
	class Timer
	{
		typedef std::chrono::high_resolution_clock hr_clock;
		typedef std::chrono::steady_clock::time_point time_point_t;

	public:
		void Start()
		{
			m_Begin = hr_clock::now();
		}

		void Stop()
		{
			m_End = hr_clock::now();
		}

		/* Gets elapsed time in milliseconds. */
		double GetElapsed() const
		{
			return (double)std::chrono::duration_cast<std::chrono::milliseconds>(m_End - m_Begin).count();
		}

	private:
		time_point_t m_Begin;
		time_point_t m_End;
	};
}