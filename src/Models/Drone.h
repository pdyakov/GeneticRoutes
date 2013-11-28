/*
 * Drone.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef DRONE_H_
#define DRONE_H_

#include <iostream>
#include "Coordinates.h"
#include "FlightBase.h"

class Drone {
public:
	Drone();
	Drone(float speed, float flightTime, std::string name, const FlightBase& flightBase);
	Drone(float speed, float flightTime, std::string name, const FlightBase& flightBase, const Coordinates& coordinates);
	virtual ~Drone() { };

	Coordinates getCurrentPosition() const;
	float getDroneSpeed() const;
	float getRemainingFlightTime() const;
	std::string getDroneName() const;
	FlightBase getFlightBase() const;
	int getDroneId() const;

	void setDroneId(int id);
	void setDroneName(std::string name);

protected:
	int _id;
	float _speed;
	float _flightTime;
	std::string _name;
	FlightBase _flightBase;
	Coordinates _currentPosition;
};


#endif /* DRONE_H_ */
