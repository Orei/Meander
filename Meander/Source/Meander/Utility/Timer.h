#pragma once

namespace Meander
{
    // TODO: Reconsider this; fairly similar to GameTime & more of a stopwatch than a timer
    class Timer
    {
        typedef std::chrono::high_resolution_clock hr_clock;
        typedef std::chrono::steady_clock::time_point time_point_t;
        
    public:
        void Start()
        {
            m_Start = m_End = hr_clock::now();
            bIsActive = true;
        }

        void Stop()
        {
            m_End = hr_clock::now();
            bIsActive = false;
        }

        double GetElapsedSeconds() const
        {
            time_point_t end = bIsActive ? hr_clock::now() : m_End;
            return (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_Start).count()) * 1e-9f;
        }

    private:
        time_point_t m_Start;
        time_point_t m_End;
        bool bIsActive = false;
    };
}