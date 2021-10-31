#include <iostream>
#include <sstream>
#include <cassert>

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

Runway::Status Runway::getStatus() const {
	return this->status;
}

Runway::Runway(int maxQueueSize, double departingRate, double landingRate, bool isVerbose) : MAX_QUEUE_SIZE(maxQueueSize), DEPARTING_RATE(departingRate), LANDING_RATE(landingRate), IS_VERBOSE(isVerbose) {}

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
	switch (plane.getStatus()) {
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

void Runway::reset() {
	/*
		this->MAX_QUEUE_SIZE = 10.0;
		this->DEPARTING_RATE = this->LANDING_RATE = 0.3;
	*/
	this->status = IDLE;
	this->landingQueue = std::queue<Plane>();
	this->takeoffQueue = std::queue<Plane>();
	clock = landingCount = takeoffCount = landingRejected = takeoffRejected = landingWaitTime = takeoffWaitTime = 0;
}

void Runway::printLog(const std::string& msg) const {
	if (IS_VERBOSE)
		printf("[%d] %s\n", this->clock, msg.c_str());
}

void Runway::printLog(const Plane& plane, const Result result) const {
	if (IS_VERBOSE)
		printf("[%d] Generated Plane # %d trying to %s %s.\n",
			   clock,
			   plane.getId(),
			   plane.getStatus() == Plane::Status::LANDING ? "land" : (plane.getStatus() == Plane::Status::DEPARTING ? "takeoff" : "[INVALID]"),
			   result == SUCCESS ? "and succeeded" : "but rejected"
		);
}

void Runway::printLog(const Plane& plane, Status status) const {
	if (IS_VERBOSE)
		printf("[%d] Plane # %d used the runway to %s.\n",
			   clock,
			   plane.getId(),
			   status == LAND ? "land" : (status == TAKEOFF ? "takeoff" : "[INVALID]")
		);
}

void Runway::runSimulation(const int duration) {
	reset();
	for (clock = 0; clock < duration; ++clock) {
		generatePlane();
		// Try to inspect queues;
		if (!landingQueue.empty()) {
			assert(landPlane());
		} else if (!takeoffQueue.empty()) {
			assert(takeoffPlane());
		} else {
			this->status = IDLE;
			++idleTime;
			printLog("The runway is idle at this time.");
		}
		landingWaitTime += landingQueue.size();
		takeoffWaitTime += takeoffQueue.size();
	}
	shutdown();
}

bool Runway::landPlane() {
	if (takeoffQueue.empty())
		return false;
	this->status = LAND;
	Plane t = landingQueue.front();
	landingQueue.pop();
	++landingCount;
	printLog(t, this->status);
	return true;
}

bool Runway::takeoffPlane() {
	if (takeoffQueue.empty())
		return false;
	this->status = TAKEOFF;
	Plane t = takeoffQueue.front();
	takeoffQueue.pop();
	++takeoffCount;
	printLog(t, this->status);
	return true;
}

void Runway::shutdown() {
	printLog("Shutting down... Clearing queue");
	for (; !landingQueue.empty(); ++clock) {
		assert(landPlane());
		landingWaitTime += landingQueue.size();
		takeoffWaitTime += takeoffQueue.size();
	}
	for (; !takeoffQueue.empty(); ++clock) {
		assert(takeoffPlane());
		landingWaitTime += landingQueue.size();
		takeoffWaitTime += takeoffQueue.size();
	}
	printLog("Shutdown Completed.");
}

std::string Runway::getSummary() const {
	std::string ret;
	std::stringstream ss(ret);
	ss << "Summary:" << std::endl;
	ss << "Time simulated: " << clock << std::endl;
	ss << "Accepted planes (land/takeoff): " << landingCount << "/" << takeoffCount << std::endl;
	ss << "Rejected planes (land/takeoff): " << landingRejected << "/" << takeoffRejected << std::endl;
	ss << "Average landing waiting time: " << (double (landingWaitTime) / double (landingCount)) << std::endl;
	ss << "Average takeoff waiting time: " << (double (takeoffWaitTime) / double (takeoffCount)) << std::endl;
	// ss <<
	return ret;
}

}
