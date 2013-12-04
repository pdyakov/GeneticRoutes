/*
 * Gene.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Gene.h"

Gene::Gene(const Target& target, const Drone& drone) : _target(target), _drone(drone) {
}

Drone* Gene::getDrone() {
	return &_drone;
}

Target* Gene::getTarget() {
	return &_target;
}

void Gene::setDrone(const Drone& drone) {
	_drone = drone;
}

void Gene::setTarget(const Target& target) {
	_target = target;
}
