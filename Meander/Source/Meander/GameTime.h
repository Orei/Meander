#pragma once
#include <chrono>

namespace Meander
{
	/* Stores and calculates game-related timings. */
	class GameTime
	{
		typedef std::chrono::high_resolution_clock hr_clock;
		typedef std::chrono::steady_clock::time_point time_point_t;

	public:
		void Start()
		{
			m_Start = m_End = hr_clock::now();
		}

		void Update()
		{
			auto end = hr_clock::now();
			
			m_DeltaSeconds = GetDuration(m_End, end);
			m_TimeElapsed = GetDuration(m_Start, end);
			m_Frame++;
		
			m_End = end;
		}
		
		/* Returns time passed since last update in seconds. */
		float GetDeltaSeconds() const { return m_DeltaSeconds; }

		/* Returns time elapsed since start in seconds. */
		float GetTimeElapsed() const { return m_TimeElapsed; }

		/* Returns the current frame. */
		uint32_t GetFrame() const { return m_Frame; }

	private:
		time_point_t m_Start;
		time_point_t m_End;
		float m_DeltaSeconds = 0.f;
		float m_TimeElapsed = 0.f;
		uint32_t m_Frame = 0;

		/* Returns seconds passed between two time points. */
		float GetDuration(time_point_t start, time_point_t end)
		{
			return (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) * 1e-9f;
		}
	};
}