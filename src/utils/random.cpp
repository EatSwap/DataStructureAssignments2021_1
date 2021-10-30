#include <random>
#include "utils.h"

namespace utils {

unsigned randomInt() {
	static std::mt19937 R(time(nullptr));
	return R();
}

unsigned randomInt(unsigned n) {
	return randomInt() % n;
}

}