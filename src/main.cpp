#include <iostream>

#include "airport/Runway.h"

int main() {
	airport::Runway runway(30, 0.4, 0.4, true);
	runway.runSimulation(100);
	std::cout << runway.getSummary();
	return 0;
}
