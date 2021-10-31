#ifndef AIRPORT_RUNWAY_H
#define AIRPORT_RUNWAY_H

#include <queue>

#include "airport/Plane.h"

namespace airport {

class Runway {
public:
	enum Status {
		IDLE, LAND, TAKEOFF
	};
	enum Result {
		SUCCESS, REJECTED
	};
private:
	const bool IS_VERBOSE = false;
	int MAX_QUEUE_SIZE = 10.0;
	double DEPARTING_RATE = 0.3, LANDING_RATE = 0.3;
	Status status = IDLE;

	std::queue<Plane> landingQueue, takeoffQueue;

	// Counters
	int clock = 0;
	int landingCount = 0, takeoffCount = 0;
	int landingRejected = 0, takeoffRejected = 0;
	int landingWaitTime = 0, takeoffWaitTime = 0;

	void generatePlane();

	bool insertPlane(const Plane& plane);

	void printLog(const std::string& msg) const;

	void printLog(const Plane& plane, Result result) const;

public:
	Status getStatus() const;

	void reset();

	void runSimulation();

	Runway() = default;

	Runway(int maxQueueSize, double departingRate, double landingRate, bool isVerbose);

	int getMaxQueueSize() const;

	void setMaxQueueSize(int maxQueueSize);

	double getDepartingRate() const;

	void setDepartingRate(double departingRate);

	double getLandingRate() const;

	void setLandingRate(double landingRate);
};

}

#endif