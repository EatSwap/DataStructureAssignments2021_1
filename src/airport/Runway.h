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
	int TIME_TO_SIMULATE = -1;

	std::queue<Plane> landingQueue, takeoffQueue;

	// Counters
	// size_t --> unsigned long long
	size_t clock = 0;
	size_t landingCount = 0, takeoffCount = 0;
	size_t landingRejected = 0, takeoffRejected = 0;
	size_t landingWaitTime = 0, takeoffWaitTime = 0;
	size_t idleTime = 0;

	void generatePlane();

	bool insertPlane(const Plane& plane);

	void printLog(const std::string& msg) const;

	void printLog(const Plane& plane, Result result) const;

	void printLog(const Plane& plane, Status status) const;

	void shutdown();

	bool landPlane();

	bool takeoffPlane();

public:
	Status getStatus() const;

	void reset();

	void runSimulation(int duration);

	std::string getSummary() const;

	Runway() = default;

	Runway(int maxQueueSize, double departingRate, double landingRate, bool isVerbose = false);

	int getMaxQueueSize() const;

	void setMaxQueueSize(int maxQueueSize);

	double getDepartingRate() const;

	void setDepartingRate(double departingRate);

	double getLandingRate() const;

	void setLandingRate(double landingRate);
};

}

#endif