/*
 * Route.cpp
 *
 *  Created on: 27 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Route.h"
#include "math.h"

Route::Route(const Chromosome& chromosome, const Drone& drone) {
	_drone = drone;

	// Initialise route with current drone position
	_coordinates.push_back(drone.getCurrentPosition());

	// Add targets to route
	for (unsigned int i = 0; i < chromosome.getSize(); i++) {
		Gene gene = chromosome.getGeneAtIndex(i);
		if (gene.getDrone().getDroneName() == drone.getDroneName()) {
			_coordinates.push_back(gene.getTarget().getTargetPosition());
		}
	}

	// Add base position as final route point
	_coordinates.push_back(drone.getFlightBase().getBasePosition());
}

float Route::getRouteDistance() {
	float result = 0;

	for (unsigned int i = 0; i < _coordinates.size() - 1; i++) {
		result += distanceBetweenPoints(_coordinates.at(i), _coordinates.at(i + 1));
	}

	return result;
}

float Route::getFlightTime() {
	return getRouteDistance() / _drone.getDroneSpeed();
}

float Route::distanceBetweenPoints(const Coordinates& point1, const Coordinates& point2) {
	float xDifference = point2.getPointX() - point1.getPointX();
	float yDifference = point2.getPointY() - point1.getPointY();

	return sqrt((xDifference * xDifference) + (yDifference * yDifference));
}

std::vector<Coordinates> Route::getCoordinates() {
	return _coordinates;
}
