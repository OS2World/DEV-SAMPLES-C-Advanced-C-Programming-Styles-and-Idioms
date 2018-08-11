/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <iostream.h>

class Vehicle {
public:
	virtual int mpg() { return 0; }
	virtual void takeOff();
	virtual void swim();
	Vehicle(Vehicle *host) { hostVehicle = host; }
private:
	Vehicle *hostVehicle;
};

class Plane: public Vehicle {
public:
	int mpg() { return 100; }
	Plane(Vehicle *v) : Vehicle(v) { }
};

class Boat: public Vehicle {
public:
	int mpg() { return 10; }
	Boat(Vehicle *v) : Vehicle(v) { }
};

class SeaPlane: public Vehicle {
public:
	SeaPlane(): Vehicle(0) {
		currentMode = boat = new Boat(this);
		plane = new Plane(this);
	}
	void takeOff() { currentMode = plane; }
	void swim() { currentMode = boat; }
	Vehicle *operator->() { return currentMode; }
private:
	Vehicle *boat, *plane, *currentMode;
};

void
Vehicle::takeOff() { hostVehicle->takeOff(); }

void
Vehicle::swim() { hostVehicle->swim(); }

int main() {
	SeaPlane seaPlane;
	cout << "mpg = " << seaPlane->mpg() << endl;
	seaPlane->takeOff();
	cout << "mpg = " << seaPlane->mpg() << endl;
	seaPlane->swim();
	cout << "mpg = " << seaPlane->mpg() << endl;
}
