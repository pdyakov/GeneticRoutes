/*
 * Route.h
 *
 *  Created on: 27 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include "../RouteManager/Models/Chromosome.h"

class Route {
public:
	Route(const Chromosome& chromosome, const Drone& drone);
	virtual ~Route() { };

	float getRouteDistance();
	float getFlightTime();
	std::vector<Coordinates> getCoordinates();

private:
	float distanceBetweenPoints(const Coordinates& point1, const Coordinates& point2);

private:
	std::vector<Coordinates> _coordinates;
	Drone _drone;
};

#endif /* ROUTE_H_ */
