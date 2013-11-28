/*
 * RouteManager.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef ROUTEMANAGER_H_
#define ROUTEMANAGER_H_

#include "Models/Population.h"
#include "../Models/Route.h"

class RouteManager {
public:
	RouteManager() { };
	virtual ~RouteManager() { };

	std::vector<Route> calculateBestRoutes(const std::vector<Target>& targets);

private:
	void selection(Population& population);
	void calculateSuitabilityScoreForPopulation(Population& population);
	bool routesResolved(Population& population);
	void nextGeneration(Population& population);
	Population crossing(Population& population);
private:
	std::vector<Population> _populations;
};


#endif /* ROUTEMANAGER_H_ */
