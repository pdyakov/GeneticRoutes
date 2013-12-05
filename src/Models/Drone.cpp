/*
 * Drone.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */
#include "Drone.h"

Drone::Drone() : _id(0), _speed(0), _flightTime(0), _name("") {

}

Drone::Drone(float speed, float flightTime, std::string name,const FlightBase& flightBase, const Coordinates& coordinates)
: _id(0), _speed(speed), _flightTime(flightTime), _name(name), _flightBase(flightBase), _currentPosition(coordinates) {

}

Drone::Drone(float speed, float flightTime, std::string name, const FlightBase& flightBase)
: _id(0), _speed(speed), _flightTime(flightTime), _name(name), _flightBase(flightBase), _currentPosition(flightBase.getBasePosition()) {

}

Coordinates Drone::getCurrentPosition() const {
	return _currentPosition;
}

float Drone::getDroneSpeed() const {
	return _speed;
}

float Drone::getRemainingFlightTime() const {
    return _flightTime;
}

std::string Drone::getDroneName() const {
	return _name;
}

FlightBase Drone::getFlightBase() const {
	return _flightBase;
}

int Drone::getDroneId() const {
	return _id;
}

void Drone::setDroneId(int id) {
	_id = id;
}

void Drone::setDroneName(std::string name) {
	_name = name;
}
