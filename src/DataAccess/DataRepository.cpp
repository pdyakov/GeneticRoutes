/*
 * DataRepository.cpp
 *
 *  Created on: 9 Nov 2013
 *      Author: Pavel Dyakov
 */

#include "DataRepository.h"

DataRepository& DataRepository::getInstance() {
	static DataRepository instance;
	return instance;
}

DataRepository::DataRepository() : _droneNextId(1), _baseNextId(1), _targetNextId(1) {

}

Drone *DataRepository::getDroneById(const int id) const {
	for (unsigned int i = 0; i < _drones.size(); i++) {
		if (_drones.at(i).getDroneId() == id) {
			return (Drone *)&(_drones.at(i));
		}
	}
	return NULL;
}

FlightBase *DataRepository::getBaseById(const int id) const {
	for (unsigned int i = 0; i < _bases.size(); i++) {
		if (_bases.at(i).getBaseId() == id) {
			return (FlightBase *)&(_bases.at(i));
		}
	}
	return NULL;
}

Target *DataRepository::getTargetById(const int id) const {
	for (unsigned int i = 0; i < _targets.size(); i++) {
		if (_targets.at(i).getTargetId() == id) {
			return (Target *)&(_targets.at(i));
		}
	}
	return NULL;
}

std::vector<Drone> DataRepository::getDrones() const {
	return _drones;
}

std::vector<FlightBase> DataRepository::getBases() const {
	return _bases;
}

std::vector<Target> DataRepository::getTargets() const {
	return _targets;
}

void DataRepository::insertDrone(Drone& drone) {
	drone.setDroneId(_droneNextId);
	_droneNextId++;
	_drones.push_back(drone);
}

void DataRepository::insertBase(FlightBase& base) {
	base.setBaseId(_baseNextId);
	_baseNextId++;
	_bases.push_back(base);
}

void DataRepository::insertTarget(Target& target) {
	target.setTargetId(_targetNextId);
	_targetNextId++;
	_targets.push_back(target);
}

void DataRepository::updateDrone(Drone& drone) {
	for (unsigned int i = 0; i < _drones.size(); i++) {
		Drone bDrone = _drones.at(i);
		if (bDrone.getDroneId() == drone.getDroneId()) {
			drone.setDroneId(bDrone.getDroneId());
			_drones.assign(i, drone);
		}
	}
}

void DataRepository::updateBase(FlightBase& base) {
	for (unsigned int i = 0; i < _bases.size(); i++) {
		FlightBase bBase = _bases.at(i);
		if (bBase.getBaseId() == base.getBaseId()) {
			base.setBaseId(bBase.getBaseId());
			_bases.assign(i, base);
		}
	}
}

void DataRepository::updateTarget(Target& target) {
	for (unsigned int i = 0; i < _targets.size(); i++) {
		Target bTarget = _targets.at(i);
		if (bTarget.getTargetId() == target.getTargetId()) {
				target.setTargetId(bTarget.getTargetId());
				_targets.assign(i, target);
			}
		}
}


