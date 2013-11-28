/*
 * Target.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Target.h"

Target::Target(const Coordinates& coordinates) : _id(0), _targetPosition(coordinates) {

}

Coordinates Target::getTargetPosition() const {
	return _targetPosition;
}

int Target::getTargetId() const {
	return _id;
}

void Target::setTargetId(int id) {
	_id = id;
}


