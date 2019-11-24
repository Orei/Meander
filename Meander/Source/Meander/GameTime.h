#pragma once

namespace Meander
{
	/* Stores game-related timings. */
	class GameTime
	{
	public:
		/* Returns the delta time in seconds. */
		float GetDeltaSeconds() const { return m_DeltaSeconds * m_TimeScale; }

		/* Returns the delta time in seconds without any scaling applied. */
		float GetDeltaPure() const { return m_DeltaSeconds; }

		/* Returns the elapsed time in seconds since start. */
		float GetElapsedSeconds() const { return m_ElapsedSeconds; }

		/* Returns the current frame. */
		int GetFrame() const { return m_CurrentFrame; }

		/* Returns the current time scale. */
		float GetTimeScale() const { return m_TimeScale; }

		/* Sets the current time scale. */
		void SetTimeScale(float timeScale) { m_TimeScale = timeScale < 0.f ? 0.f : timeScale; }

		/* Updates the timings. */
		void Update(float deltaSeconds)
		{
			m_CurrentFrame++;
			m_ElapsedSeconds += deltaSeconds;
			m_DeltaSeconds = deltaSeconds;
		}

	private:
		float m_ElapsedSeconds = 0.f;
		float m_DeltaSeconds = 0.f;
		float m_TimeScale = 1.f;
		unsigned int m_CurrentFrame = 0;
	};
}