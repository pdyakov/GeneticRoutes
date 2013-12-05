/*
 * Target.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef TARGET_H_
#define TARGET_H_

#include "Coordinates.h"

class Target {
public:
    Target(){}
	Target(const Coordinates& coordinates);
	virtual ~Target() { };

	Coordinates getTargetPosition() const;
	int getTargetId() const;

	void setTargetId(int id);

private:
	int _id;
	Coordinates _targetPosition;
};


#endif /* TARGET_H_ */
