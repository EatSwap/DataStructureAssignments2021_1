#ifndef UTILS_H
#define UTILS_H

namespace utils {

unsigned randomInt();

inline unsigned randomInt(unsigned);

inline bool randomChance(double n) {
	return randomInt() < (((n < 0.0) ? 0.0 : ((n > 1.0) ? 1.0 : n)) * unsigned(0xFFFFFFFF));
}

}

#endif
