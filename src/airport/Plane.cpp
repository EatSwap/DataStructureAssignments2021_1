#include "Plane.h"

namespace airport {

int Plane::getId() const {
	return id;
}

void Plane::setId(int id) {
	Plane::id = id;
}

Plane::Status Plane::getStatus() const {
	return status;
}

void Plane::setStatus(Plane::Status status) {
	Plane::status = status;
}

}
