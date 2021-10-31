#include <random>
#include "utils.h"

namespace utils {

unsigned randomInt() {
	static std::mt19937 R(time(nullptr));
	return R();
}

inline unsigned randomInt(unsigned n) {
	return randomInt() % n;
}

inline bool randomChance(double n) {
	return randomInt() < (((n < 0.0) ? ((n > 1.0) ? 1.0 : n) : 0.0) * unsigned(0xFFFFFFFF));
}

}
