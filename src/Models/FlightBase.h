/*
 * FlightBase.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef FLIGHTBASE_H_
#define FLIGHTBASE_H_

#include "Coordinates.h"
#include <iostream>

class FlightBase {
public:
	FlightBase();
	FlightBase(std::string baseName, const Coordinates& coordinates);
	virtual ~FlightBase() { };

	std::string getBaseName() const;
	Coordinates getBasePosition() const;
	int getBaseId() const;
	void setBaseId(int id);

private:
	int _id;
	std::string _baseName;
	Coordinates _basePosition;
};


#endif /* FLIGHTBASE_H_ */
