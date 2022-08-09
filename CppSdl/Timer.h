#pragma once

#include <chrono>
using namespace std::chrono_literals;

template <size_t N>
class Timer {
	std::chrono::steady_clock::time_point start;

	//static inline std::vector<std::chrono::nanoseconds> _durations;
	static inline std::chrono::nanoseconds _durations[N];
	static inline std::chrono::nanoseconds sum = std::chrono::nanoseconds{ 0ns };
	static inline int iCounter = 0;
public:
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto duration = std::chrono::high_resolution_clock::now() - start;
		sum += duration;
		iCounter++;

		if (iCounter > N)
		{
			sum -= _durations[0]; //remove the oldest entry
			for (size_t i = 0; i < N - 1; i++)
				_durations[i] = _durations[i+1];
			//the last entry is the current one
			_durations[N - 1] = duration;
		}
		else // (iCounter <= 10)
		{
			_durations[iCounter - 1] = duration;
			return;
		}

		//std::cout << "Current: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration)
		//	<< ", Sum: " << std::chrono::duration_cast<std::chrono::milliseconds>(sum)
		//	<< ", Average: " << std::chrono::duration_cast<std::chrono::milliseconds>(sum/N) <<std::endl;


		//_durations.push_back(duration);

		////std::cout << std::chrono::duration_cast<std::chrono::seconds>(duration) << "\n";
		//std::cout << "Current: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << "\n";
		if (++iCounter % N == 0)
		{
			//auto average = std::accumulate(_durations.cbegin(), _durations.cend(),
			//	decltype(_durations)::value_type(0)) / _durations.size();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(sum);
			auto average = millis.count() / (double)N;
			//fps
			double fps = 1000.0 / average;
			std::cout << "FPS: " << setprecision(3) << fps << ", Average: " << average << ", Current: " <<
				std::chrono::duration_cast<std::chrono::milliseconds>(duration) << "\n";
		}
	}
};
