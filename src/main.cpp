#include <iostream>
#include <random>
#include <chrono>

#include "airport/Runway.h"

int main() {

	std::cout << "Runway simulator\n"
			  << "-----------------------------------------\n"
			  << "Your favourite max queue size: ";
	int maxQueueSize;
	std::cin >> maxQueueSize;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Sorry, but your input is invalid. Try again: ";
		std::cin >> maxQueueSize;
	}
	std::cout << "Your favourite max queue size is: " << maxQueueSize << "\n"
			  << "Your favourite simulation time: ";
	int simulationTime;
	std::cin >> simulationTime;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Sorry, but your input is invalid. Try again: ";
		std::cin >> simulationTime;
	}
	std::cout << "Your favourite simulation time is: " << simulationTime << "\n"
			  << "Your favourite landing planes generating rate: ";
	double landingRate;
	std::cin >> landingRate;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Sorry, but your input is invalid. Try again: ";
		std::cin >> landingRate;
	}
	std::cout << "Your favourite landing planes generating rate is: " << landingRate << "\n"
			  << "Your favourite takeoff planes generating rate: ";
	double takeoffRate;
	std::cin >> takeoffRate;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Sorry, but your input is invalid. Try again: ";
		std::cin >> takeoffRate;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Your favourite takeoff planes generating rate is: " << takeoffRate << "\n"
			  << "Want to print the detailed process (<Enter> for no and anything else for yes): ";
	std::string line;
	std::getline(std::cin, line);
	bool isVerbose = line.length();

	airport::Runway runway(maxQueueSize, takeoffRate, landingRate, isVerbose);
	std::cout << "-----------------------------------------\nSimulation started\n";
	auto startTime = std::chrono::high_resolution_clock::now();
	runway.runSimulation(simulationTime);
	auto endTime = std::chrono::high_resolution_clock::now();
	std::cout << "Simulation took " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "μs.\n";

	std::cout << runway.getSummary();
	return 0;
}
