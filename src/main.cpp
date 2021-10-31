#include <iostream>
#include <random>
#include <map>

#include "airport/Runway.h"

int main() {
	airport::Runway runway(50, 0.25, 85);
	runway.runSimulation(100000);
	std::cout << runway.getSummary();
	return 0;
}
