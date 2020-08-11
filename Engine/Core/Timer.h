#pragma once

#include <chrono>

namespace gk
{
	class Timer
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = std::chrono::duration<clock::rep, std::nano>;

	public:
		Timer() : m_timepoint(clock::now()) {}

		void Reset();
		clock::rep ElapsedTicks();
		clock::rep TicksPerSecond();

		double ElapsedSeconds();

	protected:
		clock::time_point m_timepoint;
	};

	class FrameTimer : public Timer
	{
	public:
		void Tick();
		float DeltaTime() { return m_dt; };

	protected:
		float m_dt{ 0 };
	};
}