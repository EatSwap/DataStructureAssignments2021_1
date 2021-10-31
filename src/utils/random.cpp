#include <random>
#include <iostream>
#include <ctime>
#include "utils.h"

namespace utils {

unsigned randomInt() {
	static std::mt19937 R(std::time(nullptr));
	return R();
}

inline unsigned randomInt(unsigned n) {
	return randomInt() % n;
}

int randomChance(double n) {
	static std::mt19937 R(std::time(nullptr));
	// Poisson Distribution
	std::poisson_distribution<> poissonDistribution(n);
	return poissonDistribution(R);
}

}
