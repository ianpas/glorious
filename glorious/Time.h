#pragma once
#include <chrono>

namespace Glorious
{
	class Time
	{
	public:
		template<typename Function, class... Args>
		static void Measure(Function f, Args... args)
		{
			auto start = std::chrono::high_resolution_clock::now();
			f(args...);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			m_DeltaTime = elapsed_seconds.count();
			m_TotalTime += m_DeltaTime;
		}

	public:
		static float m_DeltaTime;
		static float m_TotalTime;
	};

}
