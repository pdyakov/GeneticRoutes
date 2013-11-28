/*
 * TargetCoordinator.h
 *
 *  Created on: 20 Oct 2013
 *      Author: pavlik
 */

#ifndef TARGETCOORDINATOR_H_
#define TARGETCOORDINATOR_H_

#include <vector>
#include "../Models/Drone.h"
#include "../Models/Target.h"
#include "../Models/FlightBase.h"

class TargetCoordinator {
public:
	TargetCoordinator() { };
	virtual ~TargetCoordinator();

	void Pause(); // Pause all drones
	void Start(); // Start all drones
	void Abort(); // All drones must fly to there bases
};


#endif /* TARGETCOORDINATOR_H_ */
