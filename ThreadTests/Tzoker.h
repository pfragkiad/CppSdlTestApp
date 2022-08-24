#pragma once


#include <random>
#include <vector>
#include <algorithm>

std::random_device entropySource;
std::mt19937_64 generator(entropySource());
std::uniform_int_distribution<int> distMain(1, 45), distTzoker(1, 20);

struct Tzoker
{
	int tzoker;
	std::vector<int> main;
	friend std::ostream& operator <<(std::ostream& o, const Tzoker& tzoker) //to make our life easy with print statements
	{
		o << tzoker.main[0] << ", " << tzoker.main[1] << ", " << tzoker.main[2] << ", " << tzoker.main[3] << ", " << tzoker.main[4] << " Tzoker: " << tzoker.tzoker;
		return o;
	}
};

Tzoker getNextTzoker()
{
	int tzoker = distTzoker(generator);
	std::vector <int> lottery;
	for (int l = 0; l < 5; l++)
	{
		int current = distMain(generator); //a lottery cannot contain the same value twice 
		while (std::find(lottery.begin(), lottery.end(), current) != lottery.end())
			current = distMain(generator);
		lottery.push_back(current);
	}
	std::sort(lottery.begin(), lottery.end());  //sort it to facilitate the equality comparison

	return { tzoker,lottery };
}

void PredictTzoker(int columns)
{
	Tzoker lastTzoker = { 2, std::vector{27,39,40,9,31} }; //the latest tzoker sequence
	std::sort(lastTzoker.main.begin(), lastTzoker.main.end()); //sort it to facilitate the equality comparison
	std::cout << "Last sequence: " << lastTzoker << std::endl;

	for (int tz = 0; tz < columns; tz++)
	{
		//std::cout << tz << std::endl;
		size_t i = 0u;
		while (true)
		{
			i++;
			auto tzoker = getNextTzoker();

			bool areEqual =
				tzoker.tzoker == lastTzoker.tzoker &&
				std::equal(tzoker.main.begin(), tzoker.main.end(), lastTzoker.main.begin());

			if (areEqual) //when we find the lastTzoker sequence in the pseudo-random generated sequence we retrieve the next one
			{
				tzoker = getNextTzoker();
				std::cout << tzoker << std::endl;
				break;
			}


			//if (i % 5000000 == 0) std::cout << "Reached " << i << std::endl;
		}
	}
}