#include <random>
#include <iostream>
#include <ctime>
#include "utils.h"

namespace utils {

int randomChance(double n) {
	static std::mt19937 R(std::time(nullptr));
	// Poisson Distribution
	std::poisson_distribution<> poissonDistribution(n);
	return poissonDistribution(R);
}

}
