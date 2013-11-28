/*
 * DataRepository.h
 *
 *  Created on: 9 Nov 2013
 *      Author: Pavel Dyakov
 */

#ifndef DATAREPOSITORY_H_
#define DATAREPOSITORY_H_

#include "../Models/Drone.h"
#include "../Models/Target.h"
#include <vector>

class DataRepository {
public:
	static DataRepository& getInstance();
	virtual ~DataRepository() { };

	Drone *getDroneById(const int id) const;
	FlightBase *getBaseById(const int id) const;
	Target *getTargetById(const int id) const;

	std::vector<Drone> getDrones() const;
	std::vector<FlightBase> getBases() const;
	std::vector<Target> getTargets() const;

	void insertDrone(Drone& drone);
	void insertBase(FlightBase& drone);
	void insertTarget(Target& target);

	void updateDrone(Drone& drone);
	void updateBase(FlightBase& flightBase);
	void updateTarget(Target& target);

private:
	DataRepository();
	DataRepository(DataRepository const&);
	void operator=(DataRepository const&);

private:
	std::vector<Drone> _drones;
	std::vector<FlightBase> _bases;
	std::vector<Target> _targets;

	int _droneNextId;
	int _baseNextId;
	int _targetNextId;
};


#endif /* DATAREPOSITORY_H_ */
