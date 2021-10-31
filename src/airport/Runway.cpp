#include <iostream>

#include "Runway.h"
#include "utils/utils.h"

namespace airport {

int Runway::getMaxQueueSize() const {
	return MAX_QUEUE_SIZE;
}

void Runway::setMaxQueueSize(int maxQueueSize) {
	MAX_QUEUE_SIZE = maxQueueSize;
}

double Runway::getDepartingRate() const {
	return DEPARTING_RATE;
}

void Runway::setDepartingRate(double departingRate) {
	DEPARTING_RATE = departingRate;
}

double Runway::getLandingRate() const {
	return LANDING_RATE;
}

void Runway::setLandingRate(double landingRate) {
	LANDING_RATE = landingRate;
}

Runway::Runway(int maxQueueSize, double departingRate, double landingRate, bool isVerbose = false) : MAX_QUEUE_SIZE(maxQueueSize), DEPARTING_RATE(departingRate), LANDING_RATE(landingRate), IS_VERBOSE(isVerbose) {}

void Runway::generatePlane() {
	// Generate departing plane
	if (utils::randomChance(this->DEPARTING_RATE)) {
		Plane t(Plane::DEPARTING);
		if (insertPlane(t)) {
			printLog(t, SUCCESS);
		} else {
			++takeoffRejected;
			printLog(t, REJECTED);
		}
	} else {
		printLog("No departing plane generated at this time.");
	}
	// Generate landing plane
	if (utils::randomChance(this->LANDING_RATE)) {
		Plane t(Plane::LANDING);
		if (insertPlane(t)) {
			printLog(t, SUCCESS);
		} else {
			++landingRejected;
			printLog(t, REJECTED);
		}
	} else {
		printLog("No landing plane generated at this time.");
	}
}

bool Runway::insertPlane(const Plane& plane) {
	switch (plane.status) {
		case Plane::Status::LANDING:
			if (this->landingQueue.size() >= this->MAX_QUEUE_SIZE)
				return false;
			this->landingQueue.push(plane);
			break;
		case Plane::Status::DEPARTING:
			if (this->takeoffQueue.size() >= this->MAX_QUEUE_SIZE)
				return false;
			this->takeoffQueue.push(plane);
			break;
		default: // Invalid branch reached
			std::cerr << "[WARN] Invalid branch reached. (1)" << std::endl;
	}
	return true;
}

void Runway::printLog(const std::string& msg) const {
	if (IS_VERBOSE)
		printf("[%d] %s\n", this->clock, msg.c_str());
}

void Runway::printLog(const Plane& plane, Result result) const {
	if (IS_VERBOSE)
		printf("[%d] Generated Plane # %d trying to %s %s.\n",
			   clock,
			   plane.getId(),
			   plane.status == Plane::Status::LANDING ? "land" : (plane.status == Plane::Status::DEPARTING ? "takeoff" : "[INVALID]"),
			   result == SUCCESS ? "and succeeded" : "but rejected"
		);
}

}
