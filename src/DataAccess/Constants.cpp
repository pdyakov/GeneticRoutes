/*
 * Constants.cpp
 *
 *  Created on: 10 Nov 2013
 *      Author: Pavel Dyakov
 */

#include "Constants.h"

int Constants::getPopulationCount() {
	static int populationCount = 200;
	return populationCount;
}


