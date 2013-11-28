/*
 * FlightBase.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "FlightBase.h"

FlightBase::FlightBase() : _id(0), _baseName("") {

}

FlightBase::FlightBase(std::string baseName, const Coordinates& coordinates)
: _id(0), _baseName(baseName), _basePosition(coordinates) {

}

std::string FlightBase::getBaseName() const {
	return _baseName;
}

Coordinates FlightBase::getBasePosition() const {
	return _basePosition;
}

int FlightBase::getBaseId() const {
	return _id;
}

void FlightBase::setBaseId(int id) {
	_id = id;
}



