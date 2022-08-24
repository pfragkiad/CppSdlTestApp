#pragma once

#include <random>

inline std::random_device rd;
inline std::mt19937 gen(rd());

inline int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

inline double random(double low, double high)
{
	std::uniform_real_distribution<> dist(low, high);
	return dist(gen);
}