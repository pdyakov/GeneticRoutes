//============================================================================
// Name        : FlightControlSystem.cpp
// Author      : Pavel Dyakov
// Version     :
// Description : Flight Control System for UAV
//============================================================================

#include <iostream>
#include "DataAccess/DataRepository.h"
#include "RouteManager/RouteManager.h"
using namespace std;

int Notmain() {

	// Set flight bases. Drones always start and end at this point.
	FlightBase base1 = FlightBase("base1", Coordinates(19, 3));
	FlightBase base2 = FlightBase("base2", Coordinates(2, 20));
	FlightBase base3 = FlightBase("base3", Coordinates(3, 3));

	// Set drones. (speed, max flight time, name ,base)
	Drone drone1 = Drone(22, 3, "drone1", base1);
	Drone drone2 = Drone(12, 3, "drone2", base2);
	Drone drone3 = Drone(17, 3, "drone3", base3);

	// Set targets. (x, y)
	Target target1 = Target(Coordinates(4, 11));
	Target target2 = Target(Coordinates(10, 7));
	Target target3 = Target(Coordinates(16, 14));
	Target target4 = Target(Coordinates(11, 20));
	Target target5 = Target(Coordinates(9, 14));
	Target target6 = Target(Coordinates(18, 17));
	Target target7 = Target(Coordinates(15, 4));
	Target target8 = Target(Coordinates(19, 10));

	// Insert data.
	DataRepository::getInstance().insertBase(base1);
	DataRepository::getInstance().insertBase(base2);
	DataRepository::getInstance().insertBase(base3);

	DataRepository::getInstance().insertDrone(drone1);
	DataRepository::getInstance().insertDrone(drone2);
	DataRepository::getInstance().insertDrone(drone3);

	DataRepository::getInstance().insertTarget(target1);
	DataRepository::getInstance().insertTarget(target2);
	DataRepository::getInstance().insertTarget(target3);
	DataRepository::getInstance().insertTarget(target4);
	DataRepository::getInstance().insertTarget(target5);
	DataRepository::getInstance().insertTarget(target6);
	DataRepository::getInstance().insertTarget(target7);
	DataRepository::getInstance().insertTarget(target8);

	// Resolve routes.
	RouteManager manager = RouteManager();
	std::vector<Route> routes = manager.calculateBestRoutes(DataRepository::getInstance().getTargets());

	// Show results.
	for (unsigned int i = 0; i < routes.size(); i++) {
		std::vector<Coordinates> coordinates = routes.at(i).getCoordinates();
		cout << "Route " << i << " - " << routes.at(i).getFlightTime() << endl;
		for (unsigned int j = 0; j < coordinates.size(); j++) {
			cout << "(" << coordinates.at(j).getPointX() << ";" << coordinates.at(j).getPointY() << ")" << endl;
		}
	}

	return 0;
}
