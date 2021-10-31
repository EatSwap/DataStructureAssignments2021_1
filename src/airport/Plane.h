#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

namespace airport {

class Plane {
public:
	enum Status {
		NULL = 0, LANDING = 1, DEPARTING = 2
	};
private:
	inline static int planesCount = 0;
	int id;
	Status status = NULL;
public:
	Plane() = delete;

	explicit Plane(Status s) : status(s) {
		this->id = ++planesCount;
	}

	int getId() const;

	Status getStatus() const;

};

}

#endif //AIRPORT_PLANE_H
